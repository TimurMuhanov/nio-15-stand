#include "FileSystem.h"

FATFS FileSystem::_filesystem;
bool FileSystem::_accessibility = false;
Mutex FileSystem::_mutex;


FileSystem::FileSystem() {}

FileSystem::~FileSystem() {}

void FileSystem::init() {
    // sd card and fat file system init
    u32 tries = 3;
    while( sdcConnect(&SDCD1) != HAL_SUCCESS && --tries ) {
        chThdSleepMilliseconds(100);
    }
    if(!tries) return;

    if( f_mount(&_filesystem, "", 0 ) == FR_OK ) {
        _accessibility = true;
    }
}

bool FileSystem::isAvailable() {
    //_mutex.lock();
    bool result = _accessibility;
    //_mutex.unlock();
    return result;
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
    //_mutex.lock();
    bool result = (f_open( &fil, file.c_str(), mode) == FR_OK);
    //_mutex.unlock();
    return result;
}

bool FileSystem::write(FIL& fil, const string& data) {
    if( !isAvailable() )
        return false;

    //_mutex.lock();
    bool result = (write( fil, (const u8*) data.c_str(), data.length() ) == FR_OK);
    //_mutex.unlock();
    return result;
}

bool FileSystem::write(FIL& fil, const u8* data, const u32 len) {
    if( !isAvailable() )
        return false;


    UINT res;
    //_mutex.lock();
    bool result = (f_write( &fil, data, len, &res ) == FR_OK);
    //_mutex.unlock();
    return result;
}

bool FileSystem::readLine( FIL& fil, string& line ) {
    if( !isAvailable() )
        return false;

    //_mutex.lock();
    TCHAR buffer[255];
    if( f_gets( (TCHAR*) buffer, 255, &fil ) != NULL) {
        line = string(buffer);
        //_mutex.unlock();
        return true;
     } else {
        //_mutex.unlock();
        return false;
    }
}

bool FileSystem::sync( FIL& fil ) {
    if( !isAvailable() )
        return false;

    //_mutex.lock();
    bool syn = f_sync( &fil );
    //_mutex.unlock();
    return syn;
}

bool FileSystem::erase( FIL& fil ) {
    if( !isAvailable() )
        return false;

    //_mutex.lock();
    if( f_lseek( &fil, 0 ) != FR_OK ) {
        //_mutex.unlock();
        return false;
    }
    bool result = f_sync( &fil );
    //_mutex.unlock();
    return result;
}
