/*#include "led.h"




char buf[ IO_WRITE_BUFFER ];
u32 len;




void print(const char* string, ...) {
	va_list ap;
	
	va_start( ap, string );
	
	len = vsnprintf( buf, IO_WRITE_BUFFER, string, ap );
	
	sdWrite( &BOARD_TERMINAL_SD, (const u8*) buf, len );
	
	va_end ( ap );
}





void send(const u8* buf, const u32 len) {
	sdAsynchronousWrite( &BOARD_TERMINAL_SD, buf, len );
}




void sendToTelemethry(const u8* buf, const u32 len) { 
	sdAsynchronousWrite( &BOARD_TELEMETHRY_SD, buf, len );
}




void receiveFromTelemethry(u8* buf, const u32 len) {
	sdRead( &BOARD_TELEMETHRY_SD, buf, len );
}




u32 availableFromTelemethry(void) {
	return chQSpaceI( &BOARD_TELEMETHRY_SD.oqueue );
}
*/