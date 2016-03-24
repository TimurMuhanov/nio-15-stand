#include "io.h"

char buf[ IO_WRITE_BUFFER ];
u32 len;

SerialUSBDriver SDU1;


void ioInit(void){

	// com port over usb init
	sduObjectInit(&SDU1);
	sduStart(&SDU1, &serusbcfg);

	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(1000);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);

    Telemetry::instance();
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
    return chQSpaceI( &BOARD_USB_DEVICE.iqueue );
    //return chQSpaceI( &BOARD_BLUETOOTH_DEVICE.iqueue );
}



FATFS FileSystem::_filesystem;
bool FileSystem::_accessibility = false;
binary_semaphore_t FileSystem::_access;


FileSystem::FileSystem() {}

FileSystem::~FileSystem() {}

void FileSystem::init() {
    chBSemObjectInit( &_access, false );

    // sd card and fat file system init
    u32 tries = 3;
    while( sdcConnect(&SDCD1) != HAL_SUCCESS && --tries ) {
        chThdSleepMilliseconds(100);
    }
    if(!tries) return;

    if( f_mount(&_filesystem, "", 0 ) == FR_OK ) {
        //TCHAR name[50];
        //DWORD num;

        _accessibility = true;
        //print("get label: %u\n\r", f_getlabel ("0", name, &num) );
        //print("name: %s, serialnum: %u\n\r", name, num );
    }
}

bool FileSystem::isAvailable() {
    return _accessibility;
}

bool FileSystem::open( FIL& fil, const string& file, const u8 mode ) {
    if( !isAvailable() )
        return false;

    /*BYTE f_mode = 0;
    if( permission & Permission::Read )
        f_mode |= FA_READ;
    if( permission & Permission::Write )
        f_mode |= FA_WRITE;

    if( mode & Mode::OpenExisting )
        f_mode |= FA_OPEN_EXISTING;
    if( mode & Mode::OpenAlways )
        f_mode |= FA_OPEN_ALWAYS;
    if( mode & Mode::CreateNew )
        f_mode |= FA_CREATE_NEW;
    if( mode & Mode::CreateAlways )
        f_mode |= FA_CREATE_ALWAYS;*/

    return f_open( &fil, file.c_str(), mode) == FR_OK;
}

bool FileSystem::write(FIL& fil, const string& data) {
    if( !isAvailable() )
        return false;

    return write( fil, (const u8*) data.c_str(), data.length() );
}

bool FileSystem::write(FIL& fil, const u8* data, const u32 len) {
    if( !isAvailable() )
        return false;

    UINT res;
    chBSemWait(&_access);
    bool result = f_write( &fil, data, len, &res ) == FR_OK;
    chBSemSignal(&_access);
    return result;
}

bool FileSystem::readLine( FIL& fil, string& line ) {
    if( !isAvailable() )
        return false;

    TCHAR buffer[255];
    if( f_gets( (TCHAR*) buffer, 255, &fil ) != NULL) {
        line = string(buffer);
        return true;
     } else {
        return false;
    }
}

bool FileSystem::sync( FIL& fil ) {
    if( !isAvailable() )
        return false;
    chBSemWait(&_access);
    bool syn = f_sync( &fil );
    chBSemSignal(&_access);

    return syn;
}

bool FileSystem::erase( FIL& fil ) {
    if( !isAvailable() )
        return false;

    if( f_lseek( &fil, 0 ) != FR_OK )
        return false;
    return f_truncate( &fil ) == FR_OK;
}
