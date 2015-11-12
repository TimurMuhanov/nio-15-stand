#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSettings>
#include "visualisation.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

	public:
								MainWindow(QWidget *parent=0);
							   ~MainWindow();

		static MainWindow&		instance();
		static Ui::MainWindow&	ui();
		static QSettings&		settings();
	private:
		static MainWindow*		_instance;
		static Ui::MainWindow*	_ui;
};

#endif // MAINWINDOW_H
