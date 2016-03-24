#include "loader.h"
#include "serial.h"
#include "connection.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

#define ACK             0x79
#define NACK            0x1F

#define CMD_GET         0x00
#define CMD_CONNECT     0x7F
#define CMD_GO          0x21
#define CMD_WRITE       0x31
#define CMD_ERASE       0x44


Loader::Loader() {

    _firmwareFile = 0;
    _thread = 0;

    _acknowledgement = false;
    _threadRunning = false;

    connect(
        MainWindow::ui().firmwareChooseButton,
        &QPushButton::clicked,
        this,
        &Loader::selectFile );

    connect(
        MainWindow::ui().firmwareUploadButton,
        &QPushButton::clicked,
        this,
        &Loader::start );
}

Loader::~Loader() {
    if( _threadRunning ) {
        _response.wakeAll();
        _thread->terminate();
        //_thread->wait();
    }
}


Loader& Loader::instance() {
   static Loader instance;
   return instance;
}

void Loader::start() {
	Connection::instance().jumpToBootloader();
	// prepare thred
    _thread = new QThread();
    moveToThread(_thread);

    connect(
        _thread,
        &QThread::started,
        this,
        &Loader::process );
    connect(
        _thread,
        &QThread::finished,
        this,
        &Loader::end );
    connect(
        _thread,
        &QThread::finished,
        _thread,
        &QThread::deleteLater );
    connect(
        this,
        &Loader::success,
        _thread,
        &QThread::quit );
    connect(
        this,
        &Loader::error,
        _thread,
        &QThread::quit );

    connect(
        &Serial::instance(),
        &Serial::available,
        this,
        &Loader::receive,
        Qt::DirectConnection );

	//qDebug() << "Loader::flash" << QThread::currentThreadId();

    _thread->start();
}

void Loader::selectFile() {
//	qDebug() << "select file";
    // open file
    _firmwareFile = new QFile(this);
    _firmwareFile->setFileName( QFileDialog::getOpenFileName(
                                    &MainWindow::instance(),
                                    tr("Open Firmware"),
                                    "",
                                    tr("Firmware File (*.hex)") ) );

    if( !_firmwareFile->open(QIODevice::ReadOnly) ) {
        delete _firmwareFile;
        return;
    }

    MainWindow::ui().firmwareStatusLabel->setText("File opened");

    // parse file
    if( !parse() ) {
        delete _firmwareFile;
        return;
    }
    delete _firmwareFile;

    MainWindow::ui().firmwareStatusLabel->setText("File parsed, ready to upload");
    MainWindow::ui().firmwareUploadButton->setEnabled(true);
}

void Loader::process() {
    _threadRunning = true;
    QMetaObject::invokeMethod( MainWindow::ui().firmwareChooseButton, "setEnabled", Q_ARG( bool, false ) );
	//qDebug() << "Loader::process" << QThread::currentThreadId();

	// connect
    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG( QString, "Connecting..." ) );
	//qDebug() << "Loader::process connecting";
    if( !send( {CMD_CONNECT} ) ) {
        emit error();
        return;
    }
	//qDebug() << "Loader::process connected";

    //send( {CMD_GET} );

    // erase all pages
    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG( QString, "Erasing..." ) );
	//qDebug() << "Loader::process erasing";
    if( !send( {CMD_ERASE, (char)0xFF-CMD_ERASE} ) ) {
        emit error();
        return;
    }
	//qDebug() << "Loader::process erasing1";
    if( !send( {(char)0xFF, (char)0xFF, (char)0x00} ) ) {
        emit error();
        return;
    }
	//qDebug() << "Loader::process erased";

    // write image
	//qDebug() << "Loader::process flashing";
    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG( QString, "Flashing..." ) );
    for(uint address: _firmwareImage.keys() ) {
        static int progress = 0;
        ++progress;
        QMetaObject::invokeMethod( MainWindow::ui().firmwareUploadProgressBar, "setValue", Q_ARG( int, (float)progress/_firmwareImage.size()*100 ) );

		//qDebug() << "Loader::process sending write command";
        if( !send( {(char)CMD_WRITE, (char)(0xFF-CMD_WRITE)} ) ) {
            emit error();
            return;
        }
		//qDebug() << "Loader::process sending address";
        if( !send( {(char)((address >> 24)&0xFF), (char)((address >> 16)&0xFF), (char)((address >> 8)&0xFF), (char)(address&0xFF)}, true ) ) {
            emit error();
            return;
        }
        QByteArray data = _firmwareImage[address];
        data.prepend(_firmwareImage[address].length());
		//qDebug() << "Loader::process sending data";
        if( !send( data, true ) ) {
            emit error();
            return;
        }
		//qDebug() << "Loader::process write succes";
    }

    // go to firmware
    send( {CMD_GO, (char)0xFF-CMD_GO} );

    emit success();
}

