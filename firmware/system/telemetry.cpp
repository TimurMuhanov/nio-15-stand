#include "telemetry.h"
#include "io.h"


Telemetry::Telemetry() :
    BaseStaticThread<512>(),
   _uartDriver(BOARD_BLUETOOTH_DEVICE),
   _uartConfig{ Telemetry::transmitCallback, NULL, NULL, Telemetry::charReceiveCallback, NULL, BOARD_USART2_BAUD,0,0,0 }
{
    uartStart( &_uartDriver, &_uartConfig );
    start(NORMALPRIO);
}

Telemetry::~Telemetry() {
}

Telemetry& Telemetry::instance() {
    static Telemetry instance;
    return instance;
}

u8 Telemetry::get(float timeout) {
    instance().read( &instance()._receiveByte, 1, timeout);
    return instance()._receiveByte;
}

void Telemetry::put(u8 byte, float timeout) {
    instance()._sendByte = byte;
    instance().send( &instance()._sendByte, 1, timeout);
}

u32 Telemetry::send(const u8* buf, const u32 len, float timeout) {
    int writtenBytes = 0;
    systime_t end;
    if( timeout<0 ) {
        end = TIME_INFINITE;
    } else {
        end = System::getTime() + US2ST(timeout*1e6);
    }
    for( ; writtenBytes<len && System::getTime() < end; writtenBytes++ ) {
        instance()._writeBufferFreeBytes.wait();
        System::lock();
        instance()._writeBuffer[ instance()._writeBufferEndIndex % instance()._writeBufferSize ] = buf[writtenBytes];
        instance()._writeBufferEndIndex++;
        System::unlock();
        instance()._writeBufferUsedBytes.signal();
    }

    return writtenBytes;
}

u32 Telemetry::read(u8* buf, const u32 len, float timeout) {
    int redBytes = 0;
    systime_t end;
    if( timeout<0 ) {
        end = TIME_INFINITE;
    } else {
        end = System::getTime() + US2ST(timeout*1e6);
    }
    for( ; redBytes<len && System::getTime() < end; redBytes++ ) {
        if( instance()._readBytes.wait( end - System::getTime() ) != MSG_OK )
            continue;
        System::lock();
        buf[redBytes] = instance()._readBuffer[instance()._readBufferBeginIndex % instance()._readBufferSize];
        instance()._readBufferBeginIndex++;
        System::unlock();
        print("rc 0x%02x\n\r", buf[redBytes] );
    }
    return redBytes;

}

u32 Telemetry::available() {

}

void Telemetry::transmitCallback(UARTDriver*) {
    System::lockFromIsr();
    instance()._writeComplete.signalI();
    System::unlockFromIsr();
}

void Telemetry::charReceiveCallback(UARTDriver*, uint16_t c) {
    instance()._readBuffer[(instance()._readBufferEndIndex) % instance()._readBufferSize] = c;
    System::lockFromIsr();
    if( instance()._readBytes.getCounterI() == BUFFER_SIZE ) {
        ++instance()._readBufferBeginIndex;
        ++instance()._readBufferEndIndex;
    } else {
        ++instance()._readBufferEndIndex;
        instance()._readBytes.signalI();
    }
    System::unlockFromIsr();
}

void Telemetry::main() {
    setName( "telemetry sender" );
    while( !shouldTerminate() ) {
        System::lock();
        int bytes = _writeBufferUsedBytes.getCounterI();
        System::unlock();

        if( bytes == 0 ) {
            _writeBufferUsedBytes.wait();
        }
        bytes = 1;
        while( _writeBufferUsedBytes.wait( TIME_IMMEDIATE ) == MSG_OK ) {
            ++bytes;
        }

        System::lock();
        _mutex.lockS();
        if( (_writeBufferBeginIndex%_writeBufferSize)+bytes > _writeBufferSize ) {
            uartStartSendI( &_uartDriver, _writeBufferSize - (_writeBufferBeginIndex%_writeBufferSize), _writeBuffer + _writeBufferBeginIndex );
            _writeComplete.waitS();
            uartStartSendI( &_uartDriver, (_writeBufferBeginIndex%_writeBufferSize) + bytes - _writeBufferSize, _writeBuffer );
            _writeComplete.waitS();
            palSetPad(GPIOC, 0);
        } else {
            uartStartSendI( &_uartDriver, bytes, _writeBuffer + (_writeBufferBeginIndex%_writeBufferSize) );
            _writeComplete.waitS();
        }
        _mutex.unlockS();
        System::unlock();

        while( bytes-- ) {
            ++instance()._writeBufferBeginIndex;
            instance()._writeBufferFreeBytes.signal();
        }
        int a;
        a=1;
    }
    exit( 0 );
}
