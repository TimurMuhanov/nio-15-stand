#include "loader.h"
#include "serial.h"
#include "connection.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"




QByteArray Loader::_pack;
QMutex Loader::_mutex;
QByteArray Loader::_responce;
QWaitCondition Loader::_responceReceived;
QThread Loader::_thread;


Loader::Loader() {

    moveToThread(&_thread);
    _thread.start();

    connect( MainWindow::ui().firmwareChooseButton, &QPushButton::clicked, this, &Loader::selectFile, Qt::DirectConnection );
    connect( MainWindow::ui().firmwareUploadButton, &QPushButton::clicked, this, &Loader::start );
    connect( &Serial::instance(), &Serial::available, this, &Loader::receive, Qt::DirectConnection );
}

Loader::~Loader() {
    _thread.terminate();
    _thread.wait();
}


Loader& Loader::instance() {
   static Loader instance;
   return instance;
}

void Loader::start() {
    Connection::instance().jumpToBootloader();

    // get connection
    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG(QString, "Connecting..." ) );
    if( !get( _connect, 10000 ) ) {
        qDebug() << "can't connected";
        return;
    }
//    qDebug() << "connected";
    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG(QString, "Connected" ) );

    // erase
    if( !send(_erase) ) {
        qDebug() << "can't send erase";
        return;
    }
    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG(QString, "Erasing..." ) );
    send( int2array(_firmwareData.length()) );
    if( !get( _ack, 20000 ) ) {
        qDebug() << "can't erase";
        return;
    }
//    qDebug() << "erased";

    QMetaObject::invokeMethod( MainWindow::ui().firmwareUploadProgressBar, "setMaximum", Q_ARG(int, _firmwareData.length()/1024));
    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG(QString, "Flashing..." ) );

    // write data
    int index = 0;
    while( index < _firmwareData.length() ) {
//        qDebug() << "send write";
        if( !send(_write) ) {
            qDebug() << "can't send write";
            continue;
        }
        char checksum = 0;
        _pack.clear();
        _pack.append( int2array( _addressBase+index ) );
        _pack.append( _firmwareData.mid(index, _packLength) );
        if( _pack.count() < _packLength+4 ) {
            _pack.append( QByteArray( _packLength+4-_pack.count(), 0xFF ) );
        }
        for( auto c : _pack ) {
            checksum ^= c;
        }
        _pack.append( QByteArray(1,checksum) );
//        qDebug() << "send pack";
        send( _pack );
        _pack.clear();
        if( !get( _ack ) ) {
            qDebug() << "can't send pack";
            continue;
        }
        index += _packLength;
//        qDebug() << "written" << QString::number(_addressBase+index, 16);
        QMetaObject::invokeMethod( MainWindow::ui().firmwareUploadProgressBar, "setValue", Q_ARG(int, index/1024));
    }

    // jump
    if( !send(_go) ) {
        qDebug() << "can't jump";
        QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG(QString, "Error!" ) );
        return;
    }
    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG(QString, "Success!" ) );
}

void Loader::selectFile() {
    QString lastPath( MainWindow::settings().value("loader/lastPath").toString() );
    QFile file;
    file.setFileName(  QFileDialog::getOpenFileName(
                                &MainWindow::instance(),
                                tr("Open Firmware"),
                                lastPath,
                                tr("Firmware File (*.bin)") ) );

    if( !file.open(QIODevice::ReadOnly) ) {
        qDebug() << "File open error" << file.errorString();
        return;
    }

    MainWindow::settings().setValue("loader/lastPath", QFileInfo(file).absolutePath() );

    _firmwareData = file.readAll();

    MainWindow::ui().firmwareStatusLabel->setText("Ready to upload");
    MainWindow::ui().firmwareUploadButton->setEnabled(true);
}

void Loader::receive(const QByteArray& data) {
//    qDebug() << "rc" << data.toHex();
    _mutex.lock();
    _responce = data;
    _responceReceived.wakeAll();
    _mutex.unlock();
}

bool Loader::send(uint8_t cmd) {
    switch( cmd ){
        case _write:
        case _erase:
        case _go: {
            QByteArray command;
            command.append( _begin );
            command.append( cmd );
            command.append( 0x100-cmd );
            send( command );
            return get(_ack);
        }
        case _ack:
        case _nack:
            send( QByteArray( 1,cmd ) );
            return true;
    }
}

void Loader::send(const QByteArray& data) {
    QMetaObject::invokeMethod( &Serial::instance(), "write", Q_ARG(QByteArray, QByteArray(data)));
//    Serial::instance().port->flush();
//    Serial::instance().port->waitForBytesWritten(-1);
//    bg = QDateTime::currentMSecsSinceEpoch();
//    qDebug() << "tm" << data.toHex();
}

bool Loader::get(uint8_t cmd, unsigned long timeout ) {
    switch( cmd ){
        case _erase:
        case _write:
        case _go:
            return false;
        case _connect: {
            while( 1 ) {
                _mutex.lock();
                if( _responceReceived.wait(&_mutex, timeout) ) {
                    if( _responce[0] == cmd ) {
                        send(_ack);
                        _mutex.unlock();
                        return true;
                    }
                }
                _mutex.unlock();
            }
        }
        case _ack:
        case _nack: {
//            bg = QDateTime::currentMSecsSinceEpoch();
            _mutex.lock();
            if( !_responceReceived.wait(&_mutex, timeout) ) {
                qDebug() << "Loader::get() timeout";
                _mutex.unlock();
                return false;
            }
            bool returnValue = _responce[0] == cmd;
            _mutex.unlock();
//            qDebug() << "get ack" << QDateTime::currentMSecsSinceEpoch() - bg;
            return returnValue;
        }
    }
}

QByteArray Loader::int2array(int number) {
    QByteArray array;
    for( int i=0; i<sizeof(number); i++ )
        array.prepend( (number >> (i*8)) &0xFF );
    return array;
}
