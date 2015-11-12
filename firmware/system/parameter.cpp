#include "parameter.h"
#include "io.h"
#include <string>
#include <map>


using namespace std;


map<string, parameter> parameters;
FIL parameterFile;


void parameterInit(void) {
	// open file
	if( !sdCardInited() )
		return;

	if( f_open(&parameterFile, "/parameters.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS ) != FR_OK )
		return;

	// read parameters
	/*TCHAR buffer[PARAMETER_MAX_NAME + PARAMETER_MAX_STRING];
	while( f_gets( buffer, PARAMETER_MAX_NAME + PARAMETER_MAX_STRING, &parameterFile ) != NULL ) {
		std::size_t position;
		std::string strBuffer(buffer);
		int Int;
		float Float;

		std::stoi(strBuffer, &position, 0);
		//if()
		std::stof(strBuffer, &position);
	}*/

	std::string str1 = "45";
	std::string str2 = "3.14159";
	std::string str3 = "31337 with words";
	std::string str4 = "words and 2";

	//int myint1 = std::stoi(str1);
	//int myint2 = std::stoi(str2);
	//int myint3 = std::stoi(str3);
	// error: 'std::invalid_argument'
	// int myint4 = std::stoi(str4);

	//print("string \"%s\", %d\n\r", str1.c_str(), myint1);
	//print("string \"%s\", %d\n\r", str2.c_str(), myint2);
	//print("string \"%s\", %d\n\r", str3.c_str(), myint3);
}

bool parameterSearch( const char* name ) {
	if( parameters.find( string(name) ) != parameters.end() )
		return true;
	else
		return false;
}

parameter parameterGet( const char* name ) {
	return parameters[ string(name) ];
}

void parameterSet( const char* name, const parameter value ) {
	parameters[ string(name) ] = value;
}
