#include "ls7366.h"


#define	LS7366_CHIP_SELECT(pin)		palClearPad(BOARD_LS7366R_ESS_PORT, pin)
#define	LS7366_CHIP_DESELECT(pin)	palSetPad(BOARD_LS7366R_ESS_PORT, pin)

/// MDR0 configuration data; any of these data segments can be ORed together
// Count modes
#define MDR0_MODE_NOQUAD		0x00	// non-quadrature mode
#define MDR0_MODE_QUADX1		0x01	// X1 quadrature mode
#define MDR0_MODE_QUADX2		0x02	// X2 quadrature mode
#define MDR0_MODE_QUADX4		0x03	// X4 quadrature mode

// Running modes
#define MDR0_RMODE_FREE_RUN		0x00
#define MDR0_RMODE_SINGE_CYCLE 	0x04
#define MDR0_RMODE_RANGE_LIMIT 	0x08
#define MDR0_RMODE_MODULO_N		0x0C
// Index modes
#define MDR0_INDEX_DISABLE		0x00	// index disabled
#define MDR0_INDEX_LOAD_CNTR	0x10	// load DTR to CNTR when index
#define MDR0_INDEX_RESET_CNTR	0x20	// reset CNTR when index
#define MDR0_INDEX_LOAD_OTR		0x30	// load CNTR to OTR when index

#define MDR0_INDEX_ASYNCH		0x00	// asynchronous index
#define MDR0_INDEX_SYNCH		0x80	// synchronous index

// Clock filter modes
#define MDR0_FILTER_1			0x00	// filter clock frequncy division factor 1
#define MDR0_FILTER_2			0x80	// filter clock frequncy division factor 2


/// MDR1 configuration data; any of these data segments can be ORed together
// Flag modes
#define MDR1_FLAG_NO			0x00	// all flags disabled
#define MDR1_FLAG_IDX			0x10	// IDX flag
#define MDR1_FLAG_CMP			0x20	// CMP flag
#define MDR1_FLAG_BW			0x40	// BW flag
#define MDR1_FLAG_CY			0x80	// CY flag
// 1 to 4 bytes data-width
#define MDR1_BYTE_4				0x00	// four byte mode
#define MDR1_BYTE_3				0x01	// three byte mode
#define MDR1_BYTE_2				0x02	// two byte mode
#define MDR1_BYTE_1				0x03	// one byte mode
// Enable/disable counter
#define MDR1_CNTR_EN			0x00	// counting enabled
#define MDR1_CNTR_DIS			0x04	// counting disabled


#define REG_MDR0				(1<<3)
#define REG_MDR1				(2<<3)
#define REG_DTR					(3<<3)
#define REG_CNTR				(4<<3)
#define REG_OTR					(5<<3)
#define REG_STR					(6<<3)

#define CMD_CLEAR				(0<<6)
#define CMD_READ				(1<<6)
#define CMD_WRITE				(2<<6)
#define CMD_LOAD				(3<<6)




u8 byte_mode;
u8 rxBuffer[5];
u8 txBuffer[5];




u16 ls7366NumberToPin(u8 encoderNumber) {
	switch(encoderNumber) {
	case 1:
		return BOARD_LS7366R_ESS1_PIN;
	case 2:
		return BOARD_LS7366R_ESS2_PIN;
	case 3:
		return BOARD_LS7366R_ESS3_PIN;
	case 4:
		return BOARD_LS7366R_ESS4_PIN;
	case 5:
		return BOARD_LS7366R_ESS5_PIN;
	case 6:
		return BOARD_LS7366R_ESS6_PIN;
	case 7:
		return BOARD_LS7366R_ESS7_PIN;
	case 8:
		return BOARD_LS7366R_ESS8_PIN;
	case 9:
		return BOARD_LS7366R_ESS9_PIN;
	default:
		return BOARD_LS7366R_ESS1_PIN;
	}
}




void ls7366Clear( const u8 encoderNumber, const u8 reg ) {
	txBuffer[0] = reg | CMD_CLEAR;
	
	spiAcquireBus(&BOARD_LS7366R_DEVICE);
	LS7366_CHIP_SELECT( ls7366NumberToPin( encoderNumber ) );
	spiSend( &BOARD_LS7366R_DEVICE, 1, txBuffer );
	LS7366_CHIP_DESELECT( ls7366NumberToPin( encoderNumber ) );
	spiReleaseBus(&BOARD_LS7366R_DEVICE);
}




