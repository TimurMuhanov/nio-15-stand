#include "serial.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"


QThread Serial::_thread;
QMutex Serial::_mutex;


Serial::Serial(QObject *parent) : QObject(parent) {
    port = new QSerialPort(this);
    connect( port, &QSerialPort::readyRead, this, &Serial::readData );

    moveToThread( &_thread );
    _thread.start();
}

Serial::~Serial() {
    _thread.terminate();
    _thread.wait();
    close();
    delete port;
}

Serial& Serial::instance() {
   static Serial instance;
   return instance;
}

bool Serial::isOpened() {
    return instance().port->isOpen();
}

bool Serial::open(const QString& name, int baud) {
    instance().close();
    instance().port->setPortName( name );
    instance().port->setBaudRate( baud );
    instance().port->setDataBits( QSerialPort::Data8 );
    instance().port->setParity( QSerialPort::NoParity );
    instance().port->setStopBits( QSerialPort::OneStop );
    instance().port->setFlowControl( QSerialPort::NoFlowControl );
    if( instance().port->open( QIODevice::ReadWrite ) ) {
        emit instance().opened();
        return true;
    } else {
        return false;
    }
}

void Serial::write(const QByteArray& data) {
    QMutexLocker mutexLocker(&_mutex);
    if( instance().port->isOpen() ) {
        instance().port->waitForBytesWritten( 10000 );
        instance().port->write( data );
    }
}

void Serial::close() {
    if(port->isOpen()) {
        port->close();
        //qDebug() << "closed" << port->portName();
        emit closed();
    }
}

void Serial::readData() {
    QByteArray data = port->readAll();
//    qDebug() << QApplication::instance()->thread() << data.toHex();
    emit available(data);
}

