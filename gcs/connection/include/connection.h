#ifndef	CONNECTION_H
#define	CONNECTION_H


#include <QObject>
#include "serial.h"
#include "mavlink_bridge_header.h"
#include "mavlink.h"
//#include "parameters.h"
#include <cmath>
#include <math.h>


#define MAVLINK_DEFAULT_COMM		MAVLINK_COMM_0
#define RAD_DEG(x)					((x)/3.1415*180.0)
#define DEG_RAD(x)					((x)/180.0*3.1415)


enum class Value : uint {
	Roll,
	Pitch,
	Yaw,
	Q0,
	Q1,
	Q2,
    Q3
};

enum class ValueVector : uint {
    Accel,
    Gyro,
    Mag
};


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

        void			settingsRequest();
        void			settingsSend( std::string, std::string );
        void			settingsRemove(std::string key);

	signals:
		void            connected();
		void            disconnected();
		void            valueReceived( Value, double );
        void            valueVectorReceived( ValueVector, double, double, double );
        void            settingReceived( std::string, std::string );
        void            settingRemoved( std::string );

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
