#include "connection.h"
#include "control.h"
#include "encoders.h"
#include "servos.h"
#include "plot.h"
#include "logger.h"
//#include "parameters.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"


mavlink_system_t mavlink_system;


Connection::Connection(QObject *parent) : QObject(parent) {
	mavlink_system.sysid = 1;
	mavlink_system.compid = MAV_COMP_ID_ALL;

	QObject::connect(
		&Serial::instance(),
		SIGNAL(available(const QByteArray&)),
		SLOT(parseSerial(const QByteArray&)) );

	QObject::connect(
		&Serial::instance(),
		SIGNAL(closed()),
		SLOT(firmwareDisconnect()) );

	timer = new QTimer(this);
	timer->setInterval(2000);
	timer->setSingleShot(true);
	QObject::connect(
		timer,
		SIGNAL(timeout()),
		SLOT(firmwareDisconnect()));

	status = false;
}

Connection::~Connection() {
}

bool Connection::isConnected() {
	return	status;
}

void Connection::sendServoOutput(int id, double value) {
	mavlink_msg_command_int_send(
		MAVLINK_DEFAULT_COMM,		// channel
		0,							// target_system
		MAV_COMP_ID_SYSTEM_CONTROL, // target_component
		MAV_FRAME_GLOBAL,			// frame
		MAV_CMD_DO_SET_SERVO,		// command
		0,							// current,
		0,							// autocontinue,
		id,							// servo number
		value,						// angle
		0,
		0,
		0,							// x
		0,							// y
		0);							// z
}

void Connection::sendServoPowerStatus(bool status) {
	/*mavlink_msg_command_int_send(
		MAVLINK_DEFAULT_COMM,		// channel
		0,							// target_system
		MAV_COMP_ID_SERVO1,			// target_component
		MAV_FRAME_GLOBAL,			// frame
		MAV_CMD_POWER_STATUS_SET,	// command
		0,							// current,
		0,							// autocontinue,
		status,						// status
		0,
		0,
		0,
		0,							// x
		0,							// y
		0);							// z*/
}

void Connection::userCodeRun(bool status) {
    mavlink_msg_command_int_send(
		MAVLINK_DEFAULT_COMM,		// channel
		0,							// target_system
		MAV_COMP_ID_SYSTEM_CONTROL, // target_component
		MAV_FRAME_GLOBAL,			// frame
		MAV_CMD_COMPONENT_ARM_DISARM, // command
		0,							// current,
		0,							// autocontinue,
		status,						// p1
		0,							// p2
		0,							// p3
		0,							// p4
		0,							// x
		0,							// y
        0);							// z
}

void Connection::jumpToBootloader() {
    mavlink_msg_mcu_jump_to_send(MAVLINK_DEFAULT_COMM, MCU_JUMP_TO_BOOTLOADER);
}

void Connection::settingsRequest() {
    mavlink_msg_settings_request_send( MAVLINK_DEFAULT_COMM, 0, 0 );
//    qDebug() << "Connection::settingsRequest()";
}

void Connection::settingsSend(std::string key, std::string value) {
    mavlink_msg_settings_item_send( MAVLINK_DEFAULT_COMM, key.substr(0,50).c_str(), value.substr(0,50).c_str() );
    //    qDebug() << "Connection::settingsSend()" << QString::fromStdString( key.substr(0,50) ) <<  QString::fromStdString( value.substr(0,50) );
}

void Connection::settingsRemove(std::string key) {
    mavlink_msg_settings_remove_send( MAVLINK_DEFAULT_COMM, key.substr(0,50).c_str() );
}

