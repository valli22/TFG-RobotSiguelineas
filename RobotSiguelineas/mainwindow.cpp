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
    GLdouble wheelSpeed, wheelRadius, wheelSeparation, sensorSeparation, robotRadius;

    wheelSpeed = ui->wheelSpeed->value();
    wheelRadius = ui->wheelRadius->value();
    wheelSeparation = ui->wheelSeparation->value();
    sensorSeparation = ui->sensorSeparation->value();
    robotRadius = ui->robotRadius->value();

    ui->widget->setWheelSpeed(wheelSpeed);
    ui->widget->setWheelRadius(wheelRadius);
    ui->widget->setWheelSeparation(wheelSeparation);
    ui->widget->setSensorSeparation(sensorSeparation);
    ui->widget->setRobotRadius(robotRadius);
}
