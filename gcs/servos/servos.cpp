#include "servos.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "connection.h"


Servos::Servos(QObject* parent) : QObject(parent) {
	isPowerStateChanging = false;
	QObject::connect(
		MainWindow::ui().servoPowerCheckBox,
		SIGNAL(stateChanged(int) ),
		SLOT(servoPower(int)) );
}

Servos::~Servos() {
}

Servos& Servos::instance() {
	static Servos instance;
	return instance;
}

Servo* Servos::servo(int id) {
	foreach(Servo* servo, _servo) {
		if( servo->id() == id)
			return servo;
	}
	Servo* servo = new Servo(this, id);
	_servo.push_back( servo );
	return servo;
}

void Servos::powerStausGot(bool state) {
	if( !isPowerStateChanging ) {
		MainWindow::ui().servoPowerCheckBox->setChecked(state);
	} else {
		if( state == MainWindow::ui().servoPowerCheckBox->isChecked() ) {
			MainWindow::ui().servoPowerCheckBox->setStyleSheet( "QCheckBox{background-color: #fff;}" );
			isPowerStateChanging = false;
		}
	}
}

void Servos::servoPower(int state) {
	if(isPowerStateChanging)
		return;
	isPowerStateChanging = true;

	Connection::instance().sendServoPowerStatus(state);

	MainWindow::ui().servoPowerCheckBox->setStyleSheet( "QCheckBox{background-color: #ccc;}" );
	if(state == Qt::Checked)
		MainWindow::ui().servoPowerCheckBox->setCheckState(Qt::Checked);
	else
		MainWindow::ui().servoPowerCheckBox->setCheckState(Qt::Unchecked);
}

Servo::Servo(QObject* parent, int id) : QObject(parent) {
	_id = id;

    switch(id) {
        case 1:
            setSlider = MainWindow::ui().rightAileronSetHorizontalSlider;
            setSpinBox = MainWindow::ui().rightAileronSetDoubleSpinBox;
            indicateSlider = MainWindow::ui().rightAileronIndicateHorizontalSlider;
            indicateLabel = MainWindow::ui().rightAileronIndicateLabel;
            _name = QString("Servo Aileron Right");
            break;
        case 2:
            setSlider = MainWindow::ui().rightElevatorSetHorizontalSlider;
            setSpinBox = MainWindow::ui().rightElevatorSetDoubleSpinBox;
            indicateSlider = MainWindow::ui().rightElevatorIndicateHorizontalSlider;
            indicateLabel = MainWindow::ui().rightElevatorIndicateLabel;
            _name = QString("Servo Elevator Right");
            break;
        case 3:
			setSlider = MainWindow::ui().leftAileronSetHorizontalSlider;
			setSpinBox = MainWindow::ui().leftAileronSetDoubleSpinBox;
			indicateSlider = MainWindow::ui().leftAileronIndicateHorizontalSlider;
			indicateLabel = MainWindow::ui().leftAileronIndicateLabel;
            _name = QString("Servo Aileron Left");
            break;
        case 4:
            setSlider = MainWindow::ui().rudderSetHorizontalSlider;
            setSpinBox = MainWindow::ui().rudderSetDoubleSpinBox;
            indicateSlider = MainWindow::ui().rudderIndicateHorizontalSlider;
            indicateLabel = MainWindow::ui().rudderIndicateLabel;
            _name = QString("Servo Rudder");
            break;
        case 5:
			setSlider = MainWindow::ui().leftElevatorSetHorizontalSlider;
			setSpinBox = MainWindow::ui().leftElevatorSetDoubleSpinBox;
			indicateSlider = MainWindow::ui().leftElevatorIndicateHorizontalSlider;
			indicateLabel = MainWindow::ui().leftElevatorIndicateLabel;
            _name = QString("Servo Elevator Left");
			break;
	}

	QObject::connect(
		setSpinBox,
		SIGNAL(valueChanged(double)),
		SLOT(valueChanged(double)) );
	QObject::connect(
		setSlider,
		SIGNAL(valueChanged(int)),
		SLOT(valueChanged(int)) );

    //qDebug() << "Servo::Servo()" << _id;
}

Servo::~Servo() {

}

void Servo::addData(double time, double value) {
	indicateLabel->setText(QString::number(value, 'f', 2));
	indicateSlider->setValue(value);
    Plot::instance().addData( _name, time, value);
}

int Servo::id() {
	return _id;
}

void Servo::valueChanged(double value) {
    //qDebug() << "Servo::valueChanged()" << _id << value;
	Connection::instance().sendServoOutput(_id, value);
	if(setSpinBox->value() != value)
		setSpinBox->setValue(value);
	if(setSlider->value() != value)
		setSlider->setValue(value);
}

void Servo::valueChanged(int value) {
    valueChanged((double)value);
}
