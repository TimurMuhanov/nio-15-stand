#ifndef MAVLINK_BRIDGE_HEADER_H
#define MAVLINK_BRIDGE_HEADER_H
 
#define MAVLINK_USE_CONVENIENCE_FUNCTIONS

#include "mavlink_types.h"
#include "Telemetry.h"

extern mavlink_system_t mavlink_system;

//#define	MAVLINK_SEND_UART_BYTES(chan, buf, len)		Telemetry::send( (const u8*)"asdfasfdasdfsadfsadfsadfsadfasdfasdfasdfasfdasdfasdf\n\r", sizeof("asdfasfdasdfsadfsadfsadfsadfasdfasdfasdfasfdasdfasdf\n\r") )
#define	MAVLINK_SEND_UART_BYTES(chan, buf, len)		Telemetry::instance().send( (const u8*)buf, len )
//#define	MAVLINK_SEND_UART_BYTES(chan, buf, len)		sendToTerminal( (const u8*)buf, len )

#endif /* MAVLINK_BRIDGE_HEADER_H */

