#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <functional>


MainWindow*      MainWindow::_instance;
Ui::MainWindow*  MainWindow::_ui;
QActionGroup*    MainWindow::_serialPortActionGroup;
QActionGroup*	 MainWindow::_serialBaudActionGroup;
QAction*		 MainWindow::_serialDisconnectAction;
QTimer*          MainWindow::_serialUpdater;


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent) {

	_instance = this;

	_ui = new Ui::MainWindow;
	_ui->setupUi(this);


    // serial
    _serialPortActionGroup = new QActionGroup( MainWindow::ui().menuPort );
    connect( _serialPortActionGroup, &QActionGroup::triggered, this, &MainWindow::menuChanged );
    _serialBaudActionGroup = new QActionGroup( MainWindow::ui().menuPort );
    connect( _serialBaudActionGroup, &QActionGroup::triggered, this, &MainWindow::menuChanged );

    _serialUpdater = new QTimer(this);
    connect( _serialUpdater, &QTimer::timeout, this, &MainWindow::checkSerialPorts);
    _serialUpdater->start(1000);

    updateSerialPorts();
    updateSerialBauds();

    QString previousSessionBaud( MainWindow::settings().value("settings/serial/baud").toString() );
    QString previousSessionPort( MainWindow::settings().value("settings/serial/port").toString() );
    foreach( QAction* action, _serialBaudActionGroup->actions() ) {
        if(action->text() == previousSessionBaud )
            action->setChecked(true);
    }
    foreach( QAction* action, _serialPortActionGroup->actions() ) {
        if(action->text() == previousSessionPort ) {
            action->activate(QAction::Trigger);
        }
    }

//    std::bind();
}

MainWindow::~MainWindow() {
	delete _ui;
}

MainWindow& MainWindow::instance() {
	return *_instance;
}

Ui::MainWindow& MainWindow::ui() {
	return * _ui;
}

QSettings& MainWindow::settings() {
	static QSettings settings("NIO-15", "GCS");
	settings.sync();
    return settings;
}

void MainWindow::updateSerialPorts() {
    MainWindow::ui().menuPort->clear();
    for( QAction* action : _serialPortActionGroup->actions() ) {
        _serialPortActionGroup->removeAction(action);
    }

    _serialDisconnectAction = new QAction("Disconnect", MainWindow::ui().menuPort);
    _serialDisconnectAction->setCheckable(true);
    _serialDisconnectAction->setChecked(true);
    _serialDisconnectAction->setActionGroup(_serialPortActionGroup);
    MainWindow::ui().menuPort->addAction( _serialDisconnectAction );

    for( QSerialPortInfo port : QSerialPortInfo::availablePorts() ) {
        QAction* action = new QAction(port.portName(), MainWindow::ui().menuPort);
        action->setCheckable(true);
        action->setActionGroup(_serialPortActionGroup);
        MainWindow::ui().menuPort->addAction( action );
    }
}

void MainWindow::updateSerialBauds() {
    MainWindow::ui().menuBaudrate->clear();
    for( QAction* action : _serialBaudActionGroup->actions() ) {
        _serialBaudActionGroup->removeAction(action);
    }

    for( qint32 baud : QSerialPortInfo::standardBaudRates() ) {
        if( baud < 9600 || baud > 115200 ) continue;
        QAction* action = new QAction(QString::number(baud), MainWindow::ui().menuBaudrate);
        action->setCheckable(true);
        action->setActionGroup(_serialBaudActionGroup);
        MainWindow::ui().menuBaudrate->addAction( action );
    }
}

void MainWindow::menuChanged(QAction* action) {
    Q_UNUSED(action)

    if( _serialPortActionGroup->checkedAction() != 0 &&
        _serialPortActionGroup->checkedAction() != _serialDisconnectAction &&
        _serialBaudActionGroup->checkedAction() != 0 )
    {
        QString port = _serialPortActionGroup->checkedAction()->text();
        int baud = _serialBaudActionGroup->checkedAction()->text().toInt();
        bool isOpened = false;
        QMetaObject::invokeMethod( &Serial::instance(), "open", Qt::BlockingQueuedConnection, Q_RETURN_ARG(bool, isOpened), Q_ARG( QString, port ), Q_ARG( int, baud ) );
        if( isOpened ) {
            MainWindow::settings().setValue("settings/serial/port", _serialPortActionGroup->checkedAction()->text() );
            MainWindow::settings().setValue("settings/serial/baud", _serialBaudActionGroup->checkedAction()->text() );
        } else {
            _serialDisconnectAction->setChecked(true);
        }
    }
}

void MainWindow::checkSerialPorts() {
    // check to new ports
    for( QSerialPortInfo port : QSerialPortInfo::availablePorts() ) {
        bool founded = false;
        for( QAction* action : _serialPortActionGroup->actions() ) {
            if( port.portName() == action->text() ) {
                founded = true;
            }
        }
        if(!founded) {
            addSerialPort( port.portName() );
        }
    }

    // check to removed ports
    for( QAction* action : _serialPortActionGroup->actions() ) {
        if(action == _serialDisconnectAction) {
            continue;
        }

        bool founded = false;
        for( QSerialPortInfo port : QSerialPortInfo::availablePorts() ) {
            if( port.portName() == action->text() ) {
                founded = true;
            }
        }
        if(!founded) {
            removeSerialPort( action->text() );
        }
    }
}

void MainWindow::addSerialPort(const QString& portName) {
    QAction* action = new QAction(portName, MainWindow::ui().menuPort);
    action->setCheckable(true);
    action->setActionGroup(_serialPortActionGroup);
    MainWindow::ui().menuPort->removeAction( action );

    //updatePorts();
    //qDebug() << "add port" << portName << MainWindow::ui().menuPort->actions() << _serialPortActionGroup->actions();
}

void MainWindow::removeSerialPort(const QString& portName ) {
    for( QAction* action : _serialPortActionGroup->actions() ) {
        if( portName == action->text() ) {
            _serialPortActionGroup->removeAction(action);
            MainWindow::ui().menuPort->removeAction( action );
        }
    }

    //updatePorts();
    //qDebug() << "remove port" << portName << MainWindow::ui().menuPort->actions() << _serialPortActionGroup->actions();
}
