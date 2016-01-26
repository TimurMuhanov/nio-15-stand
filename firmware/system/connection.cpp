#include "connection.h"
#include "settings.h"


mavlink_system_t mavlink_system;


static THD_FUNCTION(connectionReceive, arg);
static THD_WORKING_AREA(connectionReceiveWorkingArea, 1024);

static THD_FUNCTION(connectionUpdate1Hz, arg);
static THD_WORKING_AREA(connectionUpdate1HzWorkingArea, 256);

static THD_FUNCTION(connectionUpdate40Hz, arg);
static THD_WORKING_AREA(connectionUpdate40HzWorkingArea, 512);

static THD_FUNCTION(connectionSendSettings, arg);
static THD_WORKING_AREA(connectionSendSettingsWorkingArea, 256);



void connectionInit(void) {
    mavlink_system.sysid = 0;
	mavlink_system.compid = MAV_COMP_ID_IMU;

    chThdCreateStatic(  connectionUpdate1HzWorkingArea,
                        sizeof(connectionUpdate1HzWorkingArea),
                        NORMALPRIO, connectionUpdate1Hz, NULL);
    chThdCreateStatic(  connectionUpdate40HzWorkingArea,
                        sizeof(connectionUpdate40HzWorkingArea),
                        NORMALPRIO, connectionUpdate40Hz, NULL);
    chThdCreateStatic(  connectionReceiveWorkingArea,
                        sizeof(connectionReceiveWorkingArea),
                        NORMALPRIO, connectionReceive, NULL);
}

THD_FUNCTION(connectionUpdate1Hz, arg) {
    systime_t time = chVTGetSystemTime();
    u8 mav_mode;

    while (1) {
        time += MS2ST(1000);

        if( controlStatus() & CONTROL_MODE_RUN )
            mav_mode = 0;
        else
            mav_mode = MAV_MODE_FLAG_SAFETY_ARMED;

        mavlink_msg_heartbeat_send(
            MAVLINK_DEFAULT_COMM,
            MAV_TYPE_FIXED_WING,
            MAV_AUTOPILOT_GENERIC,
            mav_mode,
            0,
            MAV_STATE_STANDBY
        );

        chThdSleepUntil(time);
    }

    chThdExit(0);
}

THD_FUNCTION(connectionUpdate40Hz, arg) {
	systime_t time = chVTGetSystemTime();

	while (1) {
		time += MS2ST(25);

		vectorData accel = imuAccelGet();
        vectorData gyro = imuGyroGet();
		vectorData mag = imuMagGet();

        mavlink_msg_scaled_imu_send(
			MAVLINK_DEFAULT_COMM,
			gyro.time,
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

        mavlink_msg_attitude_send(
				MAVLINK_DEFAULT_COMM,
				get_rpy().time,
				get_rpy().x,
				get_rpy().y,
				get_rpy().z,
				0,
				0,
				0 );

//        mavlink_msg_attitude_quaternion_send(
//                MAVLINK_DEFAULT_COMM,
//                get_quat().time,
//                get_quat().w,
//                get_quat().x,
//                get_quat().y,
//                get_quat().z,
//                0,
//                0,
//                0 );

        mavlink_msg_scaled_pressure_send(
			MAVLINK_DEFAULT_COMM,
			imuPressureGet().time,
			imuPressureGet().val,
			0,
			imuTempGet().val*100.0f
        );

		mavlink_msg_encoder_output_raw_send(
				MAVLINK_DEFAULT_COMM,
				encoderGet(0).time,
				0,
				encoderGet(0).val,
				encoderGet(1).val,
				encoderGet(2).val,
				encoderGet(3).val,
				encoderGet(4).val,
				encoderGet(5).val,
				encoderGet(6).val,
				encoderGet(7).val,
				encoderGet(8).val );

		mavlink_msg_servo_output_raw_send(
				MAVLINK_DEFAULT_COMM,
				servoGet(0).time,
				0,
				(180.0f+servoGet(0).val)*100,
				(180.0f+servoGet(1).val)*100,
				(180.0f+servoGet(2).val)*100,
				(180.0f+servoGet(3).val)*100,
				(180.0f+servoGet(4).val)*100,
				(180.0f+servoGet(5).val)*100,
				(180.0f+servoGet(6).val)*100,
                (180.0f+servoGet(7).val)*100);

		chThdSleepUntil(time);
    }
}

THD_FUNCTION(connectionSendSettings, arg) {
    for(
        map<string, string>::iterator it = Settings::settings().begin();
        it != Settings::settings().end();
        it++
    ) {
        mavlink_msg_settings_item_send( MAVLINK_DEFAULT_COMM, it->first.substr(0,50).c_str(), it->second.substr(0,50).c_str() );
    }
}

THD_FUNCTION(connectionReceive, arg) {
	mavlink_message_t mavlink_message;
	mavlink_status_t mavlink_status;
	mavlink_mcu_jump_to_t mcu_jump_to;
	char c;
 
	while(1) {
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

                case MAVLINK_MSG_ID_SETTINGS_ITEM: {
                    mavlink_settings_item_t mavlink_settings_item;
                    mavlink_msg_settings_item_decode(&mavlink_message, &mavlink_settings_item);
                    std::string key = std::string(mavlink_settings_item.name);
                    std::string value = std::string(mavlink_settings_item.value);
                    Settings::set( key, value );
                    Settings::sync();
                    mavlink_msg_settings_item_send( MAVLINK_DEFAULT_COMM, key.substr(0,50).c_str(), value.substr(0,50).c_str() );
                } break;

                case MAVLINK_MSG_ID_SETTINGS_REMOVE: {
                    mavlink_settings_remove_t mavlink_settings_remove;
                    mavlink_msg_settings_remove_decode(&mavlink_message, &mavlink_settings_remove);
                    std::string key = std::string(mavlink_settings_remove.name);
                    Settings::remove( key );
                    Settings::sync();
                } break;

				default:
				break;
			}
		}
    }
}

