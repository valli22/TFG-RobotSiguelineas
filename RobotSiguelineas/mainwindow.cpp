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

void MainWindow::on_pushButton_2_clicked()
{
    GLdouble wheelSpeed, wheelRadius, wheelSeparation, sensorSeparation, robotDiameter;
    QString circuitePath = "";

    wheelSpeed = ui->wheelSpeed->value();
    wheelRadius = ui->wheelRadius->value();
    wheelSeparation = ui->wheelSeparation->value();
    sensorSeparation = ui->sensorSeparation->value();
    robotDiameter = ui->robotDiameter->value();
    circuitePath = ui->circuitePath->toPlainText();

    if(wheelSpeed==0 && wheelRadius==0 && wheelSeparation==0 && sensorSeparation==0 && robotDiameter==0){
        ui->widget->setWheelSpeed(0.1);
        ui->widget->setWheelRadius(1);
        ui->widget->setWheelSeparation(0.01);
        ui->widget->setSensorSeparation(0.5);
        ui->widget->setRobotDiameter(0.5);
        ui->widget->setCircuite(circuitePath);
        ui->widget->startRace();
    }else{
        ui->widget->setWheelSpeed(wheelSpeed);
        ui->widget->setWheelRadius(wheelRadius);
        ui->widget->setWheelSeparation(wheelSeparation);
        ui->widget->setSensorSeparation(sensorSeparation);
        ui->widget->setRobotDiameter(robotDiameter);
        ui->widget->setCircuite(circuitePath);
        ui->widget->startRace();
    }
}
