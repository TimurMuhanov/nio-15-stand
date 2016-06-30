#include "ch.hpp"
#include "hal.h"

#include "Terminal.h"
#include "Telemetry.h"
#include "Flash.h"
#include "Thread.h"


#define TIMEOUT				0.1
#define TRIES				3

using namespace chibios_rt;


/*
  board                                 computer

  connection -------------------------------------------

  send _connect                 ->      receive _connect
  receive _ack                  <-      send _ack

  erase ------------------------------------------------
  receive _erase + length       <-      send _erase + number of bytes to earse
  send _ack                     ->      receive _ack
  being to erase
  send bytes erased             ->      update erase status
  ...
  send _ack                     ->      receive _ack

  wirte ------------------------------------------------
  receive _write                <-      send _write
  receive beginAddress          <-      send beginAddress
  receive length                <-      send length
  receive data + crc            <-      send data + crc
  send _ack                     ->      receive _ack
  write data
  send _ack                     ->      receive _ack
*/


class Loader {
                    Loader() {}
                   ~Loader() {}
    public:

        inline static Loader&          instance() {
            static Loader instance;
            return instance;
        }

        static bool             connect() {
            u32 i = 0;

            while(i++ < 0x4) {
                Telemetry::put( _connect );
//                Telemetry::put( 'a' );
                if( Telemetry::get(TIMEOUT*2) == _ack ) {
                    return true;
                }
            }
            return false;
        }

        static void             jump(u32 address) {
            boardStop();
            for( int h=0; h<8; h++ )
               NVIC->ICER[h] = NVIC->IABR[h];
            SCB->VTOR = address;
            __set_CONTROL(0);
            __set_MSP( (u32) (((u32*) address)[0]) );
            ( (void (*)(void)) (((u32*) address)[1]) )();

        }

        static bool             parseCommands() {
            Flash::unlock();
            while( 1 ) {
                switch( instance().getCommand() ) {
                    case _erase: {
//                        print("erase begin\n\r");
                        chThdSleepMilliseconds(10);
                        u32 len = instance().receiveU32();
//                        print("erase 0x%08x bytes\n\r", len);
                        chThdSleepMilliseconds(3);
                        Flash::eraseBegin();
                        for( u8 sector = Flash::sector( BOARD_FLASH_FIRMWARE ); sector <= Flash::sector( BOARD_FLASH_FIRMWARE+len ); sector++ ) {
//                            print("begin erase %u sector\n\r", sector );
                            chThdSleepMilliseconds(10);
                            Flash::eraseSector( sector );
//                            print("erased %u sector\n\r", sector );
                            chThdSleepMilliseconds(10);
                        }
                        Flash::eraseEnd();
                        instance().sendAck();
                    }
                    break;
                    case _write: {
                        print("command write received\n\r");

                        // receive block 8+_packLength+1 bytes
//                        systime_t bg = System::getTime();
//                        print("av %u\n\r", chQSpaceI( &BOARD_BLUETOOTH_DEVICE.iqueue ) );
                        u32 bytesRed = Telemetry::read( _buffer, 4+_packLength+1, TIMEOUT );
//                        print("test %u\n\r", ST2MS(System::getTime() - bg) );
                        u32 address = ((_buffer[0] << 24)&0xff000000 ) | ((_buffer[1] << 16)&0x00ff0000 ) | ((_buffer[2] << 8)&0x0000ff00 ) | ((_buffer[3] << 00)&0x000000ff );
                        u8 sendedChecksum = _buffer[4+_packLength+0];
                        u8 calculatedChecksum = 0;
                        for(u32 i=0; i<4+_packLength; i++) {
                            calculatedChecksum ^= _buffer[i];
                        }
                        if( bytesRed != 4+_packLength+1 || sendedChecksum != calculatedChecksum ) {
                            instance().sendNack();
//                            print("command write: error 0x%08x checksum 0x%02x  0x%02x %u\n\r", address, sendedChecksum, calculatedChecksum, bytesRed );
                            break;
                        } else {
                            instance().sendAck();
                            Flash::write( address, _buffer+4, _packLength );
//                            static systime_t time = System::getTime();
//                            print("command write: success 0x%08x checksum 0x%02x  0x%02x %u, %u\n\r", address, sendedChecksum, calculatedChecksum, bytesRed, ST2MS(System::getTime()-time) );
//                            time = System::getTime();
                        }
                    }
                    break;
                    case _go:
//                        flashWrite( BOARD_FLASH_FIRMWARE, (u32*)&begin, 1 );
                        Flash::lock();
                        return true;
                }
            }
        }

