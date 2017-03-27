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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    GLWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *wheelSpeedLabel;
    QDoubleSpinBox *wheelSpeed;
    QLabel *wheelRadiusLabel;
    QDoubleSpinBox *wheelRadius;
    QLabel *wheelSeparationLabel;
    QDoubleSpinBox *wheelSeparation;
    QLabel *sensorSeparationLabel;
    QDoubleSpinBox *sensorSeparation;
    QLabel *robotDiameterLabel;
    QDoubleSpinBox *robotDiameter;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(1145, 495);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new GLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        wheelSpeedLabel = new QLabel(centralWidget);
        wheelSpeedLabel->setObjectName(QStringLiteral("wheelSpeedLabel"));

        verticalLayout->addWidget(wheelSpeedLabel);

        wheelSpeed = new QDoubleSpinBox(centralWidget);
        wheelSpeed->setObjectName(QStringLiteral("wheelSpeed"));

        verticalLayout->addWidget(wheelSpeed);

        wheelRadiusLabel = new QLabel(centralWidget);
        wheelRadiusLabel->setObjectName(QStringLiteral("wheelRadiusLabel"));

        verticalLayout->addWidget(wheelRadiusLabel);

        wheelRadius = new QDoubleSpinBox(centralWidget);
        wheelRadius->setObjectName(QStringLiteral("wheelRadius"));

        verticalLayout->addWidget(wheelRadius);

        wheelSeparationLabel = new QLabel(centralWidget);
        wheelSeparationLabel->setObjectName(QStringLiteral("wheelSeparationLabel"));

        verticalLayout->addWidget(wheelSeparationLabel);

        wheelSeparation = new QDoubleSpinBox(centralWidget);
        wheelSeparation->setObjectName(QStringLiteral("wheelSeparation"));

        verticalLayout->addWidget(wheelSeparation);

        sensorSeparationLabel = new QLabel(centralWidget);
        sensorSeparationLabel->setObjectName(QStringLiteral("sensorSeparationLabel"));

        verticalLayout->addWidget(sensorSeparationLabel);

        sensorSeparation = new QDoubleSpinBox(centralWidget);
        sensorSeparation->setObjectName(QStringLiteral("sensorSeparation"));

        verticalLayout->addWidget(sensorSeparation);

        robotDiameterLabel = new QLabel(centralWidget);
        robotDiameterLabel->setObjectName(QStringLiteral("robotDiameterLabel"));

        verticalLayout->addWidget(robotDiameterLabel);

        robotDiameter = new QDoubleSpinBox(centralWidget);
        robotDiameter->setObjectName(QStringLiteral("robotDiameter"));

        verticalLayout->addWidget(robotDiameter);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Robot Siguelineas", Q_NULLPTR));
        wheelSpeedLabel->setText(QApplication::translate("MainWindow", "Wheel speed", Q_NULLPTR));
        wheelRadiusLabel->setText(QApplication::translate("MainWindow", "Wheel radius", Q_NULLPTR));
        wheelSeparationLabel->setText(QApplication::translate("MainWindow", "Wheel separation", Q_NULLPTR));
        sensorSeparationLabel->setText(QApplication::translate("MainWindow", "Sensor separation", Q_NULLPTR));
        robotDiameterLabel->setText(QApplication::translate("MainWindow", "Robot diameter", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Insert Parameters", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "&Quit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
