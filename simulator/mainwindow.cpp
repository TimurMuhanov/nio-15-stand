#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow* MainWindow::_instance;
Ui::MainWindow*  MainWindow::_ui;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	_instance = this;

	_ui = new Ui::MainWindow;
	_ui->setupUi(this);

	QList<QString> colorNameList = QColor::colorNames();
	foreach( QString colorName, colorNameList ) {
		if( QColor( colorName ).value() < 200 ) {
			colors[colorName] = false;
		}
	}

	_ui->plotWidget->setInteraction(QCP::iRangeDrag, true);
	_ui->plotWidget->setInteraction(QCP::iRangeZoom , true);

	plotUpdateTimer = new QTimer(this);
	QObject::connect(
		plotUpdateTimer,
		SIGNAL(timeout()),
		SLOT(plotUpdate())
	);
	plotUpdateTimer->start(20);
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

void MainWindow::reset() {
	foreach(QCPGraph* plot,	plotList) {
		plot->clearData();
	}
}

void MainWindow::plotUpdate() {
	if( !Calculator::instance().isRunning() )
		return;
	_ui->plotWidget->xAxis->rescale(true);
	_ui->plotWidget->yAxis->rescale(true);
	_ui->plotWidget->replot();
}

void MainWindow::plotToggle(bool state) {
	QString name( getName( dynamic_cast<QCheckBox*>(QObject::sender()) ) );
	foreach(QCPGraph* plot,	plotList) {
		if( plot->name() == name ) {
			plot->setVisible(state);
			MainWindow::ui().plotWidget->xAxis->rescale(true);
			MainWindow::ui().plotWidget->yAxis->rescale(true);
			MainWindow::ui().plotWidget->replot();
			return;
		}
	}
}

void MainWindow::plotAdd(QString name, double key, double value) {
	foreach(QCPGraph* plot,	plotList) {
		if( plot->name() == name ) {
			plot->addData(key, value);
			return;
		}
	}
	//qDebug() << "plotAdd" << name << key;
	plotList.append( _ui->plotWidget->addGraph() );

	QCheckBox* checkBox = MainWindow::instance().getCheckBox(name);
	plotList.back()->setName(name);
	plotList.back()->setVisible( checkBox->isChecked() );
	QString color( getNewColor() );
	QPalette palette (checkBox->palette());
	palette.setColor(QPalette::Active, QPalette::WindowText, QColor(color));
	plotList.back()->setPen(QPen(QColor( color )));
	checkBox->setPalette( palette );
	QObject::connect(
		checkBox,
		SIGNAL(toggled(bool)),
		SLOT(plotToggle(bool))
	);
}

QString MainWindow::getNewColor() {
	for( QMap<QString, bool>::iterator it=colors.begin(); it != colors.end(); it++ ) {
		if( it.value() == false ) {
			it.value() = true;
			return it.key();
		}
	}
	return QString("black");
}


QCheckBox* MainWindow::getCheckBox(QString name) {
	if( name == "mx" ) return _ui->plotMxCheckBox;
	if( name == "my" ) return _ui->plotMyCheckBox;
	if( name == "mz" ) return _ui->plotMzCheckBox;

	if( name == "wx" ) return _ui->plotWxCheckBox;
	if( name == "wy" ) return _ui->plotWyCheckBox;
	if( name == "wz" ) return _ui->plotWzCheckBox;

	if( name == "psi" ) return _ui->plotPsiCheckBox;
	if( name == "theta" ) return _ui->plotThetaCheckBox;
	if( name == "gamma" ) return _ui->plotGammaCheckBox;

	if( name == "servo1" ) return _ui->plotServo1CheckBox;
	if( name == "servo2" ) return _ui->plotServo2CheckBox;
	if( name == "servo3" ) return _ui->plotServo3CheckBox;
	if( name == "servo4" ) return _ui->plotServo4CheckBox;
	if( name == "servo5" ) return _ui->plotServo5CheckBox;

	if( name == "fi" ) return _ui->plotFiCheckBox;
	if( name == "df" ) return _ui->plotDfCheckBox;
	if( name == "da" ) return _ui->plotDaCheckBox;
	if( name == "dr" ) return _ui->plotDrCheckBox;
}


QString	MainWindow::getName(QCheckBox* checkBox) {
	if( checkBox == _ui->plotMxCheckBox ) return "mx";
	if( checkBox == _ui->plotMyCheckBox ) return "my";
	if( checkBox == _ui->plotMzCheckBox ) return "mz";

	if( checkBox == _ui->plotWxCheckBox ) return "wx";
	if( checkBox == _ui->plotWyCheckBox ) return "wy";
	if( checkBox == _ui->plotWzCheckBox ) return "wz";

	if( checkBox == _ui->plotPsiCheckBox ) return "psi";
	if( checkBox == _ui->plotThetaCheckBox ) return "theta";
	if( checkBox == _ui->plotGammaCheckBox ) return "gamma";

	if( checkBox == _ui->plotServo1CheckBox ) return "servo1";
	if( checkBox == _ui->plotServo2CheckBox ) return "servo2";
	if( checkBox == _ui->plotServo3CheckBox ) return "servo3";
	if( checkBox == _ui->plotServo4CheckBox ) return "servo4";
	if( checkBox == _ui->plotServo5CheckBox ) return "servo5";

	if( checkBox == _ui->plotFiCheckBox ) return "fi";
	if( checkBox == _ui->plotDfCheckBox ) return "df";
	if( checkBox == _ui->plotDaCheckBox ) return "da";
	if( checkBox == _ui->plotDrCheckBox ) return "dr";
}
