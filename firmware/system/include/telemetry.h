#ifndef TELEMETRY_H
#define TELEMETRY_H

#define BUFFER_SIZE         12

#include "ch.hpp"
#include "hal.h"


using namespace chibios_rt;

class Telemetry : public BaseStaticThread<512> {
    friend class TelemetryReader;
                                            Telemetry();
                                           ~Telemetry();
    public:
        static Telemetry&                   instance();

        static u8                           get(float timeout = -1);
        static void                         put(u8 byte, float timeout = -1);

        /**	send package to channel
            this function blocks untill send is complete or timeout
            @param		buf			pointer to the package begin
            @param		len			package len in bytes
            @param		timeout		timeout in sec, -1 for infinite time
            @retval     number of bytes which actually was sent */
        static u32                          send(const u8* buf, const u32 len, float timeout = -1);
//        u32                                 send(const Container&, float timeout = -1);

        /**	synchronus asynchronus receive package from channel
            this function blocks caller thread untill receive complete or timeout
            @param		buf			pointer to the package begin
            @param		len			package len in bytes
            @param		timeout		timeout in sec, -1 for infinite time
            @retval     number of bytes which actually was received */
        static u32                          read(u8* buf, const u32 len, float timeout = -1 );

        /**	number of bytes available in channel
            @retval		len			available bytes */
        static u32                          available();

    private:
        static void                         transmitCallback(UARTDriver*);
        static void                         charReceiveCallback(UARTDriver*, uint16_t c);
        virtual void                        main(void);

        u8                                 _sendByte;
        u8                                 _receiveByte;

        UARTDriver&                        _uartDriver;
        UARTConfig                         _uartConfig;


        const u32                          _readBufferSize = BUFFER_SIZE;
        u8                                 _readBuffer[ BUFFER_SIZE ];
        u32                                _readBufferBeginIndex = 0;
        u32                                _readBufferEndIndex = 0;
        CounterSemaphore                   _readBytes{ 0 };

        const u32                          _writeBufferSize = BUFFER_SIZE;
        u8                                 _writeBuffer[ BUFFER_SIZE ];
        u32                                _writeBufferBeginIndex = 0;
        u32                                _writeBufferEndIndex = 0;
        CounterSemaphore                   _writeBufferFreeBytes{ BUFFER_SIZE };
        CounterSemaphore                   _writeBufferUsedBytes{ 0 };
        CondVar                            _writeComplete;
        Mutex                              _mutex;
};


#endif
