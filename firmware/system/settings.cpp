#include "settings.h"
#include "io.h"
#include <algorithm>


map<string, string> Settings::_settings;
FIL                 Settings::_file;


Settings::Settings() {
}

Settings::~Settings() {
}

void Settings::init() {
    // open file
    if( sdCardInited() ) {
        FRESULT res;

        if( (res = f_open(&_file, "/parameters.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS )) != FR_OK )
            return;

        // read _parameters
        vector<char> separators;
        separators.push_back( ' ' );
        separators.push_back( '=' );
        separators.push_back( ':' );
        separators.push_back( '\t' );
        separators.push_back( '\n' );
        separators.push_back( '\r' );

        char buffer[PARAMETER_MAX_RECORD_LENGTH];
        while( f_gets( (TCHAR*) buffer, PARAMETER_MAX_RECORD_LENGTH, &_file ) != NULL ) {
            string record(buffer);
            string name, value;
            unsigned int i=0;

            while( find( separators.begin(), separators.end(), record[i] ) != separators.end() && i<record.length() )
                i++;
            while( find( separators.begin(), separators.end(), record[i] ) == separators.end() && i<record.length() )
                name += record[i++];
            while( find( separators.begin(), separators.end(), record[i] ) != separators.end() && i<record.length() )
                i++;
            while( find( separators.begin(), separators.end(), record[i] ) == separators.end() && i<record.length() )
                value += record[i++];

            if( !( name.empty() || value.empty() ) )
                set(name, value);
        }
    }

    //sync();
}

void Settings::sync() {
    if( !sdCardInited() )
        return;

    f_lseek(&_file, 0);
    f_truncate(&_file);

    UINT len;
    UINT res;
    char record[PARAMETER_MAX_RECORD_LENGTH];
    for(
        map<string, string>::iterator it = _settings.begin();
        it != _settings.end();
        it++
    ) {
        len = sprintf(record, "%s %s\r\n", it->first.c_str(), it->second.c_str() );
        f_write( &_file, record, len, &res );
    }
    f_sync( &_file );
}

void Settings::set( const string& name, const string& value ) {
    _settings[name] = value;
}

string Settings::get( const string& name ) {
    if( _settings.find(name) != _settings.end() )
        return _settings[name];
    return string();
}

void Settings::remove( const string& name ) {
    _settings.erase( _settings.find( name ) );
}

map<string, string>&Settings::settings() {
    return _settings;
}
