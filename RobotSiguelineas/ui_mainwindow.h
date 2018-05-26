/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *wheelSpeedLabel;
    QDoubleSpinBox *wheelSpeed;
    QLabel *wheelRadiusLabel;
    QDoubleSpinBox *wheelRadius;
    QLabel *wheelSeparationLabel;
    QDoubleSpinBox *wheelSeparation;
    QLabel *distanceToWheelsLabel;
    QDoubleSpinBox *distanceToWheels;
    QHBoxLayout *RobotSizeLabelHorizontalLayout;
    QLabel *robotHighLabel;
    QLabel *robotWidthLabel;
    QHBoxLayout *RobotSizeHorizontalLayout;
    QDoubleSpinBox *robotHigh;
    QDoubleSpinBox *robotWidth;
    QHBoxLayout *SensorLabelHorizontalLayout;
    QLabel *sensorDistanceLabel;
    QLabel *sensorSeparationLabel;
    QHBoxLayout *SensorHorizontalLayout;
    QDoubleSpinBox *sensorDistance;
    QDoubleSpinBox *sensorSeparation;
    QHBoxLayout *CameraTypeHorizontalLayout;
    QRadioButton *perspectiveRadioButton;
    QRadioButton *orthogonalRadioButton;
    QLabel *circuitePathLabel;
    QPlainTextEdit *circuitePath;
    QCheckBox *showRobotCheckBox;
    QLabel *timeTittleLabel;
    QLabel *timeLabel;
    QSpacerItem *verticalSpacer;
    QPushButton *insertParameters;
    QPushButton *quit;
    GLWidget *widget;
    QLabel *robotPhoto;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(1145, 733);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        wheelSpeedLabel = new QLabel(centralWidget);
        wheelSpeedLabel->setObjectName(QStringLiteral("wheelSpeedLabel"));
        wheelSpeedLabel->setEnabled(true);
        wheelSpeedLabel->setScaledContents(false);

        verticalLayout->addWidget(wheelSpeedLabel);

        wheelSpeed = new QDoubleSpinBox(centralWidget);
        wheelSpeed->setObjectName(QStringLiteral("wheelSpeed"));
        wheelSpeed->setValue(2);

        verticalLayout->addWidget(wheelSpeed);

        wheelRadiusLabel = new QLabel(centralWidget);
        wheelRadiusLabel->setObjectName(QStringLiteral("wheelRadiusLabel"));

        verticalLayout->addWidget(wheelRadiusLabel);

        wheelRadius = new QDoubleSpinBox(centralWidget);
        wheelRadius->setObjectName(QStringLiteral("wheelRadius"));
        wheelRadius->setValue(2);

        verticalLayout->addWidget(wheelRadius);

        wheelSeparationLabel = new QLabel(centralWidget);
        wheelSeparationLabel->setObjectName(QStringLiteral("wheelSeparationLabel"));

        verticalLayout->addWidget(wheelSeparationLabel);

        wheelSeparation = new QDoubleSpinBox(centralWidget);
        wheelSeparation->setObjectName(QStringLiteral("wheelSeparation"));
        wheelSeparation->setValue(16);

        verticalLayout->addWidget(wheelSeparation);

        distanceToWheelsLabel = new QLabel(centralWidget);
        distanceToWheelsLabel->setObjectName(QStringLiteral("distanceToWheelsLabel"));

        verticalLayout->addWidget(distanceToWheelsLabel);

        distanceToWheels = new QDoubleSpinBox(centralWidget);
        distanceToWheels->setObjectName(QStringLiteral("distanceToWheels"));
        distanceToWheels->setValue(3);

        verticalLayout->addWidget(distanceToWheels);

        RobotSizeLabelHorizontalLayout = new QHBoxLayout();
        RobotSizeLabelHorizontalLayout->setSpacing(6);
        RobotSizeLabelHorizontalLayout->setObjectName(QStringLiteral("RobotSizeLabelHorizontalLayout"));
        RobotSizeLabelHorizontalLayout->setContentsMargins(-1, -1, -1, 3);
        robotHighLabel = new QLabel(centralWidget);
        robotHighLabel->setObjectName(QStringLiteral("robotHighLabel"));

        RobotSizeLabelHorizontalLayout->addWidget(robotHighLabel);

        robotWidthLabel = new QLabel(centralWidget);
        robotWidthLabel->setObjectName(QStringLiteral("robotWidthLabel"));

        RobotSizeLabelHorizontalLayout->addWidget(robotWidthLabel);


        verticalLayout->addLayout(RobotSizeLabelHorizontalLayout);

        RobotSizeHorizontalLayout = new QHBoxLayout();
        RobotSizeHorizontalLayout->setSpacing(6);
        RobotSizeHorizontalLayout->setObjectName(QStringLiteral("RobotSizeHorizontalLayout"));
        RobotSizeHorizontalLayout->setContentsMargins(-1, -1, -1, 0);
        robotHigh = new QDoubleSpinBox(centralWidget);
        robotHigh->setObjectName(QStringLiteral("robotHigh"));
        robotHigh->setValue(22);

        RobotSizeHorizontalLayout->addWidget(robotHigh);

        robotWidth = new QDoubleSpinBox(centralWidget);
        robotWidth->setObjectName(QStringLiteral("robotWidth"));
        robotWidth->setValue(16);

        RobotSizeHorizontalLayout->addWidget(robotWidth);


        verticalLayout->addLayout(RobotSizeHorizontalLayout);

        SensorLabelHorizontalLayout = new QHBoxLayout();
        SensorLabelHorizontalLayout->setSpacing(6);
        SensorLabelHorizontalLayout->setObjectName(QStringLiteral("SensorLabelHorizontalLayout"));
        SensorLabelHorizontalLayout->setContentsMargins(0, -1, -1, 3);
        sensorDistanceLabel = new QLabel(centralWidget);
        sensorDistanceLabel->setObjectName(QStringLiteral("sensorDistanceLabel"));

        SensorLabelHorizontalLayout->addWidget(sensorDistanceLabel);

        sensorSeparationLabel = new QLabel(centralWidget);
        sensorSeparationLabel->setObjectName(QStringLiteral("sensorSeparationLabel"));

        SensorLabelHorizontalLayout->addWidget(sensorSeparationLabel);


        verticalLayout->addLayout(SensorLabelHorizontalLayout);

        SensorHorizontalLayout = new QHBoxLayout();
        SensorHorizontalLayout->setSpacing(6);
        SensorHorizontalLayout->setObjectName(QStringLiteral("SensorHorizontalLayout"));
        SensorHorizontalLayout->setContentsMargins(-1, -1, -1, 0);
        sensorDistance = new QDoubleSpinBox(centralWidget);
        sensorDistance->setObjectName(QStringLiteral("sensorDistance"));

        SensorHorizontalLayout->addWidget(sensorDistance);

        sensorSeparation = new QDoubleSpinBox(centralWidget);
        sensorSeparation->setObjectName(QStringLiteral("sensorSeparation"));
        sensorSeparation->setValue(4);

        SensorHorizontalLayout->addWidget(sensorSeparation);


        verticalLayout->addLayout(SensorHorizontalLayout);

        CameraTypeHorizontalLayout = new QHBoxLayout();
        CameraTypeHorizontalLayout->setSpacing(6);
        CameraTypeHorizontalLayout->setObjectName(QStringLiteral("CameraTypeHorizontalLayout"));
        CameraTypeHorizontalLayout->setContentsMargins(-1, -1, -1, 0);
        perspectiveRadioButton = new QRadioButton(centralWidget);
        perspectiveRadioButton->setObjectName(QStringLiteral("perspectiveRadioButton"));
        perspectiveRadioButton->setChecked(true);

        CameraTypeHorizontalLayout->addWidget(perspectiveRadioButton);

        orthogonalRadioButton = new QRadioButton(centralWidget);
        orthogonalRadioButton->setObjectName(QStringLiteral("orthogonalRadioButton"));

        CameraTypeHorizontalLayout->addWidget(orthogonalRadioButton);


        verticalLayout->addLayout(CameraTypeHorizontalLayout);

        circuitePathLabel = new QLabel(centralWidget);
        circuitePathLabel->setObjectName(QStringLiteral("circuitePathLabel"));

        verticalLayout->addWidget(circuitePathLabel);

        circuitePath = new QPlainTextEdit(centralWidget);
        circuitePath->setObjectName(QStringLiteral("circuitePath"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(190);
        sizePolicy.setHeightForWidth(circuitePath->sizePolicy().hasHeightForWidth());
        circuitePath->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(circuitePath);

        showRobotCheckBox = new QCheckBox(centralWidget);
        showRobotCheckBox->setObjectName(QStringLiteral("showRobotCheckBox"));
        showRobotCheckBox->setChecked(true);

        verticalLayout->addWidget(showRobotCheckBox);

        timeTittleLabel = new QLabel(centralWidget);
        timeTittleLabel->setObjectName(QStringLiteral("timeTittleLabel"));

        verticalLayout->addWidget(timeTittleLabel);

        timeLabel = new QLabel(centralWidget);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        QFont font;
        font.setPointSize(20);
        timeLabel->setFont(font);

        verticalLayout->addWidget(timeLabel);

        verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        insertParameters = new QPushButton(centralWidget);
        insertParameters->setObjectName(QStringLiteral("insertParameters"));

        verticalLayout->addWidget(insertParameters);

        quit = new QPushButton(centralWidget);
        quit->setObjectName(QStringLiteral("quit"));

        verticalLayout->addWidget(quit);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        widget = new GLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMaximumSize(QSize(715, 715));
        robotPhoto = new QLabel(widget);
        robotPhoto->setObjectName(QStringLiteral("robotPhoto"));
        robotPhoto->setGeometry(QRect(140, 110, 411, 521));
        robotPhoto->setPixmap(QPixmap(QString::fromUtf8(":/Robot.jpg")));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
#ifndef QT_NO_SHORTCUT
#endif // QT_NO_SHORTCUT

        retranslateUi(MainWindow);
        QObject::connect(quit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Robot Siguelineas", Q_NULLPTR));
        wheelSpeedLabel->setText(QApplication::translate("MainWindow", "Wheel speed", Q_NULLPTR));
        wheelRadiusLabel->setText(QApplication::translate("MainWindow", "Wheel radius - WR", Q_NULLPTR));
        wheelSeparationLabel->setText(QApplication::translate("MainWindow", "Wheel separation - WS", Q_NULLPTR));
        distanceToWheelsLabel->setText(QApplication::translate("MainWindow", "Distance to wheels - WD", Q_NULLPTR));
        robotHighLabel->setText(QApplication::translate("MainWindow", "Robot high - L", Q_NULLPTR));
        robotWidthLabel->setText(QApplication::translate("MainWindow", "Robot width - A", Q_NULLPTR));
        sensorDistanceLabel->setText(QApplication::translate("MainWindow", "Sensor distance - SD", Q_NULLPTR));
        sensorSeparationLabel->setText(QApplication::translate("MainWindow", "Sensor separation - SS", Q_NULLPTR));
        perspectiveRadioButton->setText(QApplication::translate("MainWindow", "Perspective", Q_NULLPTR));
        orthogonalRadioButton->setText(QApplication::translate("MainWindow", "Orthogonal", Q_NULLPTR));
        circuitePathLabel->setText(QApplication::translate("MainWindow", "Circuite path", Q_NULLPTR));
        circuitePath->setPlainText(QApplication::translate("MainWindow", "C:\\GitHub\\TFG\\TFG-RobotSiguelineas\\Circuitos\\circuito.txt", Q_NULLPTR));
        circuitePath->setPlaceholderText(QString());
        showRobotCheckBox->setText(QApplication::translate("MainWindow", "Show robot image", Q_NULLPTR));
        timeTittleLabel->setText(QApplication::translate("MainWindow", "Time", Q_NULLPTR));
        timeLabel->setText(QApplication::translate("MainWindow", "0s", Q_NULLPTR));
        insertParameters->setText(QApplication::translate("MainWindow", "Insert Parameters", Q_NULLPTR));
        quit->setText(QApplication::translate("MainWindow", "&Quit", Q_NULLPTR));
        robotPhoto->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
