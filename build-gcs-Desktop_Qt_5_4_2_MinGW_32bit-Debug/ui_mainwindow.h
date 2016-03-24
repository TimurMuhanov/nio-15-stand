/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "magnetometervisualiser.h"
#include "qcustomplot.h"
#include "visualisation.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPort;
    QAction *actionBaud;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGroupBox *encoderGroupBox;
    QGridLayout *gridLayout_9;
    QGroupBox *encoderPitchBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *encoderPitchIndicateLabel;
    QGroupBox *encoderYawBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *encoderYawIndicateLabel;
    QGroupBox *encoderRollBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *encoderRollIndicateLabel;
    QGroupBox *loggingGroupBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *loggingPathLabel;
    QPushButton *loggingPathButton;
    QGroupBox *statusGroupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *codeStatusLabel;
    QPushButton *codeStatusButton;
    QGroupBox *connectionGgroupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *signalIconLabel;
    QLabel *signalValueLabel;
    QTabWidget *tabWidget;
    QWidget *graph;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *plotLayout;
    QCustomPlot *plotWidget;
    QVBoxLayout *leftPlotLayout;
    QGroupBox *plotGroupBox;
    QGridLayout *gridLayout;
    QGroupBox *rangeGroupBox;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *allTimeRadioButton;
    QHBoxLayout *lastSecLayout;
    QRadioButton *lastSecRadioButton;
    QLineEdit *lastSecLineEdit;
    QLabel *secLabel;
    QPushButton *pauseStartPushButton;
    QWidget *visualistion;
    QHBoxLayout *horizontalLayout_7;
    Visualisation *visualisationWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_11;
    MagnetometerVisualiser *openGLWidget;
    QWidget *loader;
    QGridLayout *gridLayout_10;
    QSpacerItem *verticalSpacer_2;
    QLabel *firmwareLabel;
    QLabel *firmwareStatusLabel;
    QPushButton *firmwareChooseButton;
    QProgressBar *firmwareUploadProgressBar;
    QPushButton *firmwareUploadButton;
    QSpacerItem *verticalSpacer_3;
    QWidget *settings;
    QHBoxLayout *horizontalLayout_6;
    QTableView *settingsTableView;
    QGroupBox *servoGroupBox;
    QGridLayout *gridLayout_3;
    QGroupBox *rightElevatorGroupBox;
    QGridLayout *gridLayout_6;
    QSlider *rightElevatorSetHorizontalSlider;
    QSlider *rightElevatorIndicateHorizontalSlider;
    QDoubleSpinBox *rightElevatorSetDoubleSpinBox;
    QLabel *rightElevatorIndicateLabel;
    QGroupBox *rightAileronGroupBox;
    QGridLayout *gridLayout_5;
    QDoubleSpinBox *rightAileronSetDoubleSpinBox;
    QLabel *rightAileronIndicateLabel;
    QSlider *rightAileronSetHorizontalSlider;
    QSlider *rightAileronIndicateHorizontalSlider;
    QGroupBox *leftElevatorGroupBox;
    QGridLayout *gridLayout_7;
    QDoubleSpinBox *leftElevatorSetDoubleSpinBox;
    QSlider *leftElevatorSetHorizontalSlider;
    QSlider *leftElevatorIndicateHorizontalSlider;
    QLabel *leftElevatorIndicateLabel;
    QGroupBox *leftAileronGroupBox;
    QGridLayout *gridLayout_4;
    QSlider *leftAileronSetHorizontalSlider;
    QSlider *leftAileronIndicateHorizontalSlider;
    QDoubleSpinBox *leftAileronSetDoubleSpinBox;
    QLabel *leftAileronIndicateLabel;
    QGroupBox *rudderGroupBox;
    QGridLayout *gridLayout_8;
    QSlider *rudderSetHorizontalSlider;
    QSlider *rudderIndicateHorizontalSlider;
    QDoubleSpinBox *rudderSetDoubleSpinBox;
    QLabel *rudderIndicateLabel;
    QCheckBox *servoPowerCheckBox;
    QSpacerItem *verticalSpacer;
    QGroupBox *imuGroupBox;
    QGridLayout *gridLayout_11;
    QGroupBox *imuPitchBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *imuPitchIndicateLabel;
    QGroupBox *imuYawBox;
    QHBoxLayout *horizontalLayout_9;
    QLabel *imuYawIndicateLabel;
    QGroupBox *imuRollBox;
    QHBoxLayout *horizontalLayout_10;
    QLabel *imuRollIndicateLabel;
    QMenuBar *menuBar;
    QMenu *menuConnection;
    QMenu *menuPort;
    QMenu *menuBaudrate;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(969, 666);
        actionPort = new QAction(MainWindow);
        actionPort->setObjectName(QStringLiteral("actionPort"));
        actionBaud = new QAction(MainWindow);
        actionBaud->setObjectName(QStringLiteral("actionBaud"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        encoderGroupBox = new QGroupBox(centralWidget);
        encoderGroupBox->setObjectName(QStringLiteral("encoderGroupBox"));
        gridLayout_9 = new QGridLayout(encoderGroupBox);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        encoderPitchBox = new QGroupBox(encoderGroupBox);
        encoderPitchBox->setObjectName(QStringLiteral("encoderPitchBox"));
        horizontalLayout_3 = new QHBoxLayout(encoderPitchBox);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        encoderPitchIndicateLabel = new QLabel(encoderPitchBox);
        encoderPitchIndicateLabel->setObjectName(QStringLiteral("encoderPitchIndicateLabel"));

        horizontalLayout_3->addWidget(encoderPitchIndicateLabel);


        gridLayout_9->addWidget(encoderPitchBox, 0, 1, 1, 1);

        encoderYawBox = new QGroupBox(encoderGroupBox);
        encoderYawBox->setObjectName(QStringLiteral("encoderYawBox"));
        horizontalLayout_5 = new QHBoxLayout(encoderYawBox);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        encoderYawIndicateLabel = new QLabel(encoderYawBox);
        encoderYawIndicateLabel->setObjectName(QStringLiteral("encoderYawIndicateLabel"));

        horizontalLayout_5->addWidget(encoderYawIndicateLabel);


        gridLayout_9->addWidget(encoderYawBox, 0, 3, 1, 1);

        encoderRollBox = new QGroupBox(encoderGroupBox);
        encoderRollBox->setObjectName(QStringLiteral("encoderRollBox"));
        horizontalLayout_4 = new QHBoxLayout(encoderRollBox);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        encoderRollIndicateLabel = new QLabel(encoderRollBox);
        encoderRollIndicateLabel->setObjectName(QStringLiteral("encoderRollIndicateLabel"));

        horizontalLayout_4->addWidget(encoderRollIndicateLabel);


        gridLayout_9->addWidget(encoderRollBox, 0, 0, 1, 1);


        gridLayout_2->addWidget(encoderGroupBox, 2, 0, 1, 2);

        loggingGroupBox = new QGroupBox(centralWidget);
        loggingGroupBox->setObjectName(QStringLiteral("loggingGroupBox"));
        verticalLayout_3 = new QVBoxLayout(loggingGroupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        loggingPathLabel = new QLabel(loggingGroupBox);
        loggingPathLabel->setObjectName(QStringLiteral("loggingPathLabel"));

        verticalLayout_3->addWidget(loggingPathLabel);

        loggingPathButton = new QPushButton(loggingGroupBox);
        loggingPathButton->setObjectName(QStringLiteral("loggingPathButton"));

        verticalLayout_3->addWidget(loggingPathButton);


        gridLayout_2->addWidget(loggingGroupBox, 1, 0, 1, 2);

        statusGroupBox = new QGroupBox(centralWidget);
        statusGroupBox->setObjectName(QStringLiteral("statusGroupBox"));
        statusGroupBox->setMinimumSize(QSize(115, 57));
        statusGroupBox->setMaximumSize(QSize(115, 57));
        horizontalLayout = new QHBoxLayout(statusGroupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        codeStatusLabel = new QLabel(statusGroupBox);
        codeStatusLabel->setObjectName(QStringLiteral("codeStatusLabel"));
        codeStatusLabel->setEnabled(false);

        horizontalLayout->addWidget(codeStatusLabel);

        codeStatusButton = new QPushButton(statusGroupBox);
        codeStatusButton->setObjectName(QStringLiteral("codeStatusButton"));
        codeStatusButton->setMinimumSize(QSize(28, 24));
        codeStatusButton->setMaximumSize(QSize(28, 24));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/img/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        codeStatusButton->setIcon(icon);

        horizontalLayout->addWidget(codeStatusButton);


        gridLayout_2->addWidget(statusGroupBox, 0, 1, 1, 1);

        connectionGgroupBox = new QGroupBox(centralWidget);
        connectionGgroupBox->setObjectName(QStringLiteral("connectionGgroupBox"));
        verticalLayout = new QVBoxLayout(connectionGgroupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        signalIconLabel = new QLabel(connectionGgroupBox);
        signalIconLabel->setObjectName(QStringLiteral("signalIconLabel"));
        signalIconLabel->setMaximumSize(QSize(27, 27));
        signalIconLabel->setPixmap(QPixmap(QString::fromUtf8(":/icon/img/signal_lost.png")));

        horizontalLayout_2->addWidget(signalIconLabel);

        signalValueLabel = new QLabel(connectionGgroupBox);
        signalValueLabel->setObjectName(QStringLiteral("signalValueLabel"));
        signalValueLabel->setMaximumSize(QSize(43, 16777215));

        horizontalLayout_2->addWidget(signalValueLabel);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout_2->addWidget(connectionGgroupBox, 0, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        graph = new QWidget();
        graph->setObjectName(QStringLiteral("graph"));
        verticalLayout_5 = new QVBoxLayout(graph);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        plotLayout = new QHBoxLayout();
        plotLayout->setSpacing(6);
        plotLayout->setObjectName(QStringLiteral("plotLayout"));
        plotWidget = new QCustomPlot(graph);
        plotWidget->setObjectName(QStringLiteral("plotWidget"));

        plotLayout->addWidget(plotWidget);

        leftPlotLayout = new QVBoxLayout();
        leftPlotLayout->setSpacing(6);
        leftPlotLayout->setObjectName(QStringLiteral("leftPlotLayout"));
        plotGroupBox = new QGroupBox(graph);
        plotGroupBox->setObjectName(QStringLiteral("plotGroupBox"));
        plotGroupBox->setMinimumSize(QSize(200, 0));
        gridLayout = new QGridLayout(plotGroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        leftPlotLayout->addWidget(plotGroupBox);

        rangeGroupBox = new QGroupBox(graph);
        rangeGroupBox->setObjectName(QStringLiteral("rangeGroupBox"));
        verticalLayout_4 = new QVBoxLayout(rangeGroupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        allTimeRadioButton = new QRadioButton(rangeGroupBox);
        allTimeRadioButton->setObjectName(QStringLiteral("allTimeRadioButton"));
        allTimeRadioButton->setChecked(true);

        verticalLayout_4->addWidget(allTimeRadioButton);

        lastSecLayout = new QHBoxLayout();
        lastSecLayout->setSpacing(6);
        lastSecLayout->setObjectName(QStringLiteral("lastSecLayout"));
        lastSecRadioButton = new QRadioButton(rangeGroupBox);
        lastSecRadioButton->setObjectName(QStringLiteral("lastSecRadioButton"));

        lastSecLayout->addWidget(lastSecRadioButton);

        lastSecLineEdit = new QLineEdit(rangeGroupBox);
        lastSecLineEdit->setObjectName(QStringLiteral("lastSecLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lastSecLineEdit->sizePolicy().hasHeightForWidth());
        lastSecLineEdit->setSizePolicy(sizePolicy);
        lastSecLineEdit->setMaximumSize(QSize(30, 16777215));

        lastSecLayout->addWidget(lastSecLineEdit);

        secLabel = new QLabel(rangeGroupBox);
        secLabel->setObjectName(QStringLiteral("secLabel"));

        lastSecLayout->addWidget(secLabel);


        verticalLayout_4->addLayout(lastSecLayout);


        leftPlotLayout->addWidget(rangeGroupBox);

        pauseStartPushButton = new QPushButton(graph);
        pauseStartPushButton->setObjectName(QStringLiteral("pauseStartPushButton"));

        leftPlotLayout->addWidget(pauseStartPushButton);

        leftPlotLayout->setStretch(0, 1);

        plotLayout->addLayout(leftPlotLayout);

        plotLayout->setStretch(0, 1);

        verticalLayout_5->addLayout(plotLayout);

        verticalLayout_5->setStretch(0, 1);
        tabWidget->addTab(graph, QString());
        visualistion = new QWidget();
        visualistion->setObjectName(QStringLiteral("visualistion"));
        horizontalLayout_7 = new QHBoxLayout(visualistion);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        visualisationWidget = new Visualisation(visualistion);
        visualisationWidget->setObjectName(QStringLiteral("visualisationWidget"));

        horizontalLayout_7->addWidget(visualisationWidget);

        tabWidget->addTab(visualistion, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_11 = new QHBoxLayout(tab);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        openGLWidget = new MagnetometerVisualiser(tab);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        horizontalLayout_11->addWidget(openGLWidget);

        tabWidget->addTab(tab, QString());
        loader = new QWidget();
        loader->setObjectName(QStringLiteral("loader"));
        gridLayout_10 = new QGridLayout(loader);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        verticalSpacer_2 = new QSpacerItem(20, 244, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_2, 0, 1, 1, 1);

        firmwareLabel = new QLabel(loader);
        firmwareLabel->setObjectName(QStringLiteral("firmwareLabel"));
        firmwareLabel->setMinimumSize(QSize(43, 16));
        firmwareLabel->setMaximumSize(QSize(43, 16));

        gridLayout_10->addWidget(firmwareLabel, 1, 1, 1, 1);

        firmwareStatusLabel = new QLabel(loader);
        firmwareStatusLabel->setObjectName(QStringLiteral("firmwareStatusLabel"));

        gridLayout_10->addWidget(firmwareStatusLabel, 1, 2, 1, 1);

        firmwareChooseButton = new QPushButton(loader);
        firmwareChooseButton->setObjectName(QStringLiteral("firmwareChooseButton"));
        firmwareChooseButton->setEnabled(true);
        firmwareChooseButton->setMinimumSize(QSize(121, 23));
        firmwareChooseButton->setMaximumSize(QSize(121, 23));

        gridLayout_10->addWidget(firmwareChooseButton, 2, 0, 1, 1);

        firmwareUploadProgressBar = new QProgressBar(loader);
        firmwareUploadProgressBar->setObjectName(QStringLiteral("firmwareUploadProgressBar"));
        firmwareUploadProgressBar->setEnabled(true);
        firmwareUploadProgressBar->setValue(0);

        gridLayout_10->addWidget(firmwareUploadProgressBar, 2, 1, 1, 2);

        firmwareUploadButton = new QPushButton(loader);
        firmwareUploadButton->setObjectName(QStringLiteral("firmwareUploadButton"));
        firmwareUploadButton->setEnabled(false);
        firmwareUploadButton->setMinimumSize(QSize(80, 23));
        firmwareUploadButton->setMaximumSize(QSize(80, 23));

        gridLayout_10->addWidget(firmwareUploadButton, 2, 3, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 243, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_3, 3, 1, 1, 1);

        tabWidget->addTab(loader, QString());
        settings = new QWidget();
        settings->setObjectName(QStringLiteral("settings"));
        horizontalLayout_6 = new QHBoxLayout(settings);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        settingsTableView = new QTableView(settings);
        settingsTableView->setObjectName(QStringLiteral("settingsTableView"));

        horizontalLayout_6->addWidget(settingsTableView);

        tabWidget->addTab(settings, QString());

        gridLayout_2->addWidget(tabWidget, 0, 2, 6, 1);

        servoGroupBox = new QGroupBox(centralWidget);
        servoGroupBox->setObjectName(QStringLiteral("servoGroupBox"));
        gridLayout_3 = new QGridLayout(servoGroupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        rightElevatorGroupBox = new QGroupBox(servoGroupBox);
        rightElevatorGroupBox->setObjectName(QStringLiteral("rightElevatorGroupBox"));
        gridLayout_6 = new QGridLayout(rightElevatorGroupBox);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        rightElevatorSetHorizontalSlider = new QSlider(rightElevatorGroupBox);
        rightElevatorSetHorizontalSlider->setObjectName(QStringLiteral("rightElevatorSetHorizontalSlider"));
        rightElevatorSetHorizontalSlider->setMinimum(-40);
        rightElevatorSetHorizontalSlider->setMaximum(40);
        rightElevatorSetHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(rightElevatorSetHorizontalSlider, 0, 1, 1, 1);

        rightElevatorIndicateHorizontalSlider = new QSlider(rightElevatorGroupBox);
        rightElevatorIndicateHorizontalSlider->setObjectName(QStringLiteral("rightElevatorIndicateHorizontalSlider"));
        rightElevatorIndicateHorizontalSlider->setEnabled(false);
        rightElevatorIndicateHorizontalSlider->setMinimum(-40);
        rightElevatorIndicateHorizontalSlider->setMaximum(40);
        rightElevatorIndicateHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(rightElevatorIndicateHorizontalSlider, 1, 1, 1, 1);

        rightElevatorSetDoubleSpinBox = new QDoubleSpinBox(rightElevatorGroupBox);
        rightElevatorSetDoubleSpinBox->setObjectName(QStringLiteral("rightElevatorSetDoubleSpinBox"));
        rightElevatorSetDoubleSpinBox->setMinimum(-40);
        rightElevatorSetDoubleSpinBox->setMaximum(40);
        rightElevatorSetDoubleSpinBox->setSingleStep(0.5);

        gridLayout_6->addWidget(rightElevatorSetDoubleSpinBox, 0, 0, 1, 1);

        rightElevatorIndicateLabel = new QLabel(rightElevatorGroupBox);
        rightElevatorIndicateLabel->setObjectName(QStringLiteral("rightElevatorIndicateLabel"));

        gridLayout_6->addWidget(rightElevatorIndicateLabel, 1, 0, 1, 1);


        gridLayout_3->addWidget(rightElevatorGroupBox, 2, 1, 1, 1);

        rightAileronGroupBox = new QGroupBox(servoGroupBox);
        rightAileronGroupBox->setObjectName(QStringLiteral("rightAileronGroupBox"));
        gridLayout_5 = new QGridLayout(rightAileronGroupBox);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        rightAileronSetDoubleSpinBox = new QDoubleSpinBox(rightAileronGroupBox);
        rightAileronSetDoubleSpinBox->setObjectName(QStringLiteral("rightAileronSetDoubleSpinBox"));
        rightAileronSetDoubleSpinBox->setMinimum(-40);
        rightAileronSetDoubleSpinBox->setMaximum(40);
        rightAileronSetDoubleSpinBox->setSingleStep(0.5);

        gridLayout_5->addWidget(rightAileronSetDoubleSpinBox, 0, 0, 1, 1);

        rightAileronIndicateLabel = new QLabel(rightAileronGroupBox);
        rightAileronIndicateLabel->setObjectName(QStringLiteral("rightAileronIndicateLabel"));

        gridLayout_5->addWidget(rightAileronIndicateLabel, 1, 0, 1, 1);

        rightAileronSetHorizontalSlider = new QSlider(rightAileronGroupBox);
        rightAileronSetHorizontalSlider->setObjectName(QStringLiteral("rightAileronSetHorizontalSlider"));
        rightAileronSetHorizontalSlider->setMinimum(-40);
        rightAileronSetHorizontalSlider->setMaximum(40);
        rightAileronSetHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(rightAileronSetHorizontalSlider, 0, 1, 1, 1);

        rightAileronIndicateHorizontalSlider = new QSlider(rightAileronGroupBox);
        rightAileronIndicateHorizontalSlider->setObjectName(QStringLiteral("rightAileronIndicateHorizontalSlider"));
        rightAileronIndicateHorizontalSlider->setEnabled(false);
        rightAileronIndicateHorizontalSlider->setMinimum(-40);
        rightAileronIndicateHorizontalSlider->setMaximum(40);
        rightAileronIndicateHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(rightAileronIndicateHorizontalSlider, 1, 1, 1, 1);


        gridLayout_3->addWidget(rightAileronGroupBox, 1, 1, 1, 1);

        leftElevatorGroupBox = new QGroupBox(servoGroupBox);
        leftElevatorGroupBox->setObjectName(QStringLiteral("leftElevatorGroupBox"));
        gridLayout_7 = new QGridLayout(leftElevatorGroupBox);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        leftElevatorSetDoubleSpinBox = new QDoubleSpinBox(leftElevatorGroupBox);
        leftElevatorSetDoubleSpinBox->setObjectName(QStringLiteral("leftElevatorSetDoubleSpinBox"));
        leftElevatorSetDoubleSpinBox->setMinimum(-40);
        leftElevatorSetDoubleSpinBox->setMaximum(40);
        leftElevatorSetDoubleSpinBox->setSingleStep(0.5);

        gridLayout_7->addWidget(leftElevatorSetDoubleSpinBox, 0, 0, 1, 1);

        leftElevatorSetHorizontalSlider = new QSlider(leftElevatorGroupBox);
        leftElevatorSetHorizontalSlider->setObjectName(QStringLiteral("leftElevatorSetHorizontalSlider"));
        leftElevatorSetHorizontalSlider->setMinimum(-40);
        leftElevatorSetHorizontalSlider->setMaximum(40);
        leftElevatorSetHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_7->addWidget(leftElevatorSetHorizontalSlider, 0, 1, 1, 1);

        leftElevatorIndicateHorizontalSlider = new QSlider(leftElevatorGroupBox);
        leftElevatorIndicateHorizontalSlider->setObjectName(QStringLiteral("leftElevatorIndicateHorizontalSlider"));
        leftElevatorIndicateHorizontalSlider->setEnabled(false);
        leftElevatorIndicateHorizontalSlider->setMinimum(-40);
        leftElevatorIndicateHorizontalSlider->setMaximum(40);
        leftElevatorIndicateHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_7->addWidget(leftElevatorIndicateHorizontalSlider, 1, 1, 1, 1);

        leftElevatorIndicateLabel = new QLabel(leftElevatorGroupBox);
        leftElevatorIndicateLabel->setObjectName(QStringLiteral("leftElevatorIndicateLabel"));

        gridLayout_7->addWidget(leftElevatorIndicateLabel, 1, 0, 1, 1);


        gridLayout_3->addWidget(leftElevatorGroupBox, 2, 0, 1, 1);

        leftAileronGroupBox = new QGroupBox(servoGroupBox);
        leftAileronGroupBox->setObjectName(QStringLiteral("leftAileronGroupBox"));
        gridLayout_4 = new QGridLayout(leftAileronGroupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        leftAileronSetHorizontalSlider = new QSlider(leftAileronGroupBox);
        leftAileronSetHorizontalSlider->setObjectName(QStringLiteral("leftAileronSetHorizontalSlider"));
        leftAileronSetHorizontalSlider->setMinimum(-40);
        leftAileronSetHorizontalSlider->setMaximum(40);
        leftAileronSetHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(leftAileronSetHorizontalSlider, 0, 1, 1, 1);

        leftAileronIndicateHorizontalSlider = new QSlider(leftAileronGroupBox);
        leftAileronIndicateHorizontalSlider->setObjectName(QStringLiteral("leftAileronIndicateHorizontalSlider"));
        leftAileronIndicateHorizontalSlider->setEnabled(false);
        leftAileronIndicateHorizontalSlider->setMinimum(-40);
        leftAileronIndicateHorizontalSlider->setMaximum(40);
        leftAileronIndicateHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(leftAileronIndicateHorizontalSlider, 1, 1, 1, 1);

        leftAileronSetDoubleSpinBox = new QDoubleSpinBox(leftAileronGroupBox);
        leftAileronSetDoubleSpinBox->setObjectName(QStringLiteral("leftAileronSetDoubleSpinBox"));
        leftAileronSetDoubleSpinBox->setMinimum(-40);
        leftAileronSetDoubleSpinBox->setMaximum(40);
        leftAileronSetDoubleSpinBox->setSingleStep(0.5);

        gridLayout_4->addWidget(leftAileronSetDoubleSpinBox, 0, 0, 1, 1);

        leftAileronIndicateLabel = new QLabel(leftAileronGroupBox);
        leftAileronIndicateLabel->setObjectName(QStringLiteral("leftAileronIndicateLabel"));

        gridLayout_4->addWidget(leftAileronIndicateLabel, 1, 0, 1, 1);


        gridLayout_3->addWidget(leftAileronGroupBox, 1, 0, 1, 1);

        rudderGroupBox = new QGroupBox(servoGroupBox);
        rudderGroupBox->setObjectName(QStringLiteral("rudderGroupBox"));
        gridLayout_8 = new QGridLayout(rudderGroupBox);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        rudderSetHorizontalSlider = new QSlider(rudderGroupBox);
        rudderSetHorizontalSlider->setObjectName(QStringLiteral("rudderSetHorizontalSlider"));
        rudderSetHorizontalSlider->setMinimum(-40);
        rudderSetHorizontalSlider->setMaximum(40);
        rudderSetHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_8->addWidget(rudderSetHorizontalSlider, 0, 1, 1, 1);

        rudderIndicateHorizontalSlider = new QSlider(rudderGroupBox);
        rudderIndicateHorizontalSlider->setObjectName(QStringLiteral("rudderIndicateHorizontalSlider"));
        rudderIndicateHorizontalSlider->setEnabled(false);
        rudderIndicateHorizontalSlider->setMinimum(-40);
        rudderIndicateHorizontalSlider->setMaximum(40);
        rudderIndicateHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_8->addWidget(rudderIndicateHorizontalSlider, 1, 1, 1, 1);

        rudderSetDoubleSpinBox = new QDoubleSpinBox(rudderGroupBox);
        rudderSetDoubleSpinBox->setObjectName(QStringLiteral("rudderSetDoubleSpinBox"));
        rudderSetDoubleSpinBox->setMinimum(-40);
        rudderSetDoubleSpinBox->setMaximum(40);
        rudderSetDoubleSpinBox->setSingleStep(0.5);

        gridLayout_8->addWidget(rudderSetDoubleSpinBox, 0, 0, 1, 1);

        rudderIndicateLabel = new QLabel(rudderGroupBox);
        rudderIndicateLabel->setObjectName(QStringLiteral("rudderIndicateLabel"));

        gridLayout_8->addWidget(rudderIndicateLabel, 1, 0, 1, 1);


        gridLayout_3->addWidget(rudderGroupBox, 3, 0, 1, 2);

        servoPowerCheckBox = new QCheckBox(servoGroupBox);
        servoPowerCheckBox->setObjectName(QStringLiteral("servoPowerCheckBox"));

        gridLayout_3->addWidget(servoPowerCheckBox, 0, 0, 1, 1);


        gridLayout_2->addWidget(servoGroupBox, 4, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 5, 0, 1, 2);

        imuGroupBox = new QGroupBox(centralWidget);
        imuGroupBox->setObjectName(QStringLiteral("imuGroupBox"));
        gridLayout_11 = new QGridLayout(imuGroupBox);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        imuPitchBox = new QGroupBox(imuGroupBox);
        imuPitchBox->setObjectName(QStringLiteral("imuPitchBox"));
        horizontalLayout_8 = new QHBoxLayout(imuPitchBox);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        imuPitchIndicateLabel = new QLabel(imuPitchBox);
        imuPitchIndicateLabel->setObjectName(QStringLiteral("imuPitchIndicateLabel"));

        horizontalLayout_8->addWidget(imuPitchIndicateLabel);


        gridLayout_11->addWidget(imuPitchBox, 0, 1, 1, 1);

        imuYawBox = new QGroupBox(imuGroupBox);
        imuYawBox->setObjectName(QStringLiteral("imuYawBox"));
        horizontalLayout_9 = new QHBoxLayout(imuYawBox);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        imuYawIndicateLabel = new QLabel(imuYawBox);
        imuYawIndicateLabel->setObjectName(QStringLiteral("imuYawIndicateLabel"));

        horizontalLayout_9->addWidget(imuYawIndicateLabel);


        gridLayout_11->addWidget(imuYawBox, 0, 3, 1, 1);

        imuRollBox = new QGroupBox(imuGroupBox);
        imuRollBox->setObjectName(QStringLiteral("imuRollBox"));
        horizontalLayout_10 = new QHBoxLayout(imuRollBox);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        imuRollIndicateLabel = new QLabel(imuRollBox);
        imuRollIndicateLabel->setObjectName(QStringLiteral("imuRollIndicateLabel"));

        horizontalLayout_10->addWidget(imuRollIndicateLabel);


        gridLayout_11->addWidget(imuRollBox, 0, 0, 1, 1);


        gridLayout_2->addWidget(imuGroupBox, 3, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 969, 21));
        menuConnection = new QMenu(menuBar);
        menuConnection->setObjectName(QStringLiteral("menuConnection"));
        menuPort = new QMenu(menuConnection);
        menuPort->setObjectName(QStringLiteral("menuPort"));
        menuBaudrate = new QMenu(menuConnection);
        menuBaudrate->setObjectName(QStringLiteral("menuBaudrate"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuConnection->menuAction());
        menuConnection->addAction(menuPort->menuAction());
        menuConnection->addAction(menuBaudrate->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionPort->setText(QApplication::translate("MainWindow", "Port", 0));
        actionBaud->setText(QApplication::translate("MainWindow", "Baud", 0));
        encoderGroupBox->setTitle(QApplication::translate("MainWindow", "Encoder", 0));
        encoderPitchBox->setTitle(QApplication::translate("MainWindow", "\316\230, Pitch", 0));
        encoderPitchIndicateLabel->setText(QApplication::translate("MainWindow", "0.00", 0));
        encoderYawBox->setTitle(QApplication::translate("MainWindow", "\316\250, Yaw", 0));
        encoderYawIndicateLabel->setText(QApplication::translate("MainWindow", "0.00", 0));
        encoderRollBox->setTitle(QApplication::translate("MainWindow", "\316\263, Roll", 0));
        encoderRollIndicateLabel->setText(QApplication::translate("MainWindow", "0.00", 0));
        loggingGroupBox->setTitle(QApplication::translate("MainWindow", "Logging", 0));
        loggingPathLabel->setText(QApplication::translate("MainWindow", "Log Path", 0));
        loggingPathButton->setText(QApplication::translate("MainWindow", "Change Log Path", 0));
        statusGroupBox->setTitle(QApplication::translate("MainWindow", "User code", 0));
        codeStatusLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">STOPPED</span></p></body></html>", 0));
        codeStatusButton->setText(QString());
        connectionGgroupBox->setTitle(QApplication::translate("MainWindow", "Connection", 0));
        signalValueLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">0</span><span style=\" font-size:12pt; color:#666666;\">%</span></p></body></html>", 0));
        plotGroupBox->setTitle(QApplication::translate("MainWindow", "Plot:", 0));
        rangeGroupBox->setTitle(QApplication::translate("MainWindow", "Range", 0));
        allTimeRadioButton->setText(QApplication::translate("MainWindow", "all time", 0));
        lastSecRadioButton->setText(QApplication::translate("MainWindow", "last", 0));
        lastSecLineEdit->setText(QApplication::translate("MainWindow", "5", 0));
        secLabel->setText(QApplication::translate("MainWindow", "sec", 0));
        pauseStartPushButton->setText(QApplication::translate("MainWindow", "Pause", 0));
        tabWidget->setTabText(tabWidget->indexOf(graph), QApplication::translate("MainWindow", "Graph", 0));
        tabWidget->setTabText(tabWidget->indexOf(visualistion), QApplication::translate("MainWindow", "Visualisation", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Magnetometer", 0));
        firmwareLabel->setText(QApplication::translate("MainWindow", "Status:", 0));
        firmwareStatusLabel->setText(QApplication::translate("MainWindow", "select firmware file", 0));
        firmwareChooseButton->setText(QApplication::translate("MainWindow", "Select file...", 0));
        firmwareUploadProgressBar->setFormat(QApplication::translate("MainWindow", "%v/%mKB, %p%", 0));
        firmwareUploadButton->setText(QApplication::translate("MainWindow", "Upload", 0));
        tabWidget->setTabText(tabWidget->indexOf(loader), QApplication::translate("MainWindow", "Loader", 0));
        tabWidget->setTabText(tabWidget->indexOf(settings), QApplication::translate("MainWindow", "Settings", 0));
        servoGroupBox->setTitle(QApplication::translate("MainWindow", "Servo", 0));
        rightElevatorGroupBox->setTitle(QApplication::translate("MainWindow", "Right Elevator", 0));
        rightElevatorIndicateLabel->setText(QApplication::translate("MainWindow", "0.00", 0));
        rightAileronGroupBox->setTitle(QApplication::translate("MainWindow", "Right Aileron", 0));
        rightAileronIndicateLabel->setText(QApplication::translate("MainWindow", "0.00", 0));
        leftElevatorGroupBox->setTitle(QApplication::translate("MainWindow", "Left Elevator", 0));
        leftElevatorIndicateLabel->setText(QApplication::translate("MainWindow", "0.00", 0));
        leftAileronGroupBox->setTitle(QApplication::translate("MainWindow", "Left Aileron", 0));
        leftAileronIndicateLabel->setText(QApplication::translate("MainWindow", "0.00", 0));
        rudderGroupBox->setTitle(QApplication::translate("MainWindow", "Rudder", 0));
        rudderIndicateLabel->setText(QApplication::translate("MainWindow", "0.00", 0));
        servoPowerCheckBox->setText(QApplication::translate("MainWindow", "Enable Power", 0));
        imuGroupBox->setTitle(QApplication::translate("MainWindow", "IMU", 0));
        imuPitchBox->setTitle(QApplication::translate("MainWindow", "\316\230, Pitch", 0));
        imuPitchIndicateLabel->setText(QApplication::translate("MainWindow", "0.00", 0));
        imuYawBox->setTitle(QApplication::translate("MainWindow", "\316\250, Yaw", 0));
        imuYawIndicateLabel->setText(QApplication::translate("MainWindow", "0.00", 0));
        imuRollBox->setTitle(QApplication::translate("MainWindow", "\316\263, Roll", 0));
        imuRollIndicateLabel->setText(QApplication::translate("MainWindow", "0.00", 0));
        menuConnection->setTitle(QApplication::translate("MainWindow", "Connection", 0));
        menuPort->setTitle(QApplication::translate("MainWindow", "Port", 0));
        menuBaudrate->setTitle(QApplication::translate("MainWindow", "Baudrate", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
