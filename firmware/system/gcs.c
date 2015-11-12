#include "gcs.h"




mavlink_system_t mavlink_system;





msg_t gcsReceive(void* var);
msg_t gcsUpdate1Hz(void* var);
msg_t gcsUpdate40Hz(void* var);






void gcsInit(void) {
	mavlink_system.sysid = 0;
	mavlink_system.compid = MAV_COMP_ID_IMU;
	
	chThdCreateFromHeap(	NULL,
							THD_WORKING_AREA_SIZE(256),
							HIGHPRIO,
							gcsUpdate1Hz,
							NULL );
	chThdCreateFromHeap(	NULL,
							THD_WORKING_AREA_SIZE(256),
							NORMALPRIO,
							gcsUpdate40Hz,
							NULL );
	chThdCreateFromHeap(	NULL,
							THD_WORKING_AREA_SIZE(256),
							NORMALPRIO,
							gcsReceive,
							NULL );
}

msg_t gcsUpdate1Hz(void* var) {
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
	return 0;
}


msg_t gcsUpdate40Hz(void* var) {
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

		/*mavlink_msg_scaled_pressure_send(
			MAVLINK_DEFAULT_COMM,
			imuPressureGet().time,
			imuPressureGet().val,
			0,
			imuTempGet().val*100.0f
		);*/

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
	return 0;
}


msg_t gcsReceive(void* var) {
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
					mavlink_msg_mcu_jump_to_decode(&mavlink_message, &mcu_jump_to);
					if( mcu_jump_to.address == MCU_JUMP_TO_BOOTLOADER ) {
						JUMP_TO(BOARD_FLASH_BOOTLOADER);
					}
				} break;

				default:
				break;
			}
		}
	}
	return 0;
}

