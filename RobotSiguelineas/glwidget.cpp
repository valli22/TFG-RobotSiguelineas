#include "glwidget.h"
#include "GL/freeglut.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "QKeyEvent"
#include "QTextStream"
#include <qmath.h>
#include <qlist.h>
#include <QFile>

GLWidget::GLWidget(QWidget *parent):
        QOpenGLWidget(parent)
{

    start = false;

    //Inicio del robot en (0,0,5) con rotacion 0
    x = 0.0f;
    z = 5.0f;
    rot = 0.0f;


    dt = 0.05f;

    threshold = 0.2;

    /*

    //Velocidad inicial de las ruedas
    leftWheel = 0.0f;
    rightWheel = 0.0f;

    wheelRadius = 1.0f;
    wheelSeparation = 0.01f;


    sensorSeparation = 0.5f;
    robotDiameter = 0.5f;

    leftSensorX = -sensorSeparation / 2.0f;
    rightSensorX = sensorSeparation / 2.0f;
    sensorZ = -robotDiameter/2.0f;

    */

    setFocusPolicy(Qt::StrongFocus);
}

void GLWidget::initializeGL(){
    glClearColor(0.2,0.2,0.2,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glm::vec3 cameraPos = glm::vec3(0.0f,5.0f,5.0f);
    glm::vec3 cameraDir = glm::vec3(0.0f,0.0f,5.0f);
    glm::vec3 up = glm::vec3(0.0f,0.0f,-1.0f);

    glm::mat4 view = glm::lookAt(cameraPos,cameraDir,up);

    const float *viewM = (const float*)glm::value_ptr(view);

    glLoadMatrixf(viewM);

    if(start){

        drawCircuite();

        //movementController();

        x -= (rightWheel + leftWheel) * ((wheelRadius * qSin(rot*M_PI/180))/2) * dt;
        z -= (rightWheel + leftWheel) * ((wheelRadius * qCos(rot*M_PI/180))/2) * dt;
        rot += (rightWheel - leftWheel)* (wheelRadius/wheelSeparation) * dt;

        glPushMatrix();
            glTranslatef(x,0.0f,z);
            glRotatef(rot,0.0f,1.0f,0.0f);

            drawRobot();
        glPopMatrix();

        rightWheel = wheelSpeed;
        leftWheel = wheelSpeed;

    }

    update();
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    GLdouble aspect = w / h;
    const GLdouble zNear = 1.0;
    const GLdouble zFar = 25.0;
    const GLdouble fov = 75.0;

    perspective(fov,aspect,zNear,zFar);

}

void GLWidget::perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan( fovy * M_PI / 360.0 );
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = -xmin;

    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        leftWheel = 0.0f;
        break;
    case Qt::Key_D:
        rightWheel = 0.0f;
        break;
    }
}


void GLWidget::drawCircuite()
{
    if(path==""){
        path = "F:\\TFG\\Git\\TFG-RobotSiguelineas\\Circuitos\\circuito1giro.txt";
    }
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QList<float> vertex;
    glBegin(GL_LINE_STRIP);
        while(!file.atEnd()){

            QString line = file.readLine();
            QStringList points = line.split(' ');
            vertex<<points.at(0).toFloat()<<points.at(1).toFloat()<<points.at(2).toFloat();
            circuite<<vertex;
            glVertex3f(points.at(0).toFloat(),points.at(1).toFloat(),points.at(2).toFloat());

        }
    glEnd();

}

void GLWidget::drawRobot(){
    //Sensor derecho
    glPushMatrix();
        glTranslatef(rightSensorX,0,sensorZ);
        glutSolidCube(0.1);
    glPopMatrix();

    //Sensor izquierdo
    glPushMatrix();
        glTranslatef(leftSensorX,0,sensorZ);
        glutSolidCube(0.1);
    glPopMatrix();

    glutSolidCube(robotDiameter);
}

void GLWidget::movementController(){

    int i = 0;
    // z = (z2-z1 / x2-x1) * (x-x1) + z1

    //Sensor izquierdo
    if(sensorZ - ((circuite.at(i+1).at(2) - circuite.at(i).at(2) / circuite.at(i+1).at(0) - circuite.at(i).at(0)) * (leftSensorX - circuite.at(i).at(0)) + circuite.at(i).at(2)) >= -threshold && sensorZ - ((circuite.at(i+1).at(2) - circuite.at(i).at(2) / circuite.at(i+1).at(0) - circuite.at(i).at(0)) * (leftSensorX - circuite.at(i).at(0)) + circuite.at(i).at(2)) <= threshold){
        leftWheel=0.0;
    }

    //Sensor derecho
    if(sensorZ - ((circuite.at(i+1).at(2) - circuite.at(i).at(2) / circuite.at(i+1).at(0) - circuite.at(i).at(0)) * (rightSensorX - circuite.at(i).at(0)) + circuite.at(i).at(2)) >= -threshold && sensorZ - ((circuite.at(i+1).at(2) - circuite.at(i).at(2) / circuite.at(i+1).at(0) - circuite.at(i).at(0)) * (rightSensorX - circuite.at(i).at(0)) + circuite.at(i).at(2)) <= threshold){
        rightWheel = 0.0;
    }

}

void GLWidget::setWheelSpeed(GLdouble speed){
    leftWheel = speed;
    rightWheel = speed;
    wheelSpeed = speed;
}

void GLWidget::setWheelRadius(GLdouble radius){
    wheelRadius = radius;
}

void GLWidget::setWheelSeparation(GLdouble separation){
    wheelSeparation = separation;
}

void GLWidget::setSensorSeparation(GLdouble separation){
    sensorSeparation = separation;
    leftSensorX = -sensorSeparation / 2.0f;
    rightSensorX = sensorSeparation / 2.0f;
}

void GLWidget::setRobotDiameter(GLdouble diameter){
    robotDiameter = diameter;
    sensorZ = -robotDiameter/2.0f;
}

void GLWidget::setCircuite(QString circuite){
    path = circuite;
}

void GLWidget::startRace(){
    start= true;
}
