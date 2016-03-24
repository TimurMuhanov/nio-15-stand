#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <functional>


MainWindow* MainWindow::_instance;
Ui::MainWindow*  MainWindow::_ui;


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent) {

	_instance = this;

	_ui = new Ui::MainWindow;
	_ui->setupUi(this);

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