void Connection::parseSerial(const QByteArray& data) {
    foreach(char c, data) {
        if(mavlink_parse_char(MAVLINK_DEFAULT_COMM, c, &mavlink_message, &mavlink_status)) {
            switch(mavlink_message.msgid) {
				case MAVLINK_MSG_ID_HEARTBEAT: {
//                    qDebug() << "heartbeat";
					timer->start();					// reset connection timer

					if(!isConnected()) firmwareConnect();

					if( mavlink_msg_heartbeat_get_base_mode( &mavlink_message ) & MAV_MODE_FLAG_SAFETY_ARMED ) {
						emit userCodeRunStatusReceived(false);
					} else {
						emit userCodeRunStatusReceived(true);
					}
				} break;

                case MAVLINK_MSG_ID_SYSTEM_INFO: {
//                    qDebug() << "status";
                    mavlink_system_info_t mavlink_system_info;
                    mavlink_msg_system_info_decode(&mavlink_message, &mavlink_system_info);
//                    qDebug() << "system info " << mavlink_system_info.cpu_usage << mavlink_system_info.usage_time << mavlink_system_info.system_time << mavlink_system_info.thread_count;
                    Plot::instance().addData( "cpuLoad", (double)mavlink_system_info.system_time/10e3, (double)mavlink_system_info.cpu_usage*100 );
                } break;

				case MAVLINK_MSG_ID_SCALED_IMU: {
					mavlink_scaled_imu_t scaled_imu;
					mavlink_msg_scaled_imu_decode(&mavlink_message, &scaled_imu);
//                    qDebug() << "scaled imu" << scaled_imu.xacc << scaled_imu.yacc << scaled_imu.zacc;
                    Plot::instance().addData( "ax", (double)scaled_imu.time_boot_ms/10e3, (double)scaled_imu.xacc/1000.0 );
                    Plot::instance().addData( "ay", (double)scaled_imu.time_boot_ms/10e3, (double)scaled_imu.yacc/1000.0 );
                    Plot::instance().addData( "az", (double)scaled_imu.time_boot_ms/10e3, (double)scaled_imu.zacc/1000.0 );
                    Plot::instance().addData( "gx", (double)scaled_imu.time_boot_ms/10e3, (double)scaled_imu.xgyro/1000.0 );
                    Plot::instance().addData( "gy", (double)scaled_imu.time_boot_ms/10e3, (double)scaled_imu.ygyro/1000.0 );
                    Plot::instance().addData( "gz", (double)scaled_imu.time_boot_ms/10e3, (double)scaled_imu.zgyro/1000.0 );
                    Plot::instance().addData( "mx", (double)scaled_imu.time_boot_ms/10e3, (double)scaled_imu.xmag/1000.0 );
                    Plot::instance().addData( "my", (double)scaled_imu.time_boot_ms/10e3, (double)scaled_imu.ymag/1000.0 );
                    Plot::instance().addData( "mz", (double)scaled_imu.time_boot_ms/10e3, (double)scaled_imu.zmag/1000.0 );
                    emit valueVectorReceived( ValueVector::Mag, (double)scaled_imu.xmag/1000.0, (double)scaled_imu.ymag/1000.0, (double)scaled_imu.zmag/1000.0 );
				} break;

				case MAVLINK_MSG_ID_ATTITUDE: {
					mavlink_attitude_t attitude;
					mavlink_msg_attitude_decode(&mavlink_message, &attitude);
					//qDebug() << "Connection::parseSerial() attitude" << attitude.roll << attitude.pitch << attitude.yaw;
					emit valueReceived( Value::Roll, attitude.roll );
					MainWindow::ui().imuRollIndicateLabel->setText( QString::number(RAD_DEG(attitude.roll), 'f', 2) );
					emit valueReceived( Value::Pitch, attitude.pitch );
					MainWindow::ui().imuPitchIndicateLabel->setText( QString::number(RAD_DEG(attitude.pitch), 'f', 2) );
					emit valueReceived( Value::Yaw, attitude.yaw );
					MainWindow::ui().imuYawIndicateLabel->setText( QString::number(RAD_DEG(attitude.yaw), 'f', 2) );
				} break;

				case MAVLINK_MSG_ID_ATTITUDE_QUATERNION: {
					mavlink_attitude_quaternion_t quaternion;
					mavlink_msg_attitude_quaternion_decode(&mavlink_message, &quaternion);
					//qDebug() << "Connection::parseSerial() quaternion" << quaternion.q1 << quaternion.q2 << quaternion.q3 << quaternion.q4;
					emit valueReceived( Value::Q0, quaternion.q1);
					emit valueReceived( Value::Q1, quaternion.q2);
					emit valueReceived( Value::Q2, quaternion.q3);
					emit valueReceived( Value::Q3, quaternion.q4);
				} break;

                /*case MAVLINK_MSG_ID_SCALED_PRESSURE: {
					//qDebug() << "scaled pressure";
					mavlink_scaled_pressure_t scaled_pressure;
					mavlink_msg_scaled_pressure_decode(&mavlink_message, &scaled_pressure);
                    Plot::instance().addData( "p", (double)scaled_pressure.time_boot_ms/10e3, (double)scaled_pressure.press_abs );
                    Plot::instance().addData( "T", (double)scaled_pressure.time_boot_ms/10e3, (double)scaled_pressure.temperature/100.0 );
                } break;*/

				case MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW: {
                    //qDebug() << "encoder";
					mavlink_encoder_output_raw_t raw_encoder;
					mavlink_msg_encoder_output_raw_decode(&mavlink_message, &raw_encoder);
					//qDebug() << "encoder" << raw_encoder.encoder1_raw;
                    Encoders::instance().encoder(1)->addData( (double)raw_encoder.time_usec/10e3, raw_encoder.encoder1_raw);
                    Encoders::instance().encoder(2)->addData( (double)raw_encoder.time_usec/10e3, raw_encoder.encoder2_raw);
                    Encoders::instance().encoder(3)->addData( (double)raw_encoder.time_usec/10e3, raw_encoder.encoder3_raw);

                    Logger::instance().addData("encoder", (double)raw_encoder.time_usec/10e3, {raw_encoder.encoder1_raw, raw_encoder.encoder2_raw, raw_encoder.encoder3_raw} );
//					Encoders::instance().encoder(4)->addData( (double)raw_encoder.time_usec/10e3, raw_encoder.encoder4_raw;
//					Encoders::instance().encoder(5)->addData( (double)raw_encoder.time_usec/10e3, raw_encoder.encoder5_raw);
//					Encoders::instance().encoder(6)->addData( (double)raw_encoder.time_usec/10e3, raw_encoder.encoder6_raw);
//					Encoders::instance().encoder(7)->addData( (double)raw_encoder.time_usec/10e3, raw_encoder.encoder7_raw);
//					Encoders::instance().encoder(8)->addData( (double)raw_encoder.time_usec/10e3, raw_encoder.encoder8_raw);
//					Encoders::instance().encoder(9)->addData( (double)raw_encoder.time_usec/10e3, raw_encoder.encoder9_raw);
				} break;

				case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW: {
                    //qDebug() << "servo";
					mavlink_servo_output_raw_t raw_servo;
					mavlink_msg_servo_output_raw_decode(&mavlink_message, &raw_servo);
                    //qDebug() << (double)raw_servo.time_usec/10e3 << ((float)raw_servo.servo1_raw)/100.0-180.0;
                    Servos::instance().servo(1)->addData( (double)raw_servo.time_usec/10e3, ((float)raw_servo.servo1_raw)/100.0-180.0 );
                    Servos::instance().servo(2)->addData( (double)raw_servo.time_usec/10e3, ((float)raw_servo.servo2_raw)/100.0-180.0 );
                    Servos::instance().servo(3)->addData( (double)raw_servo.time_usec/10e3, ((float)raw_servo.servo3_raw)/100.0-180.0 );
                    Servos::instance().servo(4)->addData( (double)raw_servo.time_usec/10e3, ((float)raw_servo.servo4_raw)/100.0-180.0 );
                    Servos::instance().servo(5)->addData( (double)raw_servo.time_usec/10e3, ((float)raw_servo.servo5_raw)/100.0-180.0 );
//                    Servos::instance().servo(6)->addData( (double)raw_servo.time_usec/10e3, ((float)raw_servo.servo6_raw)/100.0-180.0 );
//                    Servos::instance().servo(7)->addData( (double)raw_servo.time_usec/10e3, ((float)raw_servo.servo7_raw)/100.0-180.0 );
//                    Servos::instance().servo(8)->addData( (double)raw_servo.time_usec/10e3, ((float)raw_servo.servo8_raw)/100.0-180.0 );

				} break;

				case MAVLINK_MSG_ID_POWER_STATUS: {
					//qDebug() << "servo power status";
					mavlink_power_status_t power_status;
					mavlink_msg_power_status_decode(&mavlink_message, &power_status);
					Servos::instance().powerStausGot( power_status.flags & MAV_POWER_STATUS_SERVO_VALID );

				} break;

                case MAVLINK_MSG_ID_SETTINGS_ITEM: {
                    mavlink_settings_item_t mavlink_settings_item;
                    mavlink_msg_settings_item_decode(&mavlink_message, &mavlink_settings_item);
                    //qDebug() << "Connection::parseSerial() settings item received" << QString(mavlink_settings_item.name) << QString(mavlink_settings_item.value);
                    emit settingReceived( std::string(mavlink_settings_item.name), std::string(mavlink_settings_item.value) );
                } break;

                case MAVLINK_MSG_ID_SETTINGS_REMOVE: {
                    mavlink_settings_remove_t mavlink_settings_remove;
                    mavlink_msg_settings_remove_decode(&mavlink_message, &mavlink_settings_remove);
                    //qDebug() << "Connection::parseSerial() settings item remoce" << QString(mavlink_settings_item.name);
                    emit settingRemoved( std::string( mavlink_settings_remove.name ) );
                } break;

				default: break;
			}
		}
	}
}

void Connection::firmwareConnect() {
	MainWindow::ui().signalIconLabel->setPixmap(QPixmap(":/icon/img/signal_4.png"));
	MainWindow::ui().signalValueLabel->setText(
		QString("<html><head/><body><p><span style=\"font-size:12pt;\">%1</span><span style=\"font-size:12pt; color:#666666;\">%</span></p></body></html>").arg(100));
	status = true;
	emit connected();
	qDebug() << "connected";
}

void Connection::firmwareDisconnect() {
	timer->stop();
	MainWindow::ui().signalIconLabel->setPixmap(QPixmap(":/icon/img/signal_lost.png"));
	MainWindow::ui().signalValueLabel->setText(
		QString("<html><head/><body><p><span style=\"font-size:12pt;\">%1</span><span style=\"font-size:12pt; color:#666666;\">%</span></p></body></html>").arg(0));
	status = false;
	emit disconnected();
	qDebug() << "disconnected";
}
