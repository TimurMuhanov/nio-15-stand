#include "loader.h"
#include "serial.h"
#include "connection.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"




QByteArray Loader::_pack;
QThread Loader::_thread;
qint64 Loader::bg;


Loader::Loader() {

//    connect(
//        MainWindow::ui().firmwareChooseButton,
//        &QPushButton::clicked,
//        this,
//        &Loader::selectFile );

    moveToThread(&_thread);
    _thread.start();

    connect( MainWindow::ui().firmwareUploadButton, &QPushButton::clicked, this, &Loader::start );
    MainWindow::ui().firmwareUploadButton->setEnabled(true);
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
//	Connection::instance().jumpToBootloader();
    qDebug() << "Loader::start()" << thread() << QThread::currentThread() << QApplication::instance()->thread();

    _firmwareFile.setFileName("C:/nio15/bootloader/firmware.bin");

    if( !_firmwareFile.open(QIODevice::ReadOnly) ) {
        qDebug() << "File open error" << _firmwareFile.errorString();
        return;
    }
    QByteArray data = _firmwareFile.readAll();
    _firmwareFile.close();

    QMetaObject::invokeMethod( MainWindow::ui().firmwareUploadProgressBar, "setMaximum", Q_ARG(int, data.length()/1024));

    // get connection
    if( !get( _connect ) ) {
        qDebug() << "can't connected";
        return;
    }
    qDebug() << "connected";
    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG(QString, "Connected" ) );

    // erase
    if( !send(_erase) ) {
        qDebug() << "can't send erase";
        return;
    }
    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG(QString, "Erasing..." ) );
    send( int2array(data.length()) );
    if( !get( _ack ) ) {
        qDebug() << "can't erase";
        return;
    }
    qDebug() << "erased";

    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG(QString, "Flashing..." ) );

    // write data
    int index = 0;
    _pack.clear();
    while( index < data.length() ) {
        if( !send(_write) ) {
            qDebug() << "can't send write";
            continue;
        }
        char checksum = 0;
        _pack.append( int2array( _addressBase+index ) );
        _pack.append( data.mid(index, _packLength) );
        for( auto c : _pack ) {
            checksum ^= c;
        }
        _pack.append( QByteArray(1,checksum) );
        send( _pack );
        if( !get( _ack ) ) {
            qDebug() << "can't send pack";
            continue;
        }
        _pack.clear();
        index += _packLength;
//        qDebug() << "written" << _addressBase+index;
        QMetaObject::invokeMethod( MainWindow::ui().firmwareUploadProgressBar, "setValue", Q_ARG(int, index/1024));
    }
}

//void Loader::selectFile() {
////	qDebug() << "select file";
//    // open file
//    _firmwareFile.setFileName( QFileDialog::getOpenFileName(
//                                    &MainWindow::instance(),
//                                    tr("Open Firmware"),
//                                    "",
//                                    tr("Firmware File (*.bin)") ) );

//    if( !_firmwareFile.open(QIODevice::ReadOnly) ) {
//        return;
//    }

//    MainWindow::ui().firmwareStatusLabel->setText("Ready to upload");
//    MainWindow::ui().firmwareUploadButton->setEnabled(true);
//}

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

bool Loader::send(const QByteArray& data) {
    QMetaObject::invokeMethod( &Serial::instance(), "write", Q_ARG(QByteArray, data));
    qDebug() << "send" << data.toHex();
}

bool Loader::get(uint8_t cmd) {
    QByteArray responce = Serial::readBlocking(1);
    switch( cmd ){
        case _erase:
        case _write:
        case _go:
            return false;
        case _connect: {
            qDebug() << "get connect" << responce.toHex() << QDateTime::currentMSecsSinceEpoch() - bg;
            if( responce[0] == cmd ) {
                send(_ack);
                return true;
            } else {
                send(_nack);
                return false;
            }
        }
        case _ack:
        case _nack: {
            bg = QDateTime::currentMSecsSinceEpoch();
            bool returnValue = responce[0] == cmd;
            qDebug() << "get ack" << responce.toHex() << QDateTime::currentMSecsSinceEpoch() - bg;
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
