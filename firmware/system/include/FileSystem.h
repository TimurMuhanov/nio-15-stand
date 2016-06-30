#ifndef FILESYSTEM_H
#define FILESYSTEM_H


#include "ch.hpp"
#include "hal.h"

#include "ff.h"
#include <string>
#include "Terminal.h"

using namespace std;
using namespace chibios_rt;

/*enum class Permission {
    Read = 0x01,
    Write = 0x02
};

enum class Mode {
    OpenExisting = 0x04,    // Opens the file. The function fails if the file is not existing.
    OpenAlways = 0x08,      // Opens the file if it is existing. If not, a new file will be created.
    CreateNew = 0x10,       // Creates a new file. The function fails if the file is existing.
    CreateAlways = 0x20     // Creates a new file. If the file is existing, it will be truncated and overwritten.
};*/

class FileSystem {
    private:
                                            FileSystem();
                                           ~FileSystem();
    public:

        static void                         init();
        static bool                         isAvailable();

        static bool                         open( FIL& fil, const string& file, const u8 mode );
        static bool                         write( FIL& fil, const string& data );
        static bool                         write( FIL& fil, const u8* data, const u32 len );
        static bool                         readLine( FIL& fil, string& line );
        static bool                         sync( FIL& fil );
        static bool                         erase( FIL& fil );

    private:
        static FATFS                        _filesystem;
        static bool                         _accessibility;
        static Mutex                        _mutex;
};



#endif