void Loader::end() {
    _threadRunning = false;
    disconnect(
        &Serial::instance(),
        &Serial::available,
        this,
        &Loader::receive );

    QMetaObject::invokeMethod( MainWindow::ui().firmwareChooseButton, "setEnabled", Q_ARG( bool, true ) );
    QMetaObject::invokeMethod( MainWindow::ui().firmwareUploadButton, "setEnabled", Q_ARG( bool, false ) );
    QMetaObject::invokeMethod( MainWindow::ui().firmwareStatusLabel, "setText", Q_ARG( QString, "Success!" ) );
    QMetaObject::invokeMethod( MainWindow::ui().firmwareUploadProgressBar, "setValue", Q_ARG( int, 0 ) );

	//qDebug() << "Loader::end" << QThread::currentThreadId();
}

void Loader::receive(const QByteArray &data) {
	//qDebug() << "Loader::receive" << data.toHex();
	if( data[0] == 0xfe ) return;
    _mutex.lock();
    _acknowledgement = data[0] == ACK;
    _response.wakeAll();
	_mutex.unlock();
}

void Loader::test() {
	Connection::instance().jumpToBootloader();
}


// :LLAAAATTDD...DDCC<CR&LF>
bool Loader::parse() {
	uint baseAddress = 0;
		uint newAddress = 0;
		uint address = 0;
		uint index = 0;
		QByteArray line;

		_firmwareImage.clear();

		while( (line = QByteArray::fromHex(_firmwareFile->readLine()) ).length() ) {
			uint8_t length = line[0];
			uint16_t addr = ((line[1] << 8)&0xFF00) | ((line[2]&0x00FF));
			uint8_t sum = 0;
			for(uint i=0; i<(uint)5+length; i++)
				sum += line[i];
			if( sum != 0 )
				return false;
			switch( line[3] ) {
				case 0:             // data record
					address = baseAddress << 16 | addr;
					if( index%8 == 0 )
						newAddress = address;
					//tmp[baseAddress << 16 | addr] = line.mid(4,length);
					_firmwareImage[newAddress].append( line.mid(4,length) );
					//qDebug() << "Loader::parse" << newAddress << _firmwareImage[newAddress].toHex();
					++index;
					break;
				case 1:             // file end
					return true;
				case 4:             // base address
					baseAddress = line[4] << 8 | line[5];
					break;
			}
		}

		return false;
}

bool Loader::send(std::initializer_list<char> list, bool addChecksum) {
    QByteArray data;
    for(char c : list)
        data.append(c);

    return send(data, addChecksum);
}

bool Loader::send(QByteArray data, bool addChecksum) {
    if( addChecksum ) {
        char checksum = 0;
        for(char c : data)
            checksum ^= c;
        data.append(checksum);
    }

    _acknowledgement = false;
    uint tries = 20;
    while(tries-- && !_acknowledgement) {
        QMetaObject::invokeMethod( &Serial::instance(), "write", Qt::BlockingQueuedConnection, Q_ARG( QByteArray, data ) );
		//qDebug() << "Loader::send" << data.toHex();
        _mutex.lock();
		if( _response.wait(&_mutex, 2000) ) {
			if( _acknowledgement ==true ) {
				_mutex.unlock();
				return true;
			}
        }
        _mutex.unlock();
    }
	return false;
}
