#include "Flash.h"
#include "Terminal.h"


Flash::Flash() : BaseStaticThread<512>() {
    start(NORMALPRIO);
}

Flash::~Flash() {}

void Flash::write( u32 address, u8* buffer, u32 length ) {
    if( !BOARD_IS_ADRESS_CORRECT(address) || !BOARD_IS_ADRESS_CORRECT(address+length) )
        return;
//    for( u32 i = 0; i < length; ++i, ++instance().endIndex ) {
//        instance().freeBytes.wait();
//        instance().addressBuffer[instance().endIndex % instance().bufferSize] = address + i;
//        instance().dataBuffer[instance().endIndex % instance().bufferSize] = buffer[i];
//        instance().usedBytes.signal();
//    }
    FLASH->CR |= FLASH_CR_PG;                   // begin programming
    FLASH->CR &= ~FLASH_CR_PSIZE;               // programming size is 1 byte
    FLASH->CR |= FLASH_CR_PSIZE_1;              // programming size is 4 byte
    for( u32 i = 0; i < length; i+=4 ) {
        while( FLASH->SR & FLASH_SR_BSY );          // wait for flash ready
        *(__IO u32*)( address+i ) = *((u32*)(buffer+i));
    }
    FLASH->CR &= ~(FLASH_CR_PG);                // end programming
}

u8 Flash::sector( u32 address ) {
    return BOARD_ADDRESS_TO_SECTOR(address);
}

void Flash::erase( u32 begin, u32 length ) {
    eraseBegin();
    for( u8 i = sector( begin ); i <= sector( begin+length ); i++) {
         eraseSector( i );
    }
    eraseEnd();
}

void Flash::eraseBegin() {
    FLASH->CR |= FLASH_CR_SER;
}

void Flash::eraseEnd() {
    FLASH->CR &= ~FLASH_CR_SER;
}

bool Flash::eraseSector( u8 sector ) {
    while( FLASH->SR & FLASH_SR_BSY );
    FLASH->CR &= ~FLASH_CR_SNB;
    FLASH->CR |= (sector << 3) & 0x78;
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= FLASH_CR_STRT;
    return true;
}

bool Flash::isLocked() {
    return FLASH->CR & FLASH_CR_LOCK;
}

void Flash::lock() {
    FLASH->CR |= FLASH_CR_LOCK;
}

void Flash::unlock() {
    FLASH->KEYR = (u32)0x45670123;
    FLASH->KEYR = (u32)0xCDEF89AB;
}

void Flash::main(void) {
    setName( "flash" );
    while( !shouldTerminate() ) {
        usedBytes.wait();
        while( FLASH->SR & FLASH_SR_BSY );          // wait for flash ready
        FLASH->CR |= FLASH_CR_PG;                   // begin programming
        FLASH->CR &= ~FLASH_CR_PSIZE;               // programming size is 1 byte

        *(__IO u8*)( addressBuffer[beginIndex % bufferSize] ) = dataBuffer[beginIndex % bufferSize];

        FLASH->CR &= ~(FLASH_CR_PG);                // end programming
        beginIndex++;
        freeBytes.signal();
    }
    exit( 0 );
}
