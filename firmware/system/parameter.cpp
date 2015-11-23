#include "parameter.h"
#include "io.h"
#include <algorithm>
#include <map>
#include <string>
#include <string.h>
#include <vector>
#include <memory>


using namespace std;


map<string, Parameter*> parameters;
FIL parameterFile;


void parameterInit(void) {
	// open file
	if( sdCardInited() ) {
		if( f_open(&parameterFile, "/parameters.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS ) != FR_OK ) {
			return;
		}

		// read parameters
		vector<char> separators;
		separators.push_back( ' ' );
		separators.push_back( '=' );
		separators.push_back( ':' );
		separators.push_back( '\t' );
		separators.push_back( '\n' );
		separators.push_back( '\r' );

		TCHAR buffer[PARAMETER_MAX_RECORD_LENGTH];
		while( f_gets( buffer, PARAMETER_MAX_RECORD_LENGTH, &parameterFile ) != NULL ) {
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

			if( name.empty() || value.empty() )
				continue;

			Parameter* parameter = (Parameter*)malloc( sizeof(Parameter) );
			bool alphaFlag = false;
			bool digitFlag = false;
			bool dotFlag = false;

			for( char ch : value ) {
				if( isalpha(ch) )
					alphaFlag = true;
				if( isdigit(ch) )
					digitFlag = true;
				if( ch == '.' ) {
					dotFlag = true;
				}
			}
			if( digitFlag ) {
				if( !dotFlag ) {
					parameter->type = Int;
					parameter->val.Int = stoi(value);
				} else {
					parameter->type = Float;
					parameter->val.Float = stof(value);
				}
			} else if( alphaFlag ) {
				parameter->type = String;
				parameter->val.String = (char*) malloc( PARAMETER_MAX_STRING_LENGTH*sizeof(char) );
				strcpy( parameter->val.String, value.c_str() );
			}
			if( digitFlag || alphaFlag ) {
				parameters[ name ] = parameter;
			}
		}
		f_close( &parameterFile );
	}
}

bool parameterFind( const char* name ) {
	if( parameters.find( string(name) ) != parameters.end() )
		return true;
	else
		return false;
}

Parameter* parameterGet( const char* name ) {
	if( parameterFind(name) )
		return parameters[ string(name) ];
	return NULL;
}

void parameterAdd(const char *name, Parameter *parameter) {
	parameters[ string(name) ] = parameter;
}

void parameterSync() {
	if( f_open(&parameterFile, "/parameters.txt", FA_WRITE | FA_CREATE_ALWAYS ) != FR_OK )
		return;

	uint len;
	UINT res;
	char record[PARAMETER_MAX_RECORD_LENGTH];
	for( map<string, Parameter*>::iterator it = parameters.begin(); it != parameters.end(); it++) {
		switch( it->second->type ) {
			case Int:
				len = sprintf(record, "%s %d\r\n", it->first.c_str(), it->second->val.Int );
				break;
			case Float:
				len = sprintf(record, "%s %."PARAMETER_FLOAT_PRECISION"f\r\n", it->first.c_str(), it->second->val.Float );
				break;
			case String:
				len = sprintf(record, "%s %s\r\n", it->first.c_str(), it->second->val.String );
			break;
		}
		f_write( &parameterFile, record, len, &res );
	}
	f_sync( &parameterFile );
	f_close( &parameterFile );
}

