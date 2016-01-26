#include "logger.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"


Logger::Logger(QObject *parent) : QObject(parent) {
    QObject::connect(
		MainWindow::ui().loggingPathButton,
		SIGNAL(clicked()),
		SLOT(loggingPathChange()) );

    _path = MainWindow::settings().value( "logger/savePath" ).toString();
    if( !QDir( _path ).exists() ) {
        _path = QCoreApplication::applicationDirPath()+"/logs";
        if( !QDir( _path ).exists() ) QDir().mkdir( _path );
        MainWindow::settings().setValue( "logger/savePath", _path );	}
    MainWindow::ui().loggingPathLabel->setText(_path);
}

Logger::~Logger() {
    for( auto log : _logs.values() )
        delete log;
}

Logger& Logger::instance() {
    static Logger instance;
	return instance;
}

void Logger::addData(const QString& name, const double time, std::initializer_list<double> data) {
    if( !_logs.contains(name) ) {
        _logs[name] = new QFile(_path + QDir::separator() + name + QString(".csv") );
        if( !_logs[name]->open(QIODevice::WriteOnly) )
            QMessageBox::information( &MainWindow::instance(), tr("Unable to open log file"), _logs[name] ->errorString());
    }

    QString line = QString::number(time, 'f', 6);
    for(double value : data) {
        line += QString(",") + QString::number(value, 'f', 6);
    }

	//qDebug() << "Logger::addData" << name << line.toLatin1();
    _logs[name]->write( line.toLatin1()+"\n" );
}

void Logger::loggingPathChange() {
	QString path( QFileDialog::getExistingDirectory(
		&MainWindow::instance(),
		tr("Log File Save Directory"),
        _path ) );

    for( auto log : _logs.values() ) {
        delete log;
    }
    _logs.clear();

    _path = path;
    MainWindow::ui().loggingPathLabel->setText(_path);
    MainWindow::settings().setValue( "logger/savePath", _path );
}
