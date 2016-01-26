#include "control.h"
#include "connection.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"


Control::Control(QObject *parent) : QObject(parent) {
	updateUserCodeRunStatus(false);

	QObject::connect(
		MainWindow::ui().codeStatusButton,
		SIGNAL(clicked()),
		SLOT(userCodeRun()) );

	QObject::connect(
		&Connection::instance(),
		SIGNAL(userCodeRunStatusReceived(bool)),
		SLOT(updateUserCodeRunStatus(bool)) );
}

Control::~Control() {
}

bool Control::userCodeRunStatus() {
	return _userCodeRunStatus;
}

void Control::userCodeRun() {
	Connection::instance().userCodeRun( !userCodeRunStatus() );
	MainWindow::ui().codeStatusButton->setEnabled(false);
}

void Control::updateUserCodeRunStatus(bool status) {
	if( _userCodeRunStatus == status)
		return;

	_userCodeRunStatus = status;
	MainWindow::ui().codeStatusButton->setEnabled(true);

	if(status) {
		MainWindow::ui().codeStatusButton->setIcon(QIcon(":/icon/img/pause.png"));
		MainWindow::ui().codeStatusLabel->setText("<html><head/><body><p><span style=\" font-size:10pt; color: #0f0; text-align:center;\">RUN</span></p></body></html>");
		MainWindow::ui().servoGroupBox->setEnabled(false);
	} else {
		MainWindow::ui().codeStatusButton->setIcon(QIcon(":/icon/img/play.png"));
		MainWindow::ui().codeStatusLabel->setText("<html><head/><body><p><span style=\" font-size:10pt; color: #666; text-align:center;\">STOPPED</span></p></body></html>");
		MainWindow::ui().servoGroupBox->setEnabled(true);
	}
}
