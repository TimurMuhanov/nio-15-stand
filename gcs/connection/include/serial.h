#ifndef	SERIAL_H
#define	SERIAL_H


#include <QSerialPort>
#include <QSerialPortInfo>
#include <QActionGroup>
#include <QThread>
#include <QMutex>


class Serial : public QObject {
    Q_OBJECT

    public:
        static Serial&			instance();
        static bool             isOpened();

        /** Open @p port at @p baud.
        @note Non thread safe!
        @param      port        system serial port name (COM1, /dev/tty1, etc)
        @param      baud        serial port baud rate */
        Q_INVOKABLE
        static bool             open(const QString& port, int baud=9600);

        /** Send @p data from serial port.
        @note Non thread safe!
        @param      data        data to send */
        Q_INVOKABLE
        static void             write(const QByteArray& data);

    signals:
        void					opened();
        void					closed();
        void					available(const QByteArray& data);

    private:
                                Serial(QObject *parent = 0);
                               ~Serial();
                                Serial(Serial const&);
                                Serial& operator= (Serial const&);
        void					close();
        void					readData();

        QSerialPort*			port;
        static QThread         _thread;
        static QMutex          _mutex;
};


#endif // SERIAL_H
