#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    photoHigh = ui->robotPhoto->height();
    photoWidth = ui->robotPhoto->width();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_insertParameters_clicked()
{
    GLdouble wheelSpeed, wheelRadius, wheelSeparation, sensorSeparation, sensorDistance, robotHigh, robotWidth,distanceToWheels;
    QString circuitePath = "";

    wheelSpeed = ui->wheelSpeed->value();
    wheelRadius = ui->wheelRadius->value();
    wheelSeparation = ui->wheelSeparation->value();
    sensorSeparation = ui->sensorSeparation->value();
    sensorDistance = ui->sensorSeparation->value();
    robotHigh = ui -> robotHigh ->value();
    robotWidth = ui->robotWidth->value();
    distanceToWheels = ui->distanceToWheels->value();
    circuitePath = ui->circuitePath->toPlainText();

    if(wheelSpeed==0 && wheelRadius==0 && wheelSeparation==0 && sensorSeparation==0 && robotHigh==0 && robotWidth==0 && distanceToWheels==0 && sensorDistance==0){
        ui->widget->setWheelSpeed(2*2*M_PI);
        ui->widget->setWheelRadius(2);
        ui->widget->setWheelSeparation(16);
        ui->widget->setSensorPosition(4,0);
        ui->widget->setRobotSize(16,22);
        ui->widget->setCameraType(ui->perspectiveRadioButton->isChecked());
        ui->widget->setCircuite(circuitePath);
        ui->widget->setWheelPosition(3);

    }else{
        ui->widget->setWheelSpeed(wheelSpeed*2*M_PI);
        ui->widget->setWheelRadius(wheelRadius);
        ui->widget->setWheelSeparation(wheelSeparation);
        ui->widget->setSensorPosition(sensorSeparation,sensorDistance);
        ui->widget->setRobotSize(robotWidth,robotHigh);
        ui->widget->setWheelPosition(distanceToWheels);
        ui->widget->setCameraType(ui->perspectiveRadioButton->isChecked());
        ui->widget->setCircuite(circuitePath);

    }

    ui->widget->startRace(this);
}
void MainWindow::setTimer(QString totalTime){
    ui->timeLabel->setText(totalTime);
}

void MainWindow::on_showRobotCheckBox_clicked()
{
    if(ui->showRobotCheckBox->isChecked()){
        ui->robotPhoto->setFixedHeight(photoHigh);
        ui->robotPhoto->setFixedWidth(photoWidth);
    }else{
        ui->robotPhoto->setFixedWidth(0);
        ui->robotPhoto->setFixedHeight(0);
    }
}
