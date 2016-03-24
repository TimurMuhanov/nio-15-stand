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
