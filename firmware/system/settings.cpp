#include "Settings.h"
#include "FileSystem.h"
#include <algorithm>


map<string, string> Settings::_settings;
FIL                 Settings::_file;


Settings::Settings() {
}

Settings::~Settings() {
}

void Settings::init() {
    // open file
    if( !FileSystem::isAvailable() )
        return;

    if( !FileSystem::open( _file, string("/parameters.txt"), FA_READ | FA_WRITE | FA_OPEN_ALWAYS ) )
        return;

    // read _parameters
    vector<char> separators;
    separators.push_back( ' ' );
    separators.push_back( '=' );
    separators.push_back( ':' );
    separators.push_back( '\t' );
    separators.push_back( '\n' );
    separators.push_back( '\r' );

    string record;
    while( FileSystem::readLine( _file, record ) ) {
        string key, value;
        unsigned int i=0;

        while( find( separators.begin(), separators.end(), record[i] ) != separators.end() && i<record.length() )
            i++;
        while( find( separators.begin(), separators.end(), record[i] ) == separators.end() && i<record.length() )
            key += record[i++];
        while( find( separators.begin(), separators.end(), record[i] ) != separators.end() && i<record.length() )
            i++;
        while( find( separators.begin(), separators.end(), record[i] ) == separators.end() && i<record.length() )
            value += record[i++];

        if( !( key.empty() || value.empty() ) )
            set(key, value);
    }
}

void Settings::sync() {
    if( !FileSystem::isAvailable() )
        return;

    FileSystem::erase( _file );

    for(
        map<string, string>::iterator it = _settings.begin();
        it != _settings.end();
        it++
    ) {
        FileSystem::write( _file, it->first + " " + it->second + "\n" );
    }

    FileSystem::sync( _file );
}

bool Settings::contains(const string& key) {
    if( _settings.find(key) != _settings.end() ) {
        return true;
    } else {
        return false;
    }
}

void Settings::set( const string& key, const string& value ) {
    _settings[key] = value;
}

string Settings::get( const string& key ) {
    if( contains(key) ) {
        return _settings[key];
    } else {
        return string();
    }
}

void Settings::remove( const string& key ) {
    _settings.erase( _settings.find( key ) );
}

map<string, string>&Settings::settings() {
    return _settings;
}
