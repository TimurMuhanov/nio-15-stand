#ifndef SETTINGS_H
#define SETTINGS_H


#include "ch.h"
#include "ff.h"
#include <map>
#include <string>

using namespace std;


class Settings {
    private:
                                            Settings();
                                           ~Settings();
    public:

        static void                         init();
        static void                         sync();
        static bool                         contains( const string& );
        static void                         set( const string& key, const string& value );
        static string                       get( const string& );
        static void                         remove( const string& );
        static map<string, string>&         settings();
    private:
        static map<string, string>          _settings;
        static FIL                          _file;
};

#endif // SETTINGS_H
