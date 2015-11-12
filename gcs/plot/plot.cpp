#include "plot.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"


PlotItem::PlotItem(QObject *parent, const QString& name, const QString &color) : QObject(parent), name(name) {
	QColor plotColor( color );
	QGridLayout* parametersLayout = (QGridLayout*) MainWindow::ui().plotGroupBox->layout();

    // create ui to graph control
	QCheckBox* checkBox = new QCheckBox();
	parametersLayout->addWidget( checkBox, Plot::instance().plots.length(), 0 );
	QObject::connect(
				checkBox,
				SIGNAL(clicked(bool)),
				SLOT(setVisible(bool)) );
	QLabel* label = new QLabel(name);
	QPalette palette = label->palette();
	palette.setColor(label->foregroundRole(), plotColor);
	label->setPalette(palette);
	parametersLayout->addWidget( label, Plot::instance().plots.length(), 1 );

	// create graph
	graph = MainWindow::ui().plotWidget->addGraph();
	graph->setPen(QPen(plotColor));
	graph->setVisible(false);
}

PlotItem::~PlotItem() {
}

void PlotItem::addData(const double key, const double value){
	//qDebug() << name << key << data;
	graph->addData( key, value );
}

void PlotItem::clear() {
    graph->clearData();
}

void PlotItem::setVisible(bool state) {
	graph->setVisible(state);
}

Plot::Plot(QObject *parent) : QObject(parent) {
	// set colors
	QList<QString> colorNameList = QColor::colorNames();
	foreach( QString colorName, colorNameList ) {
		if( QColor( colorName ).value() < 200 ) {
			colors[colorName] = false;
		}
	}

	dataRange = all;
	QObject::connect(
		MainWindow::ui().allTimeRadioButton,
		SIGNAL(clicked()),
		SLOT(plotRangeChangeToAll()) );
	QObject::connect(
		MainWindow::ui().lastSecRadioButton,
		SIGNAL(clicked()),
		SLOT(plotRangeChangeToPeriod()) );
	QObject::connect(
		MainWindow::ui().pauseStartPushButton,
		SIGNAL(clicked()),
		SLOT(plotPauseStop()) );

	replotTimer = new QTimer(this);
	replotTimer->setInterval(REPLOT_TIME_MS);
	QObject::connect(
		replotTimer,
		SIGNAL(timeout()),
		SLOT(replot()));
	replotTimer->start();

	MainWindow::ui().plotWidget->xAxis->setLabel("Time, sec");
    MainWindow::ui().plotWidget->setInteraction(QCP::iRangeDrag, true);
	MainWindow::ui().plotWidget->setInteraction(QCP::iRangeZoom, true);
}

Plot::~Plot() {
	replotTimer->stop();
}

Plot& Plot::instance() {
	static Plot instance;
	return instance;
}

void Plot::addData(const QString& name, const double key, const double data) {
	foreach(PlotItem* plot, plots) {
		if( plot->name == name ) {
			plot->addData(key, data);
			return;
		}
	}

	plots.append(new PlotItem(this, name, getNewColor()));
    plots.last()->addData(key, data);
}

void Plot::clear() {
    for(auto item : plots)
        item->clear();
}

void Plot::replot() {
	if( plots.length() == 0 )
		return;

	MainWindow::ui().plotWidget->yAxis->rescale(true);
	if( dataRange == period ) {
		MainWindow::ui().plotWidget->xAxis->setRange(
			MainWindow::ui().plotWidget->graph(0)->data()->last().key,
            MainWindow::ui().lastSecLineEdit->text().toFloat(),
			Qt::AlignRight );
	} else {
		MainWindow::ui().plotWidget->xAxis->rescale(true);
	}
	MainWindow::ui().plotWidget->replot();
}

void Plot::plotRangeChangeToAll() {
	dataRange = all;
}

void Plot::plotRangeChangeToPeriod() {
	dataRange = period;
}

void Plot::plotPauseStop() {
	if( replotTimer->isActive() ) {
		replotTimer->stop();
		MainWindow::ui().pauseStartPushButton->setText("Start");
	} else {
		replotTimer->start();
		MainWindow::ui().pauseStartPushButton->setText("Pause");
	}
}

const QString& Plot::getNewColor() {
	for( QMap<QString, bool>::iterator it=colors.begin(); it != colors.end(); it++ ) {
		if( it.value() == false ) {
			it.value() = true;
			return it.key();
		}
	}
}

