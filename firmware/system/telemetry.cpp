#include "Telemetry.h"
#include "Terminal.h"



//Telemetry::Telemetry() : BaseStaticThread<512>(), _inQueue(_inBuf, BUFFER_SIZE, NULL, NULL) {
////    start(NORMALPRIO);
//}

//Telemetry::~Telemetry() {}

//Telemetry& Telemetry::instance() {
//    static Telemetry instance;
//    return instance;
//}

////void Telemetry::put(u8 byte, float timeout) {
////    instance()._outQueue.put( byte, timeout<0 ? TIME_INFINITE : MS2ST(timeout*1e3) );
////}

//u8 Telemetry::get(float timeout) {
//    return instance()._inQueue.get( timeout<0 ? TIME_INFINITE : MS2ST(timeout*1e3) );
//}

//u32 Telemetry::send(const u8* buf, const u32 len, float timeout) {
//    u32 writtenBytes = 0;
//    _outMutex.lock();
//    uartStartSend( &BOARD_BLUETOOTH_DEVICE, len, buf );
//    _outReady.wait();
//    _outMutex.unlock();
//    return writtenBytes;
//}

//u32 Telemetry::read(u8* buf, const u32 len, float timeout) {
//    instance()._inMutex.lock();
//    u32 redBytes = instance()._inQueue.read( buf, len, timeout<0 ? TIME_INFINITE : MS2ST(timeout*1e3) );
//    instance()._inMutex.unlock();
//    return redBytes;
//}

//u32 Telemetry::available() {
//    System::lockFromIsr();
//    u32 available = instance()._inQueue.getFullI();
//    System::unlockFromIsr();
//    return available;
//}

//void Telemetry::main() {
//}




//void telemetryTransmitCallback(UARTDriver*) {
//    System::lockFromIsr();
//    Telemetry::instance()._outReady.signalI();
//    System::unlockFromIsr();
//}

//void telemetryCharReceiveCallback(UARTDriver*, uint16_t c) {
//    System::lockFromIsr();
//    Telemetry::instance()._inQueue.putI(c);
//    System::unlockFromIsr();
//}






















//#include "Telemetry.h"
//#include "Terminal.h"



//Telemetry::Telemetry() {
//    start(NORMALPRIO);
//}

//Telemetry::~Telemetry() {}

//Telemetry& Telemetry::instance() {
//    static Telemetry instance;
//    return instance;
//}

//u8 Telemetry::get(float timeout) {
//    instance().read( &instance()._receiveByte, 1, timeout);
//    return instance()._receiveByte;
//}

//void Telemetry::put(u8 byte, float timeout) {
//    instance()._sendByte = byte;
//    instance().send( &instance()._sendByte, 1, timeout);
//}

//u32 Telemetry::send(const u8* buf, const u32 len, float timeout) {
//    u32 writtenBytes = 0;
//    systime_t end;
//    if( timeout<0 ) {
//        end = TIME_INFINITE;
//    } else {
//        end = System::getTime() + MS2ST(timeout*1e3);
//    }
//    for( ; writtenBytes<len && System::getTime() < end; writtenBytes++ ) {
//        instance()._writeBufferFreeBytes.wait();
//        System::lock();
//        instance()._writeBuffer[ instance()._writeBufferEndIndex % instance()._writeBufferSize ] = buf[writtenBytes];
//        instance()._writeBufferEndIndex++;
//        System::unlock();
//        instance()._writeBufferUsedBytes.signal();
////        print("tm 0x%02x\n\r", buf[writtenBytes] );
//    }

//    return writtenBytes;
//}

//u32 Telemetry::read(u8* buf, const u32 len, float timeout) {
//    u32 redBytes = 0;
//    systime_t end;
//    if( timeout<0 ) {
//        end = TIME_INFINITE;
//    } else {
//        end = System::getTime() + MS2ST(timeout*1e3);
//    }
////    print("read end %u, curr %u, tim %f, tim %u\n\r", end, System::getTime(), timeout, MS2ST(timeout*1e3) );
//    for( ; redBytes<len && System::getTime() < end; ) {
//        if( instance()._receivedBytes.wait( end - System::getTime() ) != MSG_OK ) {
//            continue;
//        }
//        System::lock();
//        buf[redBytes] = instance()._readBuffer[instance()._readBufferBeginIndex % instance()._readBufferSize];
//        instance()._readBufferBeginIndex++;
//        System::unlock();
////        print("rc 0x%02x\n\r", buf[redBytes] );
//        redBytes++;
//    }
////    print("rce %u\n\r", redBytes );
////    chThdSleepMilliseconds(10);
//    return redBytes;

