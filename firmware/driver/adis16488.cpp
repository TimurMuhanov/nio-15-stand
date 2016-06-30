#include "adis16488.h"
#include "Terminal.h"
#include "Imu.h"


#define ADIS16488_PROD_ID_ADDRESS       0x7e
#define ADIS16488_PROD_ID               0x4068
#define	ADIS_CHIP_SELECT	palClearPad(BOARD_ADIS16488_CS_PORT, BOARD_ADIS16488_CS_PIN)
#define	ADIS_CHIP_DESELECT	palSetPad(BOARD_ADIS16488_CS_PORT, BOARD_ADIS16488_CS_PIN)


Topic<vectorData> Adis::accel;
Topic<vectorData> Adis::gyro;
Topic<vectorData> Adis::mag;
Topic<scalarData> Adis::temp;
Topic<scalarData> Adis::press;


//void adis16488Reset(void) {
//#ifdef ADIS16488_SOFT_RESET
//#else
//	palClearPad(BOARD_ADIS16488_RSTI_PORT, BOARD_ADIS16488_RSTI_PIN);
//	chThdSleepMilliseconds(200);
//	palSetPad(BOARD_ADIS16488_RSTI_PORT, BOARD_ADIS16488_RSTI_PIN);
//#endif
//}

Adis::Adis() {
    start(NORMALPRIO);
}

Adis::~Adis() {
}

Adis& Adis::instance() {
    static Adis instance;
    return instance;
}

char adisName[] = "Adis";

void Adis::main() {
    setName( adisName );
    init();

    systime_t chibios_time = chVTGetSystemTime();

    while( !chThdShouldTerminateX() ) {
        chibios_time += MS2ST(ADIS_UPDATE_PERIOD);

        s16 buffer[18];
        vectorData vData;
        scalarData sData;

        sData.time = vData.time = chVTGetSystemTime();
        read(0, 0x0E, 18, (u16*)buffer );

        sData.val = buffer[0]*0.00565f + 25 + 273.15;
        temp = sData;

        vData.val(0) = -buffer[2]*0.02f;
        vData.val(0) += -buffer[1]*0.02f/(2<<16);
        vData.val(1) = -buffer[4]*0.02f;
        vData.val(1) += -buffer[3]*0.02f/(2<<16);
        vData.val(2) = buffer[6]*0.02f;
        vData.val(2) += buffer[5]*0.02f/(2<<16);
        gyro = vData;

        vData.val(0) = -buffer[8]*0.0008f;
        vData.val(0) += -buffer[7]*0.0008f/(2<<16);
        vData.val(1) = -buffer[10]*0.0008f;
        vData.val(1) += -buffer[9]*0.0008f/(2<<16);
        vData.val(2) = buffer[12]*0.0008f;
        vData.val(2) += buffer[11]*0.0008f/(2<<16);
        accel = vData;

        vData.val(0) = -buffer[13]*0.0001f;
        vData.val(1) = -buffer[14]*0.0001f;
        vData.val(2) = buffer[15]*0.0001f;
        mag = vData;

        sData.val = buffer[17]*0.00004f;
        sData.val += buffer[16]*0.00004f/(2<<16);
        press = sData;

        #ifdef ADIS16488_DEBUG
        print( "gyro: %.3f %.3f %.3f\n\raccel: %.3f %.3f %.3f\n\rmag: %.3f %.3f %.3f\n\rbaro: %.3f\n\rtemp: %.3f\n\r",
               imu.g.x,imu.g.y,imu.g.z,
               imu.a.x,imu.a.y,imu.a.z,
               imu.m.x,imu.m.y,imu.m.z,
               imu.p.val, imu.T.val );
        #endif

//        chThdSleepUntil(chibios_time);

        systime_t delta = chibios_time - chVTGetSystemTime();
        if( chibios_time > chVTGetSystemTime() )
            chThdSleepMilliseconds( ST2MS(delta) );
    }

    chThdExit( 0 );
}

void Adis::init() {
    ADIS_CHIP_SELECT;
    if( !testConnection() )
        return;
}

bool Adis::testConnection() {
    u16 prodId;
    read( 0, ADIS16488_PROD_ID_ADDRESS, 1, &prodId );
    if( prodId != ADIS16488_PROD_ID ) {
        Terminal::print( "driver/ADIS16488/testConnection: error, test connection failed, response is 0x%X, correct response is 0x%X\n\r", prodId, ADIS16488_PROD_ID );
        return FALSE;
    } else {
        #ifdef ADIS16488_DEBUG
        Terminal::print( "driver/"ADIS16488_NAME"/testConnection: test connection succeed, response is 0x%X, correct response is 0x%X\n\r", prodId, ADIS16488_PROD_ID );
        #endif
        return TRUE;
    }
    return false;
}

void Adis::read(u8 page, u8 address, u32 length, u16* buffer) {
    // if length > ADIS_BUFFER_SIZE

    //ADIS_CHIP_SELECT;

    // first change page
    txBuffer[0] = 0x8000 | page;
    spiExchange( &BOARD_ADIS16488_DEVICE, 1, txBuffer, rxBuffer );

    u32 i;
    for( i=0; i<length; i++ )
        txBuffer[i] = ( (( address + 2*i ) & 0x7F) << 8) & 0xFF00;
    txBuffer[i] = 0x0000;
    spiExchange( &BOARD_ADIS16488_DEVICE, length+1, txBuffer, rxBuffer );
    for( i=0; i<length; i++ )
        buffer[i] = rxBuffer[i+1];

    #ifdef ADIS16488_DEBUG
    print( "driver/"ADIS16488_NAME"/read: sent:" );
    for( i=0; i<length+1; i++ )
        print( " 0x%04X", txBuffer[i] );
    print( ", received:" );
    for( i=0; i<length+1; i++ )
        print( " 0x%04X", rxBuffer[i] );
    print( "\n\r" );
    #endif

    //ADIS_CHIP_DESELECT;
}

void Adis::write(u8 page, u8 address, u32 length, const u16* buffer) {
    // if length > ADIS_BUFFER_SIZE*2

    //ADIS_CHIP_SELECT;

    // first change page
    txBuffer[0] = 0x8000 | page;
    spiExchange( &BOARD_ADIS16488_DEVICE, 1, txBuffer, rxBuffer );

    // write data by 8 blocks
    u32 i;
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

