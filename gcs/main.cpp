#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serial.h"
#include "connection.h"
#include "plot.h"
#include "logger.h"
#include "control.h"
#include "loader.h"
#include "settings.h"
#include <QApplication>





int main(int argc, char *argv[]) {
    qSetMessagePattern("%{function}: (%{threadid}) %{message}");

	QApplication app(argc, argv);

	MainWindow mainWindow;

	Serial::instance();
	Connection::instance();
    Logger::instance();
	Plot::instance();
	Control::instance();
    Loader::instance();
    Settings::instance();

	mainWindow.show();

    return app.exec();
}
