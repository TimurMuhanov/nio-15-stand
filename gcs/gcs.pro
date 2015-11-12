#-------------------------------------------------
#
# Project created by QtCreator 2015-01-19T12:17:02
#
#-------------------------------------------------

QT       += core gui serialport opengl printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = gcs
TEMPLATE = app


SOURCES += \
	main.cpp\
	mainwindow.cpp \
	serial\serial.cpp \
	visualisation\visualisation.cpp \
	connection\connection.cpp \
	../library/qcustomplot/qcustomplot.cpp \
	plot\plot.cpp \
	encoders/encoders.cpp \
	servos/servos.cpp \
	control/control.cpp \
	loader/loader.cpp \
	logger/logger.cpp

HEADERS  += \
	mainwindow.h \
	serial\serial.h \
	visualisation\visualisation.h \
	connection\connection.h \
	../library/qcustomplot/qcustomplot.h \
	plot\plot.h \
	encoders/encoders.h \
	servos/servos.h \
	control/control.h \
	loader/loader.h \
	logger/logger.h

FORMS    += mainwindow.ui


INCLUDEPATH += \
	../library/mavlink/ \
	../library/mavlink/nio15_1/ \
	../library/qcustomplot/ \
	encoders \
	serial \
	visualisation \
	connection \
	plot \
	servos \
	loader \
	logger

RESOURCES += \
    img.qrc
