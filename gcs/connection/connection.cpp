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
    timer->setInterval(1000);
	timer->setSingleShot(true);
	QObject::connect(
		timer,
		SIGNAL(timeout()),
		SLOT(firmwareDisconnect()));

    connect( MainWindow::ui().magStartCalibrationButton, &QPushButton::clicked, this, &Connection::startStopCalibration );

	status = false;
}

Connection::~Connection() {
}

void Connection::startStopCalibration() {
    _magCalibrationStatus = !_magCalibrationStatus;

    mavlink_msg_command_long_send(
        MAVLINK_DEFAULT_COMM,           // channel
        0,                              // target_system
        MAV_COMP_ID_SYSTEM_CONTROL,     // target_component
        MAV_CMD_PREFLIGHT_CALIBRATION,  // command
        0,                              // confirm
        0,                              // param1 Gyro calibration
        _magCalibrationStatus,          // param2 Magnetometer calibration
        0,                              // param3 Ground pressure
        0,                              // param4 Radio calibratio
        0,                              // param5 Accelerometer calibration
        0,                              // param6 Compass/Motor interference calibration
        0 );
    if( _magCalibrationStatus ) {
        MainWindow::ui().magStartCalibrationButton->setText("Click to end calibration.");
        MainWindow::ui().magCalibrationStatusLabel->setText("Calibrating...");
    } else {
        MainWindow::ui().magStartCalibrationButton->setText("Start calibration.");
        MainWindow::ui().magCalibrationStatusLabel->setText("Click to begin calibration.");
    }
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
//    qDebug() << "Connection::jumpToBootloader()";
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
            timer->start();					// reset connection timer

//            qDebug() << "msg" << isConnected();
            if(!isConnected()) firmwareConnect();

            switch(mavlink_message.msgid) {
				case MAVLINK_MSG_ID_HEARTBEAT: {
//                    qDebug() << "heartbeat";

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
                    Plot::instance().addData( "cpuLoad", (double)mavlink_system_info.time/1e3, (double)mavlink_system_info.cpu_usage*100 );
                    MainWindow::ui().cpuLoadValueLabel->setText(
                        QString("<html><head/><body><p><span style=\"font-size:12pt;\">%1</span><span style=\"font-size:12pt; color:#666666;\">%</span></p></body></html>").arg((double)mavlink_system_info.cpu_usage*100));
                } break;

                /*case MAVLINK_MSG_ID_SCALED_IMU: {
					mavlink_scaled_imu_t scaled_imu;
					mavlink_msg_scaled_imu_decode(&mavlink_message, &scaled_imu);
//                    qDebug() << "scaled imu" << scaled_imu.xacc << scaled_imu.yacc << scaled_imu.zacc;
//                    qDebug() << "scaled imu" << scaled_imu.time_boot_ms/1e3;
                    Plot::instance().addData( "ax", (double)scaled_imu.time_boot_ms/1e3, (double)scaled_imu.xacc/1000.0 );
                    Plot::instance().addData( "ay", (double)scaled_imu.time_boot_ms/1e3, (double)scaled_imu.yacc/1000.0 );
                    Plot::instance().addData( "az", (double)scaled_imu.time_boot_ms/1e3, (double)scaled_imu.zacc/1000.0 );
                    Plot::instance().addData( "gx", (double)scaled_imu.time_boot_ms/1e3, (double)scaled_imu.xgyro/1000.0 );
                    Plot::instance().addData( "gy", (double)scaled_imu.time_boot_ms/1e3, (double)scaled_imu.ygyro/1000.0 );
                    Plot::instance().addData( "gz", (double)scaled_imu.time_boot_ms/1e3, (double)scaled_imu.zgyro/1000.0 );
                    Plot::instance().addData( "mx", (double)scaled_imu.time_boot_ms/1e3, (double)scaled_imu.xmag/1000.0 );
                    Plot::instance().addData( "my", (double)scaled_imu.time_boot_ms/1e3, (double)scaled_imu.ymag/1000.0 );
                    Plot::instance().addData( "mz", (double)scaled_imu.time_boot_ms/1e3, (double)scaled_imu.zmag/1000.0 );
                    emit valueVectorReceived( ValueVector::Mag, (double)scaled_imu.xmag/1000.0, (double)scaled_imu.ymag/1000.0, (double)scaled_imu.zmag/1000.0 );
				} break;

                case MAVLINK_MSG_ID_ATTITUDE: {
					mavlink_attitude_t attitude;
					mavlink_msg_attitude_decode(&mavlink_message, &attitude);
//                    qDebug() << "Connection::parseSerial() attitude" << attitude.time_boot_ms/1000.0 << attitude.roll << attitude.pitch << attitude.yaw;
//					emit valueReceived( Value::Roll, attitude.roll );
					MainWindow::ui().imuRollIndicateLabel->setText( QString::number(RAD_DEG(attitude.roll), 'f', 2) );
                    Plot::instance().addData( "imuRoll", attitude.time_boot_ms/1000.0, RAD_DEG(attitude.roll) );
//					emit valueReceived( Value::Pitch, attitude.pitch );
					MainWindow::ui().imuPitchIndicateLabel->setText( QString::number(RAD_DEG(attitude.pitch), 'f', 2) );
                    Plot::instance().addData( "imuPitch", attitude.time_boot_ms/1000.0, RAD_DEG(attitude.pitch) );
//					emit valueReceived( Value::Yaw, attitude.yaw );
					MainWindow::ui().imuYawIndicateLabel->setText( QString::number(RAD_DEG(attitude.yaw), 'f', 2) );
                    Plot::instance().addData( "imuYaw", attitude.time_boot_ms/1000.0, RAD_DEG(attitude.yaw) );
				} break;

                case MAVLINK_MSG_ID_SCALED_PRESSURE: {
                    mavlink_scaled_pressure_t mavlink_scaled_pressure;
                    mavlink_msg_scaled_pressure_decode(&mavlink_message, &mavlink_scaled_pressure);
//                    qDebug() << "sc pr" << mavlink_scaled_pressure.time_boot_ms;
                    emit valueReceived( Value::Pressure, mavlink_scaled_pressure.press_abs );
                    Plot::instance().addData( "pressure", mavlink_scaled_pressure.time_boot_ms/1000.0, mavlink_scaled_pressure.press_abs );
                    Plot::instance().addData( "temperature", mavlink_scaled_pressure.time_boot_ms/1000.0, mavlink_scaled_pressure.temperature/100.0-273.15 );
                } break;

                case MAVLINK_MSG_ID_ATTITUDE_QUATERNION: {
					mavlink_attitude_quaternion_t quaternion;
					mavlink_msg_attitude_quaternion_decode(&mavlink_message, &quaternion);
//                    qDebu☺g() << "Connection::parseSerial() quaternion" << quaternion.q1 << quaternion.q2 << quaternion.q3 << quaternion.q4;
					emit valueReceived( Value::Q0, quaternion.q1);
                    Plot::instance().addData( "imuQ0", quaternion.time_boot_ms/1000.0, quaternion.q1 );
					emit valueReceived( Value::Q1, quaternion.q2);
                    Plot::instance().addData( "imuQ1", quaternion.time_boot_ms/1000.0, quaternion.q2 );
					emit valueReceived( Value::Q2, quaternion.q3);
                    Plot::instance().addData( "imuQ2", quaternion.time_boot_ms/1000.0, quaternion.q3 );
					emit valueReceived( Value::Q3, quaternion.q4);
                    Plot::instance().addData( "imuQ3", quaternion.time_boot_ms/1000.0, quaternion.q4 );
				} break;

                case MAVLINK_MSG_ID_SCALED_PRESSURE: {
					//qDebug() << "scaled pressure";
					mavlink_scaled_pressure_t scaled_pressure;
					mavlink_msg_scaled_pressure_decode(&mavlink_message, &scaled_pressure);
                    Plot::instance().addData( "p", (double)scaled_pressure.time_boot_ms/1e3, (double)scaled_pressure.press_abs );
                    Plot::instance().addData( "T", (double)scaled_pressure.time_boot_ms/1e3, (double)scaled_pressure.temperature/100.0 );
                } break;*/



				case MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW: {
                    //qDebug() << "encoder";
//					mavlink_encoder_output_raw_t raw_encoder;
//					mavlink_msg_encoder_output_raw_decode(&mavlink_message, &raw_encoder);
//                    qDebug() << "encoder" << raw_encoder.time_usec;
//                    Encoders::instance().encoder(1)->addData( (double)raw_encoder.time_usec/1e3, raw_encoder.encoder1_raw);
//                    Encoders::instance().encoder(2)->addData( (double)raw_encoder.time_usec/1e3, raw_encoder.encoder2_raw);
//                    Encoders::instance().encoder(3)->addData( (double)raw_encoder.time_usec/1e3, raw_encoder.encoder3_raw);
//                    Logger::instance().addData("encoder", (double)raw_encoder.time_usec/1e3, {raw_encoder.encoder1_raw, raw_encoder.encoder2_raw, raw_encoder.encoder3_raw} );
//					Encoders::instance().encoder(4)->addData( (double)raw_encoder.time_usec/1e3, raw_encoder.encoder4_raw;
//					Encoders::instance().encoder(5)->addData( (double)raw_encoder.time_usec/1e3, raw_encoder.encoder5_raw);
//					Encoders::instance().encoder(6)->addData( (double)raw_encoder.time_usec/1e3, raw_encoder.encoder6_raw);
//					Encoders::instance().encoder(7)->addData( (double)raw_encoder.time_usec/1e3, raw_encoder.encoder7_raw);
//					Encoders::instance().encoder(8)->addData( (double)raw_encoder.time_usec/1e3, raw_encoder.encoder8_raw);
//					Encoders::instance().encoder(9)->addData( (double)raw_encoder.time_usec/1e3, raw_encoder.encoder9_raw);
				} break;

				case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW: {
//                    qDebug() << "servo";
					mavlink_servo_output_raw_t raw_servo;
					mavlink_msg_servo_output_raw_decode(&mavlink_message, &raw_servo);
//                    qDebug() <<  "servo" << (double)raw_servo.time_usec;
//                    Servos::instance().servo(1)->addData( (double)raw_servo.time_usec/1e3, ((float)raw_servo.servo1_raw)/100.0-180.0 );
//                    Servos::instance().servo(2)->addData( (double)raw_servo.time_usec/1e3, ((float)raw_servo.servo2_raw)/100.0-180.0 );
//                    Servos::instance().servo(3)->addData( (double)raw_servo.time_usec/1e3, ((float)raw_servo.servo3_raw)/100.0-180.0 );
//                    Servos::instance().servo(4)->addData( (double)raw_servo.time_usec/1e3, ((float)raw_servo.servo4_raw)/100.0-180.0 );
//                    Servos::instance().servo(5)->addData( (double)raw_servo.time_usec/1e3, ((float)raw_servo.servo5_raw)/100.0-180.0 );
//                    Servos::instance().servo(6)->addData( (double)raw_servo.time_usec/1e3, ((float)raw_servo.servo6_raw)/100.0-180.0 );
//                    Servos::instance().servo(7)->addData( (double)raw_servo.time_usec/1e3, ((float)raw_servo.servo7_raw)/100.0-180.0 );
//                    Servos::instance().servo(8)->addData( (double)raw_servo.time_usec/1e3, ((float)raw_servo.servo8_raw)/100.0-180.0 );

				} break;

                case MAVLINK_MSG_ID_VALUE:{
                    mavlink_value_t value;
                    mavlink_msg_value_decode(&mavlink_message, &value);
                    Plot::instance().addData( value.key, value.time_usec/1000.0, value.value );
                } break;

                case MAVLINK_MSG_ID_VECTOR_VALUE:{
                    mavlink_vector_value_t vector;
                    mavlink_msg_vector_value_decode(&mavlink_message, &vector);
                    if( QString(vector.key) == QString("mag") && MainWindow::ui().openGLWidget ) {
                        MainWindow::ui().openGLWidget->appendMag( vector.x, vector.y, vector.z );
                    }
                    if( QString(vector.key) == QString("encRaw") ) {
                        MainWindow::ui().encoderRawRollIndicateLabel->setText( QString::number( RAD_DEG(vector.x), 'f', 2) );
                        MainWindow::ui().encoderRawPitchIndicateLabel->setText( QString::number( RAD_DEG(vector.y), 'f', 2) );
                        MainWindow::ui().encoderRawYawIndicateLabel->setText( QString::number( RAD_DEG(vector.z), 'f', 2) );
                        Plot::instance().addData( QString(vector.key)+"Roll", vector.time_usec/1000.0, RAD_DEG(vector.x) );
                        Plot::instance().addData( QString(vector.key)+"Pitch", vector.time_usec/1000.0, RAD_DEG(vector.y) );
                        Plot::instance().addData( QString(vector.key)+"Yaw", vector.time_usec/1000.0, RAD_DEG(vector.z) );
                        Logger::instance().addData(QString(vector.key), vector.time_usec/1000.0, {RAD_DEG(vector.x),  RAD_DEG(vector.y), RAD_DEG(vector.z)} );
                        break;
                    }

                    if( QString(vector.key) == QString("encEuler") ) {
                        MainWindow::ui().encoderRawRollIndicateLabel->setText( QString::number( RAD_DEG(vector.x), 'f', 2) );
                        MainWindow::ui().encoderRawPitchIndicateLabel->setText( QString::number( RAD_DEG(vector.y), 'f', 2) );
                        MainWindow::ui().encoderRawYawIndicateLabel->setText( QString::number( RAD_DEG(vector.z), 'f', 2) );
                        Plot::instance().addData( QString(vector.key)+"Roll", vector.time_usec/1000.0, RAD_DEG(vector.x) );
                        Plot::instance().addData( QString(vector.key)+"Pitch", vector.time_usec/1000.0, RAD_DEG(vector.y) );
                        Plot::instance().addData( QString(vector.key)+"Yaw", vector.time_usec/1000.0, RAD_DEG(vector.z) );
                        Logger::instance().addData(QString(vector.key), vector.time_usec/1000.0, {RAD_DEG(vector.x),  RAD_DEG(vector.y), RAD_DEG(vector.z)} );
                        break;
                    }

                    Plot::instance().addData( QString(vector.key)+"x", vector.time_usec/1000.0, vector.x );
                    Plot::instance().addData( QString(vector.key)+"y", vector.time_usec/1000.0, vector.y );
                    Plot::instance().addData( QString(vector.key)+"z", vector.time_usec/1000.0, vector.z );
                    Plot::instance().addData( QString(vector.key)+"norm", vector.time_usec/1000.0, sqrt( vector.x*vector.x + vector.y*vector.y + vector.z*vector.z ) );
                } break;

                case MAVLINK_MSG_ID_QUAT_VALUE:{
                    mavlink_quat_value_t quat;
                    mavlink_msg_quat_value_decode(&mavlink_message, &quat);

                    double roll = RAD_DEG(atan2( 2*(quat.w*quat.x - quat.y*quat.z), 2*quat.w*quat.w + 2*quat.y*quat.y - 1 ));
                    double pitch = RAD_DEG(asinf( 2*(quat.x*quat.y + quat.z*quat.w) ));
                    double yaw = RAD_DEG(atan2f( 2*(quat.w*quat.y - quat.x*quat.z), 2*quat.w*quat.w + 2*quat.x*quat.x - 1 ));

                    if( QString(quat.key) == "imu" ) {
                        emit valueReceived( Value::Q0, quat.w );
                        emit valueReceived( Value::Q1, quat.x );
                        emit valueReceived( Value::Q2, quat.y );
                        emit valueReceived( Value::Q3, quat.z );

                        MainWindow::ui().imuRollIndicateLabel->setText( QString::number( roll, 'f', 2) );
                        MainWindow::ui().imuPitchIndicateLabel->setText( QString::number( pitch, 'f', 2) );
                        MainWindow::ui().imuYawIndicateLabel->setText( QString::number( yaw, 'f', 2) );
                    } else if( QString(quat.key) == "enc" ) {
                        MainWindow::ui().encoderRollIndicateLabel->setText( QString::number( roll, 'f', 2) );
                        MainWindow::ui().encoderPitchIndicateLabel->setText( QString::number( pitch, 'f', 2) );
                        MainWindow::ui().encoderYawIndicateLabel->setText( QString::number( yaw, 'f', 2) );
                    }
                    Plot::instance().addData( QString(quat.key)+"Qw", quat.time_usec/1000.0, quat.w );
                    Plot::instance().addData( QString(quat.key)+"Qx", quat.time_usec/1000.0, quat.x );
                    Plot::instance().addData( QString(quat.key)+"Qy", quat.time_usec/1000.0, quat.y );
                    Plot::instance().addData( QString(quat.key)+"Qz", quat.time_usec/1000.0, quat.z );
                    Plot::instance().addData( QString(quat.key)+"Roll", quat.time_usec/1000.0, roll );
                    Plot::instance().addData( QString(quat.key)+"Pitch", quat.time_usec/1000.0, pitch );
                    Plot::instance().addData( QString(quat.key)+"Yaw", quat.time_usec/1000.0, yaw );
                    Logger::instance().addData(QString(quat.key), quat.time_usec/1000.0, {quat.w, quat.x, quat.y, quat.z} );
                    Logger::instance().addData(QString(quat.key)+"Euler", quat.time_usec/1000.0, {roll, pitch, yaw} );
                } break;

				case MAVLINK_MSG_ID_POWER_STATUS: {
//                    qDebug() << "servo power status";
					mavlink_power_status_t power_status;
					mavlink_msg_power_status_decode(&mavlink_message, &power_status);
					Servos::instance().powerStausGot( power_status.flags & MAV_POWER_STATUS_SERVO_VALID );

				} break;

                case MAVLINK_MSG_ID_SETTINGS_ITEM: {
                    mavlink_settings_item_t mavlink_settings_item;
                    mavlink_msg_settings_item_decode(&mavlink_message, &mavlink_settings_item);
//                    qDebug() << "Connection::parseSerial() settings item received" << QString(mavlink_settings_item.name) << QString(mavlink_settings_item.value);
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
    status = true;
    MainWindow::ui().signalValueLabel->setText( "<html><head/><body><p><span style=\" font-size:12pt;\">CONNECTED</span></p></body></html>" );
    emit connected();
}

void Connection::firmwareDisconnect() {
    timer->stop();
    status = false;
    MainWindow::ui().signalValueLabel->setText( "<html><head/><body><p><span style=\" font-size:12pt;\">DISCONNECTED</span></p></body></html>" );
}