    private:
        u32                     receiveU32() {
            u8 buffer[4];
//            print("receiveU32: rc begin\n\r" );
//            chThdSleepMilliseconds(10);
            u32 bytesRed = Telemetry::read( buffer, 4, TIMEOUT );
//            print("receiveU32: rc end\n\r" );
            if( bytesRed == 4 ) {
                return ((buffer[0] << 24)&0xff000000 ) | ((buffer[1] << 16)&0x00ff0000 ) | ((buffer[2] << 8)&0x0000ff00 ) | ((buffer[3] << 00)&0x000000ff );
            } else {
//                print("receiveU32: error read %u\n\r", bytesRed );
//                chThdSleepMilliseconds(3);
                return 0;
            }
        }
        u8                      receiveU8() {
            u8 buffer;
            u32 bytesRed = Telemetry::read( &buffer, 1, TIMEOUT );
            if( bytesRed == 1 ) {
                return buffer;
            } else {
//                print("receiveU8: error read %u\n\r", bytesRed );
                chThdSleepMilliseconds(3);
                return 0;
            }
        }

        void                    sendAck() {
            Telemetry::put( _ack );
//            print("sendAck\n\r");
        }

        void                    sendNack() {
            Telemetry::put( _nack );
//            print("sendNack\n\r");
        }

        u8                      getCommand() {
//            print("get cmd\n\r");
            u8 command[2];
            while( Telemetry::get() != _begin );
            u32 bytesRed = Telemetry::read( command, 2, TIMEOUT );
            if( bytesRed == 2 && command[0] + command[1] == 0x100 ) {
                switch( command[0] ) {
                    case _erase:
                    case _write:
                    case _go:
                        sendAck();
                        return command[0];
                    default:
                        sendNack();
                        return _unknown;
                }
                return true;
            }
            return _unknown;
        }

        static const u8                _begin = 0xFE;
        static const u8                _connect = 0x7F;
        static const u8                _go = 0x21;
        static const u8                _write = 0x31;
        static const u8                _erase = 0x44;
        static const u8                _ack = 0x79;
        static const u8                _nack = 0x1F;
        static const u8                _unknown = 0x55;

        static const int               _packLength = 1024;
        static u8                      _buffer[4+_packLength+1];
};

u8 Loader::_buffer[];

class BlinkerThread : public BaseStaticThread<128> {
    public:
        BlinkerThread() : BaseStaticThread<128>() {}

    private:
        virtual void main(void) {
            setName( "blinker" );
            while( !shouldTerminate() ) {
                palTogglePad(GPIOC, 15);
                sleep(MS2ST(50));
            }
            exit( 0 );
        }

};

BlinkerThread blinkerThread;

class LoaderThread : public BaseStaticThread<512> {
    public:
        LoaderThread() : BaseStaticThread<512>() {}

    private:
        virtual void main(void) {
            setName( "loader" );

            if( !Loader::connect() ) {
                blinkerThread.requestTerminate();
                blinkerThread.wait();
                Loader::jump(BOARD_FLASH_FIRMWARE);
                return;
            }
//            print("connected\n\r");
            if( Loader::parseCommands() ) {
                blinkerThread.requestTerminate();
                blinkerThread.wait();
                Loader::jump(BOARD_FLASH_FIRMWARE);
            }
            exit( 0 );
        }

};

LoaderThread loaderThread;

int main(void) {
	halInit();
    System::init();
    ioInit();

    loaderThread.start(NORMALPRIO);
    blinkerThread.start(NORMALPRIO);

    Thread::loop();
}
