#ifndef	LOADER_H
#define	LOADER_H


#include <QObject>
#include <QMap>
#include <QFile>
#include <QMutex>
#include <QWaitCondition>


class Loader : public QObject {
    Q_OBJECT

    public:
        static Loader&		instance();

    signals:
		void					success();
		void					error();

    private slots:
        void                    start();
		void                    selectFile();
        void                    process();
        void                    end();
        void                    receive(const QByteArray& data);
		void                    test();

    private:
                                Loader();
                               ~Loader();
                                //Loader(Loader const&);
                                //Loader& operator= (Loader const&);

        /* intel hex parser */
        bool                    parse();

        /* add checksum to data and send it, block until response */
        bool                    send(std::initializer_list<char>, bool addChecksum = false);
        bool                    send(QByteArray, bool addChecksum = false);
        QThread*                _thread;
        bool                    _threadRunning;
        QMap<uint,QByteArray>   _firmwareImage;
        QFile*                  _firmwareFile;
        QMutex                  _mutex;
        QWaitCondition          _response;
        bool                    _acknowledgement;
};


#endif // LOADER_H