//}

//u32 Telemetry::available() {
//    System::lockFromIsr();
//    cnt_t receivedBytes = Telemetry::instance()._receivedBytes.getCounterI();
//    System::unlockFromIsr();
//    return receivedBytes;
//}

//void Telemetry::main() {
//    setName( "telemetry sender" );
//    while( !shouldTerminate() ) {
//        _writeBufferUsedBytes.wait();
//        int bytes = 1;
//        while( _writeBufferUsedBytes.wait( TIME_IMMEDIATE ) == MSG_OK ) {
//            ++bytes;
//        }

//        System::lock();
//        _mutex.lockS();
//        if( (_writeBufferBeginIndex%_writeBufferSize)+bytes > _writeBufferSize ) {
//            uartStartSendI( &BOARD_BLUETOOTH_DEVICE, _writeBufferSize - (_writeBufferBeginIndex%_writeBufferSize), _writeBuffer + (_writeBufferBeginIndex%_writeBufferSize) );
//            _writeComplete.waitS();
//            uartStartSendI( &BOARD_BLUETOOTH_DEVICE, (_writeBufferBeginIndex%_writeBufferSize) + bytes - _writeBufferSize, _writeBuffer );
//            _writeComplete.waitS();
//        } else {
//            uartStartSendI( &BOARD_BLUETOOTH_DEVICE, bytes, _writeBuffer + (_writeBufferBeginIndex%_writeBufferSize) );
//            _writeComplete.waitS();
//        }
//        _mutex.unlockS();
//        System::unlock();

//        while( bytes-- ) {
//            ++instance()._writeBufferBeginIndex;
//            instance()._writeBufferFreeBytes.signal();
//        }
//    }
//    exit( 0 );
//}




//void telemetryTransmitCallback(UARTDriver*) {
//    System::lockFromIsr();
//    Telemetry::instance()._writeComplete.signalI();
//    System::unlockFromIsr();
//}

//void telemetryCharReceiveCallback(UARTDriver*, uint16_t c) {
//    Telemetry::instance()._readBuffer[(Telemetry::instance()._readBufferEndIndex) % Telemetry::instance()._readBufferSize] = c;
//    System::lockFromIsr();
//    if( Telemetry::instance()._receivedBytes.getCounterI() == BUFFER_SIZE ) {
//        ++Telemetry::instance()._readBufferBeginIndex;
//        ++Telemetry::instance()._readBufferEndIndex;
//    } else {
//        ++Telemetry::instance()._readBufferEndIndex;
//        Telemetry::instance()._receivedBytes.signalI();
//    }
//    System::unlockFromIsr();
//}

Telemetry::Telemetry() {
}

Telemetry::~Telemetry() {
}

Telemetry&Telemetry::instance() {
    static Telemetry instance;
    return instance;
}

u32 Telemetry::send(const u8* buf, const u32 len) {
    instance()._sendMutex.lock();
    u32 res = sdWrite( &BOARD_BLUETOOTH_DEVICE, buf, len );
    instance()._sendMutex.unlock();
    return res;
}

u32 Telemetry::read(u8* buf, const u32 len) {
    instance()._receiveMutex.lock();
    u32 res = sdRead( &BOARD_BLUETOOTH_DEVICE, buf, len );
    instance()._receiveMutex.unlock();
    return res;

}

u8 Telemetry::get() {
    instance()._receiveMutex.lock();
    u8 res = sdGet( &BOARD_BLUETOOTH_DEVICE );
    instance()._receiveMutex.unlock();
    return res;
}

void Telemetry::put(u8 byte) {
    instance()._sendMutex.lock();
    sdPut( &BOARD_BLUETOOTH_DEVICE, byte );
    instance()._sendMutex.unlock();
}
