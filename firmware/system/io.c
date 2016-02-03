#include "io.h"

char buf[ IO_WRITE_BUFFER ];
u32 len;

SerialUSBDriver SDU1;
FATFS sd_filesystem;
bool sd_accessibility = false;
static binary_semaphore_t telemethrySendAccess;
static binary_semaphore_t telemethryReadAccess;


void ioInit(void){
    chBSemObjectInit(&telemethrySendAccess, false);
    chBSemObjectInit(&telemethryReadAccess, false);

	// com port over usb init
	sduObjectInit(&SDU1);
	sduStart(&SDU1, &serusbcfg);

	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(1000);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);

	// sd card and fat file system init
	u32 tries = 3;
	while( sdcConnect(&SDCD1) != HAL_SUCCESS && --tries ) {
		chThdSleepMilliseconds(100);
	}
	if(!tries) return;

	if( f_mount(&sd_filesystem, "", 0 ) == FR_OK ) {
        //TCHAR name[50];
        //DWORD num;

		sd_accessibility = true;
		//print("get label: %u\n\r", f_getlabel ("0", name, &num) );
		//print("name: %s, serialnum: %u\n\r", name, num );
	}
}



void print(const char* string, ...) {
	va_list ap;
	
	va_start( ap, string );
	
	chvprintf((BaseSequentialStream*) &BOARD_USB_DEVICE, string, ap );
	//chvprintf((BaseSequentialStream*) &BOARD_BLUETOOTH_DEVICE, string, ap );
	
	va_end ( ap );
}

void sendToTerminal(const u8* buf, const u32 len) {
	sdWrite( &BOARD_USB_DEVICE, buf, len );
	//sdWrite( &BOARD_BLUETOOTH_DEVICE, buf, len );
}

void receiveFromTerminal(u8* buf, const u32 len) {
	sdRead( &BOARD_USB_DEVICE, buf, len );
	//sdRead( &BOARD_BLUETOOTH_DEVICE, buf, len );
}

u32 availableFromTerminal() {
	return chQSpaceI( &BOARD_USB_DEVICE.oqueue );
	//return chQSpaceI( &BOARD_BLUETOOTH_DEVICE.oqueue );
}




void sendToTelemethry(const u8* buf, const u32 len) {
    chBSemWait(&telemethrySendAccess);
    sdWrite( &BOARD_BLUETOOTH_DEVICE, buf, len );
    //sdWrite( &BOARD_USB_DEVICE, buf, len );
    chBSemSignal(&telemethrySendAccess);
}

void receiveFromTelemethry(u8* buf, const u32 len) {
    chBSemWait(&telemethryReadAccess);
    sdRead( &BOARD_BLUETOOTH_DEVICE, buf, len );
	//sdRead( &BOARD_USB_DEVICE, buf, len );
    chBSemWait(&telemethryReadAccess);
}

u32 availableFromTelemethry(void) {
    return chQSpaceI( &BOARD_BLUETOOTH_DEVICE.oqueue );
	//return chQSpaceI( &BOARD_USB_DEVICE.oqueue );
}



bool sdCardInited(void) {
	return sd_accessibility;
}
