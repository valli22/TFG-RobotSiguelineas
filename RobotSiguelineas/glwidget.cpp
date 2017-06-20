#include "glwidget.h"
#include "GL/freeglut.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "QKeyEvent"
#include "QTextStream"
#include <qmath.h>
#include <qlist.h>
#include <QFile>
#include <QDebug>

GLWidget::GLWidget(QWidget *parent):
        QOpenGLWidget(parent)
{

    start = false;

    dt = 0.05f;

    threshold = 0.15;

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



    if(start){

        glLoadIdentity();
        glm::vec3 cameraPos = glm::vec3(cameraPosCircuite.at(0),cameraPosCircuite.at(1),cameraPosCircuite.at(2));
        glm::vec3 cameraDir = glm::vec3(cameraPosCircuite.at(0),0.0f,cameraPosCircuite.at(2));
        glm::vec3 up = glm::vec3(0.0f,0.0f,-1.0f);

        view = glm::lookAt(cameraPos,cameraDir,up);

        const float *viewM = (const float*)glm::value_ptr(view);

        glLoadMatrixf(viewM);

        drawCircuite();

        movementController();
        x -= (rightWheel + leftWheel) * ((wheelRadius * qSin(rot*M_PI/180))/2) * dt;
        z -= (rightWheel + leftWheel) * ((wheelRadius * qCos(rot*M_PI/180))/2) * dt;
        rot += (rightWheel - leftWheel)* (wheelRadius/wheelSeparation) * dt;

        model = glm::translate(glm::mat4(1.0),glm::vec3(x,0.0f,z));
        model = glm::rotate(model,(float)((rot*M_PI)/180),glm::vec3(0.0f,1.0f,0.0f));

        //mat4xvec4 vec4 is consider column
        //vec4xmat4 vec4 is consider row
        leftSensorPos = model*leftSensorVector;
        rightSensorPos = model*rightSensorVector;

        const float *modelM = (const float*)glm::value_ptr(model);
        glPushMatrix();
            glMultMatrixf(modelM);
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
    const GLdouble zFar = 50.0;

    projection = glm::perspective(fov*(M_PI/180),aspect,zNear,zFar);

    const float *projectionM = (const float*)glm::value_ptr(projection);

    glLoadMatrixf(projectionM);

}

void GLWidget::drawCircuite()
{
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
        for(int i = 0; i<circuite.length();i++){
            glVertex3f(circuite.at(i).at(0),circuite.at(i).at(1),circuite.at(i).at(2));
        }
    glEnd();
}

void GLWidget::drawRobot(){

    glPushMatrix();
        glTranslatef(rightSensorX,0,-sensorZ);
        glutSolidCube(0.05);
    glPopMatrix();

    //Sensor izquierdo
    glPushMatrix();
        glTranslatef(leftSensorX,0,-sensorZ);
        glutSolidCube(0.05);
    glPopMatrix();

    glTranslatef(0,0,((robotHigh/2)-distanceToWheels));
    glScalef(robotWidth,0.5,robotHigh);
    glutSolidCube(1.0f);

}

void GLWidget::movementController(){
    for(int i=0;i<circuite.length();i++){
        float distance = sqrt(pow(circuite.at(i).at(0)-leftSensorPos.x,2)+pow(circuite.at(i).at(2)-leftSensorPos.z,2));
        if(distance<threshold){
            leftWheel = 0;
            break;
        }
    }
    for(int i=0;i<circuite.length();i++){
        float distance = sqrt(pow(circuite.at(i).at(0)-rightSensorPos.x,2)+pow(circuite.at(i).at(2)-rightSensorPos.z,2));
        if(distance<threshold){
            rightWheel = 0;
            break;
        }
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

void GLWidget::setSensorPosition(GLdouble separation,GLdouble distance){
    sensorSeparation = separation;
    sensorDistance = distance;
    leftSensorX = -sensorSeparation / 2.0f;
    rightSensorX = sensorSeparation / 2.0f;
}

void GLWidget::setRobotSize(GLdouble width, GLdouble high){
    robotWidth = width;
    robotHigh = high;
}

void GLWidget::setWheelPosition(GLdouble dToWheel){
    distanceToWheels = dToWheel;
}

void GLWidget::setCircuite(QString circuite){
    QString path = circuite;

    if(path==""){
        path = "F:\\TFG\\Git\\TFG-RobotSiguelineas\\Circuitos\\circuito2.txt";
    }

    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while(!file.atEnd()){
        QList<float> vertex;
        QString line = file.readLine();
        line.replace(',','.');
        int index = line.indexOf('.',2);
        line.replace(index,1,' ');
        QStringList points = line.split(' ');
        vertex<<points.at(0).toFloat()<<0<<points.at(1).toFloat();
        this->circuite<<vertex;
    }

    float left = this->circuite.at(0).at(0);
    float right = this->circuite.at(0).at(0);
    float top = this->circuite.at(0).at(2);
    float bottom = this->circuite.at(0).at(2);
    float high;
    for(int i = 0; i<this->circuite.length();i++){
        if(left > this->circuite.at(i).at(0))
            left = this->circuite.at(i).at(0);
        if(right < this->circuite.at(i).at(0))
            right = this->circuite.at(i).at(0);
        if(bottom > this->circuite.at(i).at(2))
            bottom = this->circuite.at(i).at(2);
        if(top < this->circuite.at(i).at(2))
            top = this->circuite.at(i).at(2);
    }

    cameraPosCircuite<<(left+right)/2;

    if(right-left > top-bottom){
        high = right-left;
    }else{
        high = top-bottom;
    }

    //Mediante trigonometria se calcula la altura que deberia tener la camara para que viera todo el circuito y se le añade un poco de margen
    cameraPosCircuite<<(((high/2)*qSin((90-(fov/2))*M_PI/180))/qSin((fov/2)*M_PI/180));

    cameraPosCircuite<<(bottom+top)/2;

    /*
     * para comprobar que los sensores estan bien colocados
    x = cameraPosCircuite.at(0);
    z = cameraPosCircuite.at(2);
    */
    x = this->circuite.at(0).at(0);
    z = this->circuite.at(0).at(2);
    rot = 0.0f;
}

void GLWidget::startRace(){
    sensorZ = sensorDistance + distanceToWheels;
    leftSensorVector = glm::vec4 (leftSensorX,0,-sensorZ,1);
    rightSensorVector = glm::vec4 (rightSensorX,0,-sensorZ,1);
    start= true;
}
