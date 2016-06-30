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
        void					updateSerialPorts();
        void					updateSerialBauds();
        void					menuChanged(QAction* action);
        void					checkSerialPorts();
        void					addSerialPort(const QString& portName);
        void					removeSerialPort(const QString& portName);

		static MainWindow*		_instance;
		static Ui::MainWindow*	_ui;

        static QActionGroup*    _serialPortActionGroup;
        static QActionGroup*	_serialBaudActionGroup;
        static QAction*			_serialDisconnectAction;
        static QTimer*          _serialUpdater;
};

#endif // MAINWINDOW_H
