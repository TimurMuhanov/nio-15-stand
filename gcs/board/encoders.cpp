#include "encoders.h"
#include "plot.h"
#include "connection.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"


Encoders::Encoders(QObject* parent) : QObject(parent) {
}

Encoders::~Encoders() {
}

Encoders& Encoders::instance() {
	static Encoders instance;
	return instance;
}

Encoder* Encoders::encoder(int id) {
	for(Encoder* encoder : _encoder) {
		if( encoder->id() == id)
			return encoder;
	}
	Encoder* encoder = new Encoder(this, id);
	_encoder.push_back( encoder );
	return encoder;
}

Encoder::Encoder(QObject* parent, int id) : QObject(parent) {
	_id = id;

    switch(id) {
        case 1:
            _indicateLabel = MainWindow::ui().encoderRollIndicateLabel;
            _name = QString("Encoder Roll");
            break;
        case 2:
            _indicateLabel = MainWindow::ui().encoderPitchIndicateLabel;
            _name = QString("Encoder Pitch");
            break;
        case 3:
            _indicateLabel = MainWindow::ui().encoderYawIndicateLabel;
            _name = QString("Encoder Yaw");
            break;
    }
}

Encoder::~Encoder() {
}

void Encoder::addData(double time, double value) {
    _indicateLabel->setText(QString::number(value, 'f', 2));
    Plot::instance().addData( _name, time, value);
}

int Encoder::id() {
	return _id;
}
