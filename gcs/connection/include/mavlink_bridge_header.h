#ifndef MAVLINK_BRIDGE_HEADER_H
#define MAVLINK_BRIDGE_HEADER_H
 
#define MAVLINK_USE_CONVENIENCE_FUNCTIONS

#include "mavlink_types.h"

extern mavlink_system_t mavlink_system;

#define	MAVLINK_SEND_UART_BYTES(chan, buf, len)		QMetaObject::invokeMethod( &Serial::instance(), "write", Q_ARG(QByteArray, QByteArray((const char*)buf, (int)len)) )

#endif /* MAVLINK_BRIDGE_HEADER_H */