void ls7366Read( const u8 encoderNumber, const u8 reg, u8* data ) {
	txBuffer[0] = reg | CMD_READ;
	txBuffer[1] = 0;
	u8 i;
	
	switch(reg) {
		case REG_MDR0:
		case REG_MDR1:
		case REG_STR:
			spiAcquireBus(&BOARD_LS7366R_DEVICE);
			LS7366_CHIP_SELECT( ls7366NumberToPin( encoderNumber ) );
			spiExchange( &BOARD_LS7366R_DEVICE, 2, txBuffer, rxBuffer );
			LS7366_CHIP_DESELECT( ls7366NumberToPin( encoderNumber ) );
			spiReleaseBus(&BOARD_LS7366R_DEVICE);
			data[0] = rxBuffer[1];
		break;
		case REG_DTR:
		case REG_CNTR:
		case REG_OTR:
			spiAcquireBus(&BOARD_LS7366R_DEVICE);
			LS7366_CHIP_SELECT( ls7366NumberToPin( encoderNumber ) );
			spiExchange( &BOARD_LS7366R_DEVICE, byte_mode+1, txBuffer, rxBuffer );
			LS7366_CHIP_DESELECT( ls7366NumberToPin( encoderNumber ) );
			spiReleaseBus(&BOARD_LS7366R_DEVICE);
			for( i=0; i<byte_mode; i++) data[i] = rxBuffer[i+1];
		break;
	}
}




void ls7366Write( const u8 encoderNumber, const u8 reg, const u8* data ) {
	txBuffer[0] = reg | CMD_WRITE;
	u8 i;
	
	switch(reg) {
		case REG_MDR0:
		case REG_MDR1:
		case REG_STR:
			txBuffer[1] = data[0];
			spiAcquireBus(&BOARD_LS7366R_DEVICE);
			LS7366_CHIP_SELECT( ls7366NumberToPin( encoderNumber ) );
			spiSend( &BOARD_LS7366R_DEVICE, 2, txBuffer );
			LS7366_CHIP_DESELECT( ls7366NumberToPin( encoderNumber ) );
			spiReleaseBus(&BOARD_LS7366R_DEVICE);
		break;
		case REG_DTR:
		case REG_CNTR:
		case REG_OTR:
			for( i=0; i<byte_mode; i++) txBuffer[i+1] = data[i];
			spiAcquireBus(&BOARD_LS7366R_DEVICE);
			LS7366_CHIP_SELECT( ls7366NumberToPin( encoderNumber ) );
			spiSend( &BOARD_LS7366R_DEVICE, byte_mode+1, txBuffer );
			LS7366_CHIP_DESELECT( ls7366NumberToPin( encoderNumber ) );
			spiReleaseBus(&BOARD_LS7366R_DEVICE);
		break;
	}
}




void ls7366Load( const u8 encoderNumber, const u8 reg ) {
	txBuffer[0] = reg | CMD_LOAD;
	
	spiAcquireBus(&BOARD_LS7366R_DEVICE);
	LS7366_CHIP_SELECT( ls7366NumberToPin( encoderNumber ) );
	spiSend( &BOARD_LS7366R_DEVICE, 1, txBuffer );
	LS7366_CHIP_DESELECT( ls7366NumberToPin( encoderNumber ) );
	spiReleaseBus(&BOARD_LS7366R_DEVICE);
}





