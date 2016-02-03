#include "ch.h"
#include "hal.h"

#include "io.h"
#include "flash.h"

thread_t* blinkerThread;
static THD_FUNCTION(blinkerUpdate, arg);
static THD_WORKING_AREA(blinkerUpdateWorkingArea, 256);
u8 rx_buffer[5];
u8 tx_buffer[1];
u32 begin;

#define ACK             	0x79
#define NACK            	0x1F
#define CMD_CONNECT     	0x7F
#define CMD_GO        	 	0x21
#define CMD_WRITE      		0x31
#define CMD_ERASE      		0x44
#define TIMEOUT				MS2ST(400)
#define TRIES				3

#define SEND_ACK			tx_buffer[0] = ACK; \
							sdWriteTimeout( &BOARD_BLUETOOTH_DEVICE, tx_buffer, 1, TIMEOUT );
#define SEND_NACK			tx_buffer[0] = NACK; \
							sdWriteTimeout( &BOARD_BLUETOOTH_DEVICE, tx_buffer, 1, TIMEOUT );

bool	getConnection(void) {
	u32 bytesRed, tries = TRIES;

	if( *((__IO u32*) BOARD_FLASH_FIRMWARE ) == 0xFFFFFFFF )
		tries = 0xFFFFFFFF;
	while(tries--) {
		//print("getConnection: tries %u\n\r", tries);
		bytesRed = 0;
		bytesRed = sdReadTimeout( &BOARD_BLUETOOTH_DEVICE, rx_buffer, 1, TIMEOUT );
		//print("getConnection: red %u 0x%02X\n\r", bytesRed, rx_buffer[0]);
		if( bytesRed == 1 ) {
			if( rx_buffer[0] == CMD_CONNECT ) {
				SEND_ACK
				//print("getConnection: ack\n\r");
				return true;
			} else {
				SEND_NACK
				//print("getConnection: nack\n\r");
			}
		}
	}
	//print("getConnection: timeout\n\r");
	return false;
}

u8	getCommand(void) {
	u32 bytesRed, tries = TRIES;

	while(tries--) {
		//print("getCommand: tries %u\n\r", tries);
		bytesRed = sdReadTimeout( &BOARD_BLUETOOTH_DEVICE, rx_buffer, 2, TIMEOUT );
		if( bytesRed == 2 ) {
			if( rx_buffer[0]+rx_buffer[1] == 0xFF ) {
				SEND_ACK
				//print("getCommand: 0x%02X[0x%02X] ack\n\r", rx_buffer[0], rx_buffer[1]);
				return rx_buffer[0];
			} else {
				SEND_NACK
				//print("getCommand: 0x%02X[0x%02X] nack\n\r", rx_buffer[0], rx_buffer[1]);
			}
		}
	}
	//print("getCommand: timeout\n\r");
	return 0x00;
}

bool	get(u8 num) {
	u32 bytesRed, tries = TRIES;
	u8 i, checksum;

	while(tries--) {
		//print("get: tries %u\n\r", tries);
		for(i=0; i<num+1; i++) rx_buffer[i] = 0;
		//print("get: num %u\n\r", num+1);
		bytesRed = sdReadTimeout( &BOARD_BLUETOOTH_DEVICE, rx_buffer, num+1, TIMEOUT);
		//print("get: red %u\n\r", bytesRed);
		if( bytesRed == (u32)num+1 ) {
			checksum = 0x00;
			//print("get: red:");
			for(i=0; i<num; i++) {
				//print(" 0x%02X", rx_buffer[i]);
				checksum ^= rx_buffer[i];
			}
			//print("\n\r");
			//print("checksum 0x%02X\n\r", checksum);

			if( checksum == rx_buffer[num] ) {
				//print("get: ack\n\r");
				return true;
			} else {
				SEND_NACK
				//print("get: nack\n\r");
			}
		}
	}
	//print("get: timeout\n\r");
	return false;
}


THD_FUNCTION(blinkerUpdate, arg) {
    while( !chThdShouldTerminateX() ) {
        palTogglePad(GPIOC, 15);
        chThdSleepMilliseconds(50);
    }
    chThdExit( 0 );
}

int main(void) {
	halInit();
	chSysInit();

    palSetPadMode(GPIOC, 15, PAL_MODE_OUTPUT_PUSHPULL);         // blue
    palClearPad(GPIOC, 15);
    palSetPadMode(GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL);         // red
    palClearPad(GPIOC, 13);
    palSetPadMode(GPIOC, 0, PAL_MODE_OUTPUT_PUSHPULL);          // orange
    palClearPad(GPIOC, 0);

    blinkerThread = chThdCreateStatic(  blinkerUpdateWorkingArea,
                                        sizeof(blinkerUpdateWorkingArea),
                                        NORMALPRIO, blinkerUpdate, NULL);

    ioInit();

	// waiting for connection
	if( getConnection() ) {
		//print("connected\n\r");

		flashUnlock();

		while( 1 ) {
			switch( getCommand() ) {
				case CMD_ERASE:
					//print("command erase\n\r");
					if( get(2) ) {
						print("command erase: full\n\r");
						flashEraseFirmware();
						print("command erase: complete\n\r");
						while( sdAsynchronousRead( &BOARD_BLUETOOTH_DEVICE, rx_buffer, 1) );
						print("command erase: ack\n\r");
                        SEND_ACK
					}
					break;
				case CMD_WRITE:
					//print("command write\n\r");
					if( get(4) ) {
                        SEND_ACK
						u32 address =	((rx_buffer[0]<<24) & 0xFF000000) |
										((rx_buffer[1]<<16) & 0x00FF0000) |
										((rx_buffer[2]<<8) & 0x0000FF00) |
										((rx_buffer[3]) & 0x000000FF);
						//print("command write: address is 0x%08X\n\r",address);

						u8 crc, len, checksum = 0;
						u8 data[128] = {0};
						u32 index = 0;
						sdRead( &BOARD_BLUETOOTH_DEVICE, &len, 1);
						checksum ^= len;
						//print("command write: len %u\n\r", len );
						while(index<len) {
							sdRead( &BOARD_BLUETOOTH_DEVICE, data+index, 1);
							//print("command write: received %u 0x%02X\n\r", index, data[index] );
							checksum ^= data[index];
							index++;
						}
						sdRead( &BOARD_BLUETOOTH_DEVICE, &crc, 1);
						if( checksum == crc ) {
							if( address == BOARD_FLASH_FIRMWARE ) {
								begin = ((data[0]) & 0x000000FF) |
										((data[1]<<8) & 0x0000FF00) |
										((data[2]<<16) & 0x00FF0000) |
										((data[3]<<24) & 0xFF000000);
								flashWrite( address+4, (u32*)(data+4), len/4-1 );
							} else {
								flashWrite( address, (u32*)data, len/4 );
							}
                            SEND_ACK
							//print("command write: ack\n\r");
						} else {
                            SEND_NACK
							//print("command write: nack\n\r");
						}
						//print("command write: complete\n\r");
					}
					break;
				case CMD_GO:
					flashWrite( BOARD_FLASH_FIRMWARE, (u32*)&begin, 1 );
					flashLock();
                    chThdTerminate( blinkerThread );
					chThdSleepMilliseconds(100);
					JUMP_TO(BOARD_FLASH_FIRMWARE);
					break;
			}
		}
    }

    chThdTerminate( blinkerThread );
	chThdSleepMilliseconds(100);
	JUMP_TO(BOARD_FLASH_FIRMWARE);

	while(1) {
		chThdSleepMilliseconds(1000);
        palTogglePad(GPIOC, 0);
	}
}
