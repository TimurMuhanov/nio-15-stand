#ifndef SETTINGS_H
#define SETTINGS_H

#ifdef __cplusplus

#include "ch.h"
#include "ff.h"
#include <map>
#include <string>


#define PARAMETER_MAX_RECORD_LENGTH     255


using namespace std;


class Settings {
    private:
                                            Settings();
                                           ~Settings();
    public:

        static void                         init();
        static void                         sync();
        static void                         set( const string& name, const string& value );
        static string                       get( const string& );
        static void                         remove( const string& );
        static map<string, string>&         settings();
    private:
        static map<string, string>          _settings;
        static FIL                          _file;
};


#endif

#endif // SETTINGS_H
