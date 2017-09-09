#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
        ui->widget->setWheelSpeed(0.1);
        ui->widget->setWheelRadius(1);
        ui->widget->setWheelSeparation(0.01);
        ui->widget->setSensorPosition(0.5,0.2);
        ui->widget->setRobotSize(0.3,0.5);
        ui->widget->setCameraType(ui->perspectiveRadioButton->isChecked());
        ui->widget->setCircuite(circuitePath);
        ui->widget->setWheelPosition(0.1);

    }else{
        ui->widget->setWheelSpeed(wheelSpeed);
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
