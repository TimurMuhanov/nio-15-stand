#ifndef	SERIAL_H
#define	SERIAL_H


#include "mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>


class Serial : public QObject {
    Q_OBJECT

	public:
		static Serial&			instance();
        bool                    isOpened();

	signals:
		void					opened();
		void					closed();
		void					available(const QByteArray& data);

	public slots:
		void					write(const QByteArray& data);

	private slots:
		bool					open();
		void					close();
		void					readData();

		void					updatePorts();
		void					updateBauds();
		void					menuChanged(QAction* action);
		void					checkPorts();

	private:
								Serial(QObject *parent = 0);
							   ~Serial();
								Serial(Serial const&);
								Serial& operator= (Serial const&);

		void					addPort(const QString& portName);
		void					removePort(const QString& portName);

		QSerialPort*			port;
		QActionGroup*			portActionGroup;
		QActionGroup*			baudActionGroup;
		QAction*				disconnectAction;
		QTimer*					updater;
};


#endif // SERIAL_H
