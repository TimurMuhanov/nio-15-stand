/**	@defgroup	FLASH
    @brief		Module to read/write internal flash
	@{ */

#ifndef FLASH_H
#define FLASH_H

#include "ch.hpp"


#define FLASH_BUFFER_SIZE               256


using namespace chibios_rt;


class Flash : public BaseStaticThread<512> {
                                        Flash();
                                       ~Flash();

    public:
        inline static Flash&            instance();
        static void                     write( u32 address, u8* buffer, u32 length );
        static u8                       sector( u32 address );
        static void                     erase( u32 begin, u32 length );
        static void                     eraseBegin();
        static void                     eraseEnd();
        static bool                     eraseSector( u8 sector );
        static bool                     isLocked();
        static void                     lock();
        static void                     unlock();

    private:
        virtual void                    main(void);

        const u32                       bufferSize = FLASH_BUFFER_SIZE;
        u8                              dataBuffer[FLASH_BUFFER_SIZE];
        u32                             addressBuffer[FLASH_BUFFER_SIZE];

        u32                             beginIndex = 0;
        u32                             endIndex = 0;
        CounterSemaphore                freeBytes{ FLASH_BUFFER_SIZE };
        CounterSemaphore                usedBytes{ 0 };
};


Flash& Flash::instance() {
    static Flash instance;
    return instance;
}

#endif

/** @} */
