#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T16:14:54
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simulator
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    ../library/qcustomplot/qcustomplot.cpp \
    calculator/calculator.cpp \
	user_func_L1Cntrl.c

HEADERS  += mainwindow.h \
    ../library/qcustomplot/qcustomplot.h \
	matrix.h \
    calculator/calculator.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../library/qcustomplot \
			   calculator
