#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QThread>
#include "qcustomplot.h"
#include "calculator.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
							MainWindow(QWidget *parent = 0);
							~MainWindow();
	static MainWindow&		instance();
	static Ui::MainWindow&	ui();
	void					reset();

public slots:
	void					plotUpdate();
	void					plotToggle(bool);
	void					plotAdd(QString name, double key, double value);
private:
	QString					getNewColor();
	QCheckBox*				getCheckBox(QString name);
	QString					getName(QCheckBox* checkBox);

	static MainWindow*		_instance;
	static Ui::MainWindow*	_ui;

	QTimer*					plotUpdateTimer;
	QMap<QString, bool>		colors;
	QList<QCPGraph*>		plotList;
};


#endif // MAINWINDOW_H