void ls7366Init(u8 encoderNumber) {
	u8 reg;

	// enable output form LS7366 in MC74VHC1GT125
	palClearPad( BOARD_LS7366R_CS2_PORT, BOARD_LS7366R_CS2_PIN );

	// reset register values
	ls7366Clear(encoderNumber, REG_MDR0);
	ls7366Clear(encoderNumber, REG_MDR1);
	ls7366Clear(encoderNumber, REG_CNTR);
	ls7366Clear(encoderNumber, REG_STR);
	
	// configure MDR0 (Mode Register 0)
	// @fixme inverted index signal
	//if( encoderNumber == 1 || encoderNumber == 2 )
		//reg = MDR0_MODE_QUADX1 | MDR0_RMODE_FREE_RUN | MDR0_INDEX_LOAD_OTR | MDR0_INDEX_ASYNCH | MDR0_FILTER_1;
	//else
		//reg = MDR0_MODE_QUADX1 | MDR0_RMODE_FREE_RUN | MDR0_INDEX_RESET_CNTR | MDR0_INDEX_ASYNCH | MDR0_FILTER_1;
		reg = MDR0_MODE_QUADX1 | MDR0_RMODE_FREE_RUN | MDR0_INDEX_DISABLE | MDR0_INDEX_ASYNCH | MDR0_FILTER_1;
	ls7366Write(encoderNumber, REG_MDR0, &reg);
	
	// configure MDR1 (Mode Register 1)
	reg = MDR1_BYTE_4 | MDR1_FLAG_NO | MDR1_CNTR_EN;
	ls7366Write(encoderNumber, REG_MDR1, &reg);
	byte_mode = 4 - MDR1_BYTE_4;

	/*while(1) {
		//ls7366Load(encoderNumber, REG_OTR);
		//ls7366Read(encoderNumber, REG_OTR, (u8*) &cntr);
		//print("CNTR 0x%X\n\r", cntr);
		ls7366Read(encoderNumber, REG_STR, &reg);
		if(reg&0x80)
			print("CY |", reg);
		else
			print("   |", reg);
		if(reg&0x40)
			print(" BW |", reg);
		else
			print("    |", reg);
		if(reg&0x20)
			print(" CM |", reg);
		else
			print("    |", reg);
		if(reg&0x10)
			print(" IX |", reg);
		else
			print("    |", reg);
		if(reg&0x08)
			print(" CE |", reg);
		else
			print("    |", reg);
		if(reg&0x04)
			print(" PW |", reg);
		else
			print("    |", reg);
		if(reg&0x02)
			print(" DI |", reg);
		else
			print("    |", reg);
		if(reg&0x01)
			print(" SI\n\r", reg);
		else
			print("   \n\r", reg);
		print("0x%X \n\r", STM32_PCLK1);
		ls7366Clear(encoderNumber, REG_STR);
		chThdSleepMilliseconds(100);
	}*/
}




u32 ls7366Fix() {
	// @fixme inverted index signal
	//u8 reg;
	//ls7366Read(1, REG_STR, &reg);
	//print("sr 0x%X\n\r", reg );
	/*if(reg&0x10)
		ls7366Clear(1, REG_CNTR);
	ls7366Clear(1, REG_STR);
	ls7366Read(2, REG_STR, &reg);
	if(reg&0x10)
		ls7366Clear(2, REG_CNTR);
	ls7366Clear(2, REG_STR);*/

	LS7366_CHIP_SELECT( ls7366NumberToPin( 1 ) );
	LS7366_CHIP_SELECT( ls7366NumberToPin( 2 ) );
	LS7366_CHIP_SELECT( ls7366NumberToPin( 3 ) );
	LS7366_CHIP_SELECT( ls7366NumberToPin( 4 ) );
	LS7366_CHIP_SELECT( ls7366NumberToPin( 5 ) );
	LS7366_CHIP_SELECT( ls7366NumberToPin( 6 ) );
	LS7366_CHIP_SELECT( ls7366NumberToPin( 7 ) );
	LS7366_CHIP_SELECT( ls7366NumberToPin( 8 ) );
	LS7366_CHIP_SELECT( ls7366NumberToPin( 9 ) );
	spiAcquireBus(&BOARD_LS7366R_DEVICE);
	txBuffer[0] = REG_OTR | CMD_LOAD;
	spiSend( &BOARD_LS7366R_DEVICE, 1, txBuffer );
	u32 time = chVTGetSystemTime();
	spiReleaseBus(&BOARD_LS7366R_DEVICE);
	LS7366_CHIP_DESELECT( ls7366NumberToPin( 1 ) );
	LS7366_CHIP_DESELECT( ls7366NumberToPin( 2 ) );
	LS7366_CHIP_DESELECT( ls7366NumberToPin( 3 ) );
	LS7366_CHIP_DESELECT( ls7366NumberToPin( 4 ) );
	LS7366_CHIP_DESELECT( ls7366NumberToPin( 5 ) );
	LS7366_CHIP_DESELECT( ls7366NumberToPin( 6 ) );
	LS7366_CHIP_DESELECT( ls7366NumberToPin( 7 ) );
	LS7366_CHIP_DESELECT( ls7366NumberToPin( 8 ) );
	LS7366_CHIP_DESELECT( ls7366NumberToPin( 9 ) );
	return time;
}





s32 ls7366ReadCounter(u8 encoderNumber) {
	u8 data[4] = {0,0,0,0};

	ls7366Read( encoderNumber, REG_OTR, data );
	
	return (s32) (u32) data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
	}
