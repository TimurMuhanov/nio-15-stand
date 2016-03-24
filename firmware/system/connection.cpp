#include "connection.h"
#include "settings.h"
#include "control.h"
#include "imu.h"
#include "nav.h"
#include "encoder.h"
#include "servo.h"
#include "mavlink_bridge_header.h"
#include "mavlink.h"


mavlink_system_t mavlink_system;


static THD_FUNCTION(connectionReceive, arg);
static THD_WORKING_AREA(connectionReceiveWorkingArea, 2048);

extern "C" THD_FUNCTION(connectionUpdate1Hz, arg);
static THD_WORKING_AREA(connectionUpdate1HzWorkingArea, 2048);

extern "C" THD_FUNCTION(connectionUpdate40Hz, arg);
static THD_WORKING_AREA(connectionUpdate40HzWorkingArea, 2048);

static THD_FUNCTION(connectionSendSettings, arg);
static THD_WORKING_AREA(connectionSendSettingsWorkingArea, 2048);

float cpuUsage = 0;
u32 usageTime = 0;
u32 systemTime = 0;
u32 threadCount = 0;
static binary_semaphore_t messageSendAccess;

void connectionInit(void) {
    chBSemObjectInit(&messageSendAccess, false);

    mavlink_system.sysid = 0;
	mavlink_system.compid = MAV_COMP_ID_IMU;

    thread_t* tread;

    tread = chThdCreateStatic(  connectionUpdate1HzWorkingArea,
                        sizeof(connectionUpdate1HzWorkingArea),
                        NORMALPRIO, connectionUpdate1Hz, NULL);
    Thread::addThread( tread, string("cnct_upd_1") );
    tread = chThdCreateStatic(  connectionUpdate40HzWorkingArea,
                        sizeof(connectionUpdate40HzWorkingArea),
                        NORMALPRIO, connectionUpdate40Hz, NULL);
    Thread::addThread( tread, string("cnct_upd_40") );
    tread = chThdCreateStatic(  connectionReceiveWorkingArea,
                        sizeof(connectionReceiveWorkingArea),
                        NORMALPRIO, connectionReceive, NULL);
    Thread::addThread( tread, string("cnct_rcv") );
}

THD_FUNCTION(connectionUpdate1Hz, arg) {
    systime_t time = chVTGetSystemTime();
    u8 mav_mode;

    while( !chThdShouldTerminateX() ) {
        time += MS2ST(1000);
        chThdSleepUntil(time);

        if( controlStatus() & CONTROL_MODE_RUN )
            mav_mode = 0;
        else
            mav_mode = MAV_MODE_FLAG_SAFETY_ARMED;

        chBSemWait(&messageSendAccess);
        mavlink_msg_heartbeat_send(
            MAVLINK_DEFAULT_COMM,
            MAV_TYPE_FIXED_WING,
            MAV_AUTOPILOT_GENERIC,
            mav_mode,
            0,
            MAV_STATE_STANDBY
        );

        mavlink_msg_system_info_send(
            MAVLINK_DEFAULT_COMM, //mavlink_channel_t chan,
            cpuUsage, //float cpu_usage,
            usageTime, //uint32_t usage_time,
            systemTime, //uint32_t system_time,
            threadCount //uint32_t thread_count
        );
        chBSemSignal(&messageSendAccess);

    }

    chThdExit(0);
}

THD_FUNCTION(connectionUpdate40Hz, arg) {
	systime_t time = chVTGetSystemTime();

    while( !chThdShouldTerminateX() ) {
        time += MS2ST(25);
        chThdSleepUntil(time);

        vectorData accel = imuAccelGet();
        vectorData gyro = imuGyroGet();
        vectorData mag = imuMagGet();

        chBSemWait(&messageSendAccess);
        mavlink_msg_scaled_imu_send(
            MAVLINK_DEFAULT_COMM,
            accel.time/10.0,
            (s16) ((accel.x)*1000.0f),
            (s16) ((accel.y)*1000.0f),
            (s16) ((accel.z)*1000.0f),
            (s16) ((gyro.x)*1000.0f),
            (s16) ((gyro.y)*1000.0f),
            (s16) ((gyro.z)*1000.0f),
            (s16) ((mag.x)*1000.0f),
            (s16) ((mag.y)*1000.0f),
            (s16) ((mag.z)*1000.0f)
        );

//        vectorData rpy = get_rpy();
//        mavlink_msg_attitude_send(
//                MAVLINK_DEFAULT_COMM,
//                rpy.time/10.0,
//                rpy.x,
//                rpy.y,
//                rpy.z,
//                0,
//                0,
//                0 );

        quaternionData q = get_quat();
        mavlink_msg_attitude_quaternion_send(
                MAVLINK_DEFAULT_COMM,
                q.time,
                q.w,
                q.x,
                q.y,
                q.z,
                0,
                0,
                0 );

        scalarData pressure = imuPressureGet();
        scalarData temperature = imuTempGet();
        mavlink_msg_scaled_pressure_send(
            MAVLINK_DEFAULT_COMM,
            pressure.time/10.0,
            pressure.val,
            0,
            temperature.val*100.0f
        );

        u32 time = encoderGet(0).time*10;
        float e0 = encoderGet(0).val;
        float e1 = encoderGet(1).val;
        float e2 = encoderGet(2).val;
        float e3 = encoderGet(3).val;
        float e4 = encoderGet(4).val;
        float e5 = encoderGet(5).val;
        float e6 = encoderGet(6).val;
        float e7 = encoderGet(7).val;
        float e8 = encoderGet(8).val;

        mavlink_msg_encoder_output_raw_send( MAVLINK_DEFAULT_COMM, time, 0, e0, e1, e2, e3, e4, e5, e6, e7, e8 );

        mavlink_msg_servo_output_raw_send(
                MAVLINK_DEFAULT_COMM,
                servoGet(0).time/10.0,
                0,
                (180.0f+servoGet(0).val)*100,
                (180.0f+servoGet(1).val)*100,
                (180.0f+servoGet(2).val)*100,
                (180.0f+servoGet(3).val)*100,
                (180.0f+servoGet(4).val)*100,
                (180.0f+servoGet(5).val)*100,
                (180.0f+servoGet(6).val)*100,
                (180.0f+servoGet(7).val)*100);

        chBSemSignal(&messageSendAccess);
    }
    chThdExit(0);
}

