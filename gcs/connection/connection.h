#ifndef	CONNECTION_H
#define	CONNECTION_H

#include "mainwindow.h"
#include "control.h"
#include "serial.h"
#include "encoders.h"
#include "servos.h"
#include "plot.h"
#include "logger.h"
#include "mavlink_bridge_header.h"
#include "mavlink.h"


#define MAVLINK_DEFAULT_COMM		MAVLINK_COMM_0


class Connection : public QObject {
    Q_OBJECT

	public:
		inline static Connection&	instance() {
			static Connection instance;
			return instance;
		}

		/** returns connection status
		@retval	true		there is connection with firmware
		@retval	false		there isn't connection with firmware */
		bool			isConnected();

		/** sets servo output in percent
		@param	id			servo serial number
		@param	value		output level in percent 0..100% */
		void			sendServoOutput(int id, double value);

		/** sets servo power status
		@param	status		power status
			@arg	TRUE		enable servo power
			@arg	FALSE		disable servo power */
		void			sendServoPowerStatus(bool status);

		/** start/stop internal code
		@param	status
			@arg	TRUE		start
			@arg	FALSE		pause */
		void			userCodeRun(bool status);

		/** run bootloader */
		void            jumpToBootloader();

	signals:
		void            connected();
		void            disconnected();

		/** User code star/stop signal received from UAV.
		@param	status
			@arg	TRUE		user code started
			@arg	FALSE		user code stopped */
		void            userCodeRunStatusReceived(bool status);

	private slots:
		void			parseSerial(const QByteArray&);
		void			firmwareConnect();
		void			firmwareDisconnect();

	private:
						Connection(QObject *parent = 0);
					   ~Connection();
						Connection(Connection const&);
						Connection& operator= (Connection const&);
		mavlink_message_t	mavlink_message;
		mavlink_status_t	mavlink_status;
		QTimer*			timer;

		/** connection status. true if there is connection with firmware, false otherwise */
		bool			status;
};


#endif // CONNECTION_H
