#include "Connection.h"
#include "Terminal.h"
#include "Settings.h"
#include "Control.h"
#include "imu.h"
#include "encoder.h"
#include "servo.h"
#include "PubSub.h"



static THD_FUNCTION(connectionReceive, arg);
static THD_WORKING_AREA(connectionReceiveWorkingArea, 4096);

static THD_FUNCTION(connectionSendSettings, arg);
static THD_WORKING_AREA(connectionSendSettingsWorkingArea, 4096);


mavlink_system_t                    mavlink_system;


THD_FUNCTION(connectionSendSettings, arg) {
    for(
        map<string, string>::iterator it = Settings::settings().begin();
        it != Settings::settings().end();
        it++
    ) {
        Connection::instance()._mutex.lock();
        mavlink_msg_settings_item_send( MAVLINK_DEFAULT_COMM, it->first.substr(0,50).c_str(), it->second.substr(0,50).c_str() );
        Connection::instance()._mutex.unlock();
    }
    chThdExit(0);
}

THD_FUNCTION(connectionReceive, arg) {
	mavlink_message_t mavlink_message;
	mavlink_status_t mavlink_status;
	mavlink_mcu_jump_to_t mcu_jump_to;
    uint8_t c;

    chRegSetThreadName("Connection receiver");
 
    while( !chThdShouldTerminateX() ) {
        c = Telemetry::get();
        if( mavlink_parse_char(MAVLINK_DEFAULT_COMM, c, &mavlink_message, &mavlink_status) ) {
            switch(mavlink_message.msgid) {
				case MAVLINK_MSG_ID_HEARTBEAT: {
					//control.connection = CONTROL_CONNECTED;
				} break;

                case MAVLINK_MSG_ID_COMMAND_LONG: {
                    mavlink_command_long_t command;
                    mavlink_msg_command_long_decode(&mavlink_message, &command);
                    switch(command.command) {
                        case MAV_CMD_PREFLIGHT_CALIBRATION :
                            if( command.param2 ) {
                                Imu::calibrator().startMagCalibration();
                            } else {
                                Imu::calibrator().stopMagCalibration();
                            }
                            break;
                    }

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
    chThdExit(0);
}




Connection::Connection() {
    mavlink_system.sysid = 0;
    mavlink_system.compid = MAV_COMP_ID_IMU;

    /*thread_t* tread = */chThdCreateStatic(  connectionReceiveWorkingArea,
                        sizeof(connectionReceiveWorkingArea),
                        NORMALPRIO, connectionReceive, NULL);
    //start(NORMALPRIO);
}

Connection::~Connection() {
}

void Connection::valueSend(u32 time, string key, float value) {
    _mutex.lock();
    mavlink_msg_value_send( MAVLINK_DEFAULT_COMM, time, key.substr(0,50).c_str(), value );
    _mutex.unlock();
}

void Connection::vectorValueSend(u32 time, string key, Vector<3> v) {
    _mutex.lock();
    mavlink_msg_vector_value_send( MAVLINK_DEFAULT_COMM, time, key.substr(0,50).c_str(), v(0), v(1), v(2) );
    _mutex.unlock();
}

void Connection::quatValueSend(u32 time, string key, Quaternion<> q) {
    _mutex.lock();
    mavlink_msg_quat_value_send( MAVLINK_DEFAULT_COMM, time, key.substr(0,50).c_str(), q.w(), q.x(), q.y(), q.z() );
    _mutex.unlock();
}

void Connection::setCpuInfo(float cpuUsage, u32 time, u32 threadCount) {
    _mutex.lock();
    mavlink_msg_system_info_send( MAVLINK_DEFAULT_COMM, cpuUsage, time, threadCount );
    _mutex.unlock();
}

void Connection::main() {
    setName( "Connection sender" );
    vectorData mag, accel;
    quaternionData quat;
    while( !shouldTerminate() ) {
        mag = Imu::mag.get();
        accel = Imu::accel.get();

        quat = Imu::getQuat();

        encoderFix();
        Vector<3> encoder;
        Quaternion<> quatEnc;
/* roll  gamma */   encoder(0) = DEG_RAD(encoderGet(0).val);
/* pitch theta */   encoder(1) = DEG_RAD(encoderGet(1).val);
/* yaw   psi */     encoder(2) = DEG_RAD(encoderGet(2).val);
        Vector<3> Euler;

        Euler(1) = asinf( 2*(quat.val.x()*quat.val.y() + quat.val.z()*quat.val.w()) );
        Euler(2) = atan2f( 2*(quat.val.w()*quat.val.y() - quat.val.x()*quat.val.z()), 2*quat.val.w()*quat.val.w() + 2*quat.val.x()*quat.val.x() - 1 );
Vector<3> EulerSharn;
        EulerSharn(1) = asinf(sinf(encoder(1)) * cosf(encoder(2)));
        EulerSharn(2) = asinf(-sinf(encoder(1))*sinf(encoder(2))/cosf(EulerSharn(1)));
        EulerSharn(0) = asinf((sinf(encoder(2)) * cosf(encoder(0)) + cosf(encoder(2)) * cosf(encoder(1)) * sinf(encoder(0)))/cosf(EulerSharn(1)));
        EulerSharn = EulerSharn;
        quatEnc.w() = -cosf( encoder(2)/2.0f )*cosf( encoder(1)/2.0f )*cosf( encoder(0)/2.0f ) - sinf( encoder(2)/2.0f )*sinf( encoder(1)/2.0f )*sinf( encoder(0)/2.0f );
        quatEnc.x() = -cosf( encoder(2)/2.0f )*cosf( encoder(1)/2.0f )*sinf( encoder(0)/2.0f ) + sinf( encoder(2)/2.0f )*sinf( encoder(1)/2.0f )*cosf( encoder(0)/2.0f );
        quatEnc.y() = -cosf( encoder(2)/2.0f )*sinf( encoder(1)/2.0f )*sinf( encoder(0)/2.0f ) + sinf( encoder(2)/2.0f )*cosf( encoder(1)/2.0f )*cosf( encoder(0)/2.0f );
        quatEnc.z() = -cosf( encoder(2)/2.0f )*sinf( encoder(1)/2.0f )*cosf( encoder(0)/2.0f ) - sinf( encoder(2)/2.0f )*cosf( encoder(1)/2.0f )*sinf( encoder(0)/2.0f );
        quatEnc.normalize();
        encoder(2) = encoder(2);
        quatValueSend( quat.time/10, "imu", quat.val );
        quatValueSend( quat.time/10, "enc", quatEnc );
        vectorValueSend( quat.time/10, "encRaw", encoder );
        vectorValueSend( quat.time/10, "encEuler", EulerSharn);
//        valueSend(quat.time/10,"YawImuSh", RAD_DEG(atan2f(sinf(Euler(2)), tanf(Euler(1)))));
        vectorValueSend( mag.time/10, "mag", mag.val );
//        vectorValueSend( accel.time/10, "accel", accel.val );
        sleep(MS2ST(30));
    }
}



//        imuSharnear(1) = acosf(cosf(imuEuler(1)) * cosf(imuEuler(2)));
//        imuSharnear(2) = atan2f(-sinf(imuEuler(2)), tanf(imuEuler(1)));
//        imuSharnear(0) = asinf((cosf(imuEuler(0)) * sinf(imuEuler(2)) + cosf(imuEuler(2)) * sinf(imuEuler(1)) * sinf(imuEuler(0)))/sinf(imuSharnear(1)));
//        EulerSharn(1) = asinf(sinf(SharnData(1)) * cosf(SharnData(2)));
//        EulerSharn(2) = asinf(-sinf(SharnData(1))*sinf(SharnData(2))/cosf(EulerSharn(1)));
//        EulerSharn(0) = asinf((sinf(SharnData(2)) * cosf(SharnData(0)) + cosf(SharnData(2)) * cosf(SharnData(1)) * sinf(SharnData(0)))/sinf(SharnData(1)));
