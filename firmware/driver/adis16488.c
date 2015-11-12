#include "adis16488.h"



#define	ADIS_BUFFER_SIZE	100
#define	ADIS_CHIP_SELECT	palClearPad(BOARD_ADIS16488_CS_PORT, BOARD_ADIS16488_CS_PIN)
#define	ADIS_CHIP_DESELECT	palSetPad(BOARD_ADIS16488_CS_PORT, BOARD_ADIS16488_CS_PIN)

#define	ADIS16488_PROD_ID_ADDRESS		0x7E
#define	ADIS16488_PROD_ID				0x4068


static u16 txBuffer[ADIS_BUFFER_SIZE];
static u16 rxBuffer[ADIS_BUFFER_SIZE];
static u32 i;
static thread_t* updateThread;

void adis16488Read( u8 page, u8 address, u32 length, u16* buffer ) {
	// if length > ADIS_BUFFER_SIZE

	//ADIS_CHIP_SELECT;

	// first change page
//	txBuffer[0] = 0x8000 | page;
//	spiExchange( &BOARD_ADIS16488_DEVICE, 1, txBuffer, rxBuffer );

	// read data by 16 bit blocks
	for( i=0; i<length; i++ )
		txBuffer[i] = ( ( address + i*2 ) & 0x7F ) << 8;
	spiExchange( &BOARD_ADIS16488_DEVICE, length+1, txBuffer, rxBuffer );
	for( i=0; i<length; i++ )
		buffer[i] = rxBuffer[i+1];

	#ifdef ADIS16488_DEBUG
	print( "driver/"ADIS16488_NAME"/read: sent:" );
	for( i=0; i<length; i++ )
		print( " 0x%X", txBuffer[i] );
	print( ", received:" );
	for( i=0; i<length+1; i++ )
		print( " 0x%X", rxBuffer[i] );
	print( "\n\r" );
	#endif

	//ADIS_CHIP_DESELECT;
}


void adis16488Write( u8 page, u8 address, u32 length, const u16* buffer ) {
	// if length > ADIS_BUFFER_SIZE*2

	//ADIS_CHIP_SELECT;

	// first change page
//	txBuffer[0] = 0x8000 | page;
//	spiExchange( &BOARD_ADIS16488_DEVICE, 1, txBuffer, rxBuffer );

	// write data by 8 blocks
	for( i=0; i<length; i++ ) {
		txBuffer[i*2] = ( ( ( address + i*2 ) | 0x80 ) << 8 ) | ( buffer[i/2] & 0x00FF );
		txBuffer[i*2+1] = ( ( ( address + i*2 + 1 ) | 0x80 ) << 8 ) | ( ( buffer[i/2] & 0xFF00 ) >> 8 );
	}
	spiExchange( &BOARD_ADIS16488_DEVICE, length*2, txBuffer, rxBuffer );

	#ifdef ADIS16488_DEBUG
	print( "driver/"ADIS16488_NAME"/write: sent:" );
	for( i=0; i<length*2; i++ )
		print( " 0x%X", txBuffer[i] );
	print( "\n\r" );
	#endif

	//ADIS_CHIP_DESELECT;
}


void adis16488Reset(void) {
#ifdef ADIS16488_SOFT_RESET
#else
	palClearPad(BOARD_ADIS16488_RSTI_PORT, BOARD_ADIS16488_RSTI_PIN);
	chThdSleepMilliseconds(200);
	palSetPad(BOARD_ADIS16488_RSTI_PORT, BOARD_ADIS16488_RSTI_PIN);
#endif
}

u8 adis16488TestConnection(void) {
	u16 prodId;
	adis16488Read( 0, ADIS16488_PROD_ID_ADDRESS, 1, &prodId );
	if( prodId != ADIS16488_PROD_ID ) {
		print( "driver/"ADIS16488_NAME"/testConnection: error, test connection failed, response is 0x%X, correct response is 0x%X\n\r", prodId, ADIS16488_PROD_ID );
		return FALSE;
	} else {
		#ifdef ADIS16488_DEBUG
		print( "driver/"ADIS16488_NAME"/testConnection: test connection succeed, response is 0x%X, correct response is 0x%X\n\r", prodId, ADIS16488_PROD_ID );
		#endif
		return TRUE;
	}
}

msg_t adis16488Update(void* arg) {
	systime_t chibios_time = chVTGetSystemTime();

	while (1) {
		chibios_time += MS2ST(ADIS16488_UPDATE_PERIOD);
		{
			u16 buffer[18];
			vectorData vData;
			scalarData sData;

			adis16488Read(0, 0x0E, 18, buffer );
			sData.time = vData.time = chVTGetSystemTime();

			vData.x = -( (float)( (s16) buffer[2] ) )*0.02f;			// out register
			//vData.x += 0.01f/((float)(1<<16))*( (float) buffer[1] );	// low register
			vData.y = -( (float)( (s16) buffer[4] ) )*0.02f;
			//vData.y += 0.01f/((float)(1<<16))*( (float) buffer[3] );
			vData.z = ( (float)( (s16) buffer[6] ) )*0.02f;
			//vData.z += 0.01f/((float)(1<<16))*( (float) buffer[5] );
			imuGyroSet(vData);

			vData.x = -( (float)( (s16) buffer[8] ) )*0.0008f;
			//vData.x += 0.0004f/((float)(1<<16))*( (float) buffer[7] );
			vData.y = -( (float)( (s16) buffer[10] ) )*0.0008f;
			//vData.y += 0.0004f/((float)(1<<16))*( (float) buffer[9] );
			vData.z = ( (float)( (s16) buffer[12] ) )*0.0008f;
			//vData.z += 0.0004f/((float)(1<<16))*( (float) buffer[11] );
			imuAccelSet(vData);

			vData.x = -( (float)( (s16) buffer[13] ) )*0.0001f;
			vData.y = -( (float)( (s16) buffer[14] ) )*0.0001f;
			vData.z = ( (float)( (s16) buffer[15] ) )*0.0001f;
			imuMagSet(vData);

			sData.val = ( (float)( (s16) buffer[17] ) )*0.00004f;
			sData.val += 0.00002f/((float)(1<<16))*( (float) buffer[16] );
			imuPressureSet(sData);

			#ifdef ADIS16488_DEBUG
			print( "gyro: %.3f %.3f %.3f\n\raccel: %.3f %.3f %.3f\n\rmag: %.3f %.3f %.3f\n\rbaro: %.3f\n\rtemp: %.3f\n\r",
				   imu.g.x,imu.g.y,imu.g.z,
				   imu.a.x,imu.a.y,imu.a.z,
				   imu.m.x,imu.m.y,imu.m.z,
				   imu.p.val, imu.T.val );
			#endif
		}

		/*if( chThdShouldTerminateX() )
			chThdExit( 0 );*/
		chThdSleepUntil(chibios_time);
	}
	return 0;
}

void adis16488Init() {
	ADIS_CHIP_SELECT;

	if( !adis16488TestConnection() )
		return;

	updateThread = chThdCreateFromHeap(	NULL,
		THD_WORKING_AREA_SIZE(256),
		HIGHPRIO,
		adis16488Update,
		NULL );

	/*while (TRUE) {
		adis16488Update();
		chThdSleepMilliseconds(500);
	}*/
}
