#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serial.h"
#include "connection.h"
#include "plot.h"
#include "control/control.h"
#include "loader.h"
#include <QApplication>





int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MainWindow mainWindow;

	Serial::instance();
	Connection::instance();
	Plot::instance();
	Control::instance();
    Loader::instance();

	mainWindow.show();

	return app.exec();
}
