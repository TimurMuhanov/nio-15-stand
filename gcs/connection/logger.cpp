#include "logger.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"


Logger::Logger(QObject *parent) : QObject(parent) {
    connect( MainWindow::ui().loggingPathButton, &QPushButton::clicked, this, &Logger::loggingPathChange );
    connect( &Connection::instance(), &Connection::connected, this, &Logger::reset );

    if( MainWindow::settings().contains( "logger/savePath" ) ) {
        _rootPath = MainWindow::settings().value( "logger/savePath" ).toString();
    } else {
        _rootPath = QDir::homePath() + "/Desktop/experiment";
        MainWindow::settings().setValue( "logger/savePath", _rootPath );
    }
    if( !QDir( _rootPath ).exists() ) {
        QDir().mkdir( _rootPath );
    }
    MainWindow::ui().loggingPathLabel->setText(_rootPath);
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
        _logs[name] = new QFile(_path + QDir::separator() + name + QString(".txt") );
        if( !_logs[name]->open(QIODevice::WriteOnly) )
            QMessageBox::information( &MainWindow::instance(), tr("Unable to open log file"), _logs[name] ->errorString());
    }

    QString line = QString::number(time, 'f', 6);
    for(double value : data) {
        line += QString("\t") + QString::number(value, 'f', 6);
    }

    _logs[name]->write( line.toLatin1()+"\n" );
}

void Logger::reset() {
    for( auto log : _logs.values() ) {
        delete log;
    }
    _logs.clear();

    _path = _rootPath + "/" + QDateTime::currentDateTime().toString("dd-MM-yyyy HH-mm-ss");
    QDir().mkdir(_path);
    MainWindow::ui().loggingPathLabel->setText(_path);
}

void Logger::loggingPathChange() {
	QString path( QFileDialog::getExistingDirectory(
		&MainWindow::instance(),
		tr("Log File Save Directory"),
        _rootPath ) );

    if( path.isNull() )
        return;

    _rootPath = path;
    MainWindow::settings().setValue( "logger/savePath", _rootPath );
    MainWindow::ui().loggingPathLabel->setText(_rootPath);
}
