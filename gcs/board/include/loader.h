#ifndef	LOADER_H
#define	LOADER_H


#include <QObject>
#include <QFile>
#include <QMutex>
#include <QWaitCondition>


class Loader : public QObject {
    Q_OBJECT
                                Loader();
                               ~Loader();

    public:
        static Loader&          instance();

    private:
        void                    start();
        void                    selectFile();
        void                    receive(const QByteArray& data);
        bool                    send(uint8_t cmd);
        void                    send(const QByteArray& data);
        bool                    get(uint8_t cmd, unsigned long timeout = 1000);
        QByteArray              int2array(int number);

        QByteArray             _firmwareData;
        static const uint8_t   _begin = 0xFE;
        static const uint8_t   _connect = 0x7F;
        static const uint8_t   _go = 0x21;
        static const uint8_t   _write = 0x31;
        static const uint8_t   _erase = 0x44;
        static const uint8_t   _ack = 0x79;
        static const uint8_t   _nack = 0x1F;
        static const uint8_t   _unknown = 0x55;

        static const uint32_t  _addressBase = 0x08040000;
        static QByteArray      _pack;
        static const int       _packLength = 1024;
        static QMutex          _mutex;
        static QByteArray      _responce;
        static QWaitCondition  _responceReceived;

        static QThread         _thread;
};


#endif // LOADER_H
