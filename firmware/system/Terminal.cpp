#include "Terminal.h"
#include "Telemetry.h"

SerialUSBDriver                     SDU1;

Terminal::Terminal() {
    // com port over usb init
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);
}

Terminal::~Terminal() {

}

Terminal&Terminal::instance() {
    static Terminal instance;
    return instance;
}

void Terminal::print(const char* string, ...) {
    va_list ap;

    va_start( ap, string );

    instance()._sendMutex.lock();
//    chvprintf((BaseSequentialStream*) &BOARD_BLUETOOTH_DEVICE, string, ap );
    chvprintf((BaseSequentialStream*) &BOARD_USB_DEVICE, string, ap );
    instance()._sendMutex.unlock();

    va_end ( ap );
}

u32 Terminal::send(const u8* buf, const u32 len) {
    instance()._sendMutex.lock();
    u32 res = sdWrite( &BOARD_USB_DEVICE, buf, len );
    instance()._sendMutex.unlock();
    return res;
}

u32 Terminal::read(u8* buf, const u32 len) {
    instance()._receiveMutex.lock();
    u32 res = sdRead( &BOARD_USB_DEVICE, buf, len );
    instance()._receiveMutex.unlock();
    return res;

}

u32 Terminal::available() {
    instance()._sendMutex.lock();
    u32 res =  chQSpaceI( &BOARD_USB_DEVICE.oqueue );
    instance()._sendMutex.unlock();
    return res;
}

u8 Terminal::get() {
    instance()._receiveMutex.lock();
    u8 res = sdGet( &BOARD_USB_DEVICE );
    instance()._receiveMutex.unlock();
    return res;
}

void Terminal::put(u8 byte) {
    instance()._sendMutex.lock();
    sdPut( &BOARD_USB_DEVICE, byte );
    instance()._sendMutex.unlock();
}