THD_FUNCTION(connectionSendSettings, arg) {
//    for(
//        map<string, string>::iterator it = Settings::settings().begin();
//        it != Settings::settings().end();
//        it++
//    ) {
//        mavlink_msg_settings_item_send( MAVLINK_DEFAULT_COMM, it->first.substr(0,50).c_str(), it->second.substr(0,50).c_str() );
//    }
    chThdExit(0);
}

THD_FUNCTION(connectionReceive, arg) {
	mavlink_message_t mavlink_message;
	mavlink_status_t mavlink_status;
	mavlink_mcu_jump_to_t mcu_jump_to;
	char c;
 
    while( !chThdShouldTerminateX() ) {
		receiveFromTelemethry((u8*)&c, 1);
        if( mavlink_parse_char(MAVLINK_DEFAULT_COMM, (uint8_t)c, &mavlink_message, &mavlink_status) ) {
			switch(mavlink_message.msgid) {
				case MAVLINK_MSG_ID_HEARTBEAT: {
					//control.connection = CONTROL_CONNECTED;
				} break;

				case MAVLINK_MSG_ID_COMMAND_INT: {
					mavlink_command_int_t command;
					mavlink_msg_command_int_decode(&mavlink_message, &command);
					switch(command.command) {
						case MAV_CMD_DO_SET_SERVO :
							servoSet(command.param1-1, command.param2);
							break;
						case MAV_CMD_COMPONENT_ARM_DISARM :
							if( command.param1 == 0 ) {
								controlStop();
							} else {
								controlStart();
							}
							break;
					}

				} break;

				case MAVLINK_MSG_ID_MCU_JUMP_TO: {
                    mavlink_msg_mcu_jump_to_decode( &mavlink_message, &mcu_jump_to );
					if( mcu_jump_to.address == MCU_JUMP_TO_BOOTLOADER ) {
                        JUMP_TO(BOARD_FLASH_BOOTLOADER);
					}
				} break;

                case MAVLINK_MSG_ID_SETTINGS_REQUEST: {
                    chThdCreateStatic(  connectionSendSettingsWorkingArea,
                                        sizeof(connectionSendSettingsWorkingArea),
                                        NORMALPRIO, connectionSendSettings, NULL);
                } break;

//                case MAVLINK_MSG_ID_SETTINGS_ITEM: {
//                    mavlink_settings_item_t mavlink_settings_item;
//                    mavlink_msg_settings_item_decode(&mavlink_message, &mavlink_settings_item);
//                    std::string key = std::string(mavlink_settings_item.name);
//                    std::string value = std::string(mavlink_settings_item.value);
//                    Settings::set( key, value );
//                    Settings::sync();
//                    mavlink_msg_settings_item_send( MAVLINK_DEFAULT_COMM, key.substr(0,50).c_str(), value.substr(0,50).c_str() );
//                } break;

//                case MAVLINK_MSG_ID_SETTINGS_REMOVE: {
//                    mavlink_settings_remove_t mavlink_settings_remove;
//                    mavlink_msg_settings_remove_decode(&mavlink_message, &mavlink_settings_remove);
//                    std::string key = std::string(mavlink_settings_remove.name);
//                    Settings::remove( key );
//                    Settings::sync();
//                } break;

				default:
				break;
			}
		}
    }
    chThdExit(0);
}

void connectionSetCpuInfo(float usage, u32 uTime, u32 sTime, u32 tCount) {
    cpuUsage = usage;
    usageTime = uTime;
    systemTime = sTime;
    threadCount = tCount;
}
