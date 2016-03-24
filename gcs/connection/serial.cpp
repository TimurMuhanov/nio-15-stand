#include "serial.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"


Serial::Serial(QObject *parent) : QObject(parent) {
	portActionGroup = new QActionGroup( MainWindow::ui().menuPort );
	QObject::connect(
		portActionGroup,
		SIGNAL(triggered(QAction*)),
		SLOT(menuChanged(QAction*) ) );
	baudActionGroup = new QActionGroup( MainWindow::ui().menuPort );
	QObject::connect(
		baudActionGroup,
		SIGNAL(triggered(QAction*)),
		SLOT(menuChanged(QAction*) ) );

	updatePorts();
	updateBauds();

	port = new QSerialPort(this);
	QObject::connect(
		port,
		SIGNAL(readyRead()),
		SLOT(readData()) );

	updater = new QTimer(this);
	QObject::connect(
		updater,
		SIGNAL(timeout()),
		SLOT(checkPorts()) );
	updater->start(1000);

	QString previousSessionBaud( MainWindow::settings().value("settings/serial/baud").toString() );
	QString previousSessionPort( MainWindow::settings().value("settings/serial/port").toString() );
	foreach (QAction* action, baudActionGroup->actions()) {
		if(action->text() == previousSessionBaud )
			action->setChecked(true);
	}
	foreach (QAction* action, portActionGroup->actions()) {
		if(action->text() == previousSessionPort ) {
			action->activate(QAction::Trigger);
		}
	}
}

Serial::~Serial() {
	close();
	delete port;
}

Serial& Serial::instance() {
   static Serial instance;
   return instance;
}

bool Serial::isOpened() {
    return port->isOpen();
}

QByteArray Serial::readBlocking(int bytes) {
    do {
        if( instance().port->waitForReadyRead( -1 ) == false ) {
            return QByteArray();
        }
    } while( instance().port->bytesAvailable() < bytes );

    return instance().port->read( bytes );
}

void Serial::readData() {
    QByteArray data = port->readAll();
	//qDebug() << "Serial::readData" << data.toHex();
    emit available(data);
}

void Serial::updatePorts() {
	MainWindow::ui().menuPort->clear();
	for( QAction* action : portActionGroup->actions() ) {
		portActionGroup->removeAction(action);
	}

	disconnectAction = new QAction("Disconnect", MainWindow::ui().menuPort);
	disconnectAction->setCheckable(true);
	disconnectAction->setChecked(true);
	disconnectAction->setActionGroup(portActionGroup);
	MainWindow::ui().menuPort->addAction(disconnectAction);

	for( QSerialPortInfo port : QSerialPortInfo::availablePorts() ) {
		QAction* action = new QAction(port.portName(), MainWindow::ui().menuPort);
		action->setCheckable(true);
		action->setActionGroup(portActionGroup);
		MainWindow::ui().menuPort->addAction(action);
	}
}

void Serial::updateBauds() {
	MainWindow::ui().menuBaudrate->clear();
	for( QAction* action : baudActionGroup->actions() ) {
		baudActionGroup->removeAction(action);
	}

	for( qint32 baud : QSerialPortInfo::standardBaudRates() ) {
		if( baud < 9600 || baud > 115200 ) continue;
		QAction* action = new QAction(QString::number(baud), MainWindow::ui().menuBaudrate);
		action->setCheckable(true);
		action->setActionGroup(baudActionGroup);
		MainWindow::ui().menuBaudrate->addAction(action);
	}
}

void Serial::menuChanged(QAction* action) {
	Q_UNUSED(action)

	close();

	if( portActionGroup->checkedAction() != 0 &&
		portActionGroup->checkedAction() != disconnectAction &&
		baudActionGroup->checkedAction() != 0 ) {

		open();
		return;
	}
}

void Serial::checkPorts() {
	// check to new ports
	for( QSerialPortInfo port : QSerialPortInfo::availablePorts() ) {
		bool founded = false;
		for( QAction* action : portActionGroup->actions() ) {
			if( port.portName() == action->text() )
				founded = true;
		}
		if(!founded)
			addPort( port.portName() );
	}

	// check to removed ports
	for( QAction* action : portActionGroup->actions() ) {
		if(action == disconnectAction)
			continue;

		bool founded = false;
		for( QSerialPortInfo port : QSerialPortInfo::availablePorts() ) {
			if( port.portName() == action->text() )
				founded = true;
		}
		if(!founded)
			removePort( action->text() );
	}
}

void Serial::addPort(const QString& portName) {
	QAction* action = new QAction(portName, MainWindow::ui().menuPort);
	action->setCheckable(true);
	action->setActionGroup(portActionGroup);
	MainWindow::ui().menuPort->addAction(action);

	//updatePorts();
	//qDebug() << "add port" << portName << MainWindow::ui().menuPort->actions() << portActionGroup->actions();
}

void Serial::removePort(const QString& portName ) {
	for( QAction* action : portActionGroup->actions() ) {
		if( portName == action->text() ) {
			portActionGroup->removeAction(action);
			MainWindow::ui().menuPort->removeAction(action);
		}
	}

	//updatePorts();
	//qDebug() << "remove port" << portName << MainWindow::ui().menuPort->actions() << portActionGroup->actions();
}

void Serial::write(const QByteArray& data) {
	if(port->isOpen()) {
		//qDebug() << "Serial::write" << data.toHex();
		port->write(data);
    }
}

bool Serial::open() {
	port->setPortName( portActionGroup->checkedAction()->text() );
	port->setBaudRate( baudActionGroup->checkedAction()->text().toInt() );
	port->setDataBits( QSerialPort::Data8 );
    port->setParity( QSerialPort::EvenParity );
	port->setStopBits( QSerialPort::OneStop );
	port->setFlowControl( QSerialPort::NoFlowControl );
	if( port->open( QIODevice::ReadWrite ) ) {
		MainWindow::settings().setValue("settings/serial/port", portActionGroup->checkedAction()->text() );
		MainWindow::settings().setValue("settings/serial/baud", baudActionGroup->checkedAction()->text() );

		emit opened();
        //qDebug() << "opened" << port->portName() << port->baudRate();
		return true;
	} else {
		//qDebug() << "fail opened" << port->portName();
		disconnectAction->setChecked(true);
		return false;
	}
}

void Serial::close() {
	if(port->isOpen()) {
		port->close();
        //qDebug() << "closed" << port->portName();
		emit closed();
	}
}
