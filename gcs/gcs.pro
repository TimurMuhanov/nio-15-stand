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
    board/control.cpp \
    board/encoders.cpp \
    board/loader.cpp \
    board/servos.cpp \
    board/settings.cpp \
    connection/connection.cpp \
    connection/logger.cpp \
    connection/serial.cpp \
    ui/visualisation.cpp \
    ui/magnetometervisualiser.cpp \
    ui/plot.cpp \
    ../library/qcustomplot/qcustomplot.cpp


HEADERS  += \
	mainwindow.h \
    board/include/control.h \
    board/include/encoders.h \
    board/include/loader.h \
    board/include/servos.h \
    board/include/settings.h \
    connection/include/connection.h \
    connection/include/logger.h \
    connection/include/serial.h \
    ui/include/visualisation.h \
    ui/include/magnetometervisualiser.h \
    ui/include/plot.h \
    ../library/qcustomplot/qcustomplot.h

FORMS    += mainwindow.ui


INCLUDEPATH += \
    board/include \
    connection/include \
    ui/include \
	../library/mavlink/ \
    ../library/mavlink/nio15/ \
	../library/qcustomplot/ \

RESOURCES += \
    img.qrc
