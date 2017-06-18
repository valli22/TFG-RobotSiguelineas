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

    threshold = 0.1;

    i=0;

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



    if(start){

        glLoadIdentity();
        glm::vec3 cameraPos = glm::vec3(cameraPosCircuite.at(0),cameraPosCircuite.at(1),cameraPosCircuite.at(2));
        glm::vec3 cameraDir = glm::vec3(cameraPosCircuite.at(0),0.0f,cameraPosCircuite.at(2));
        glm::vec3 up = glm::vec3(0.0f,0.0f,-1.0f);

        view = glm::lookAt(cameraPos,cameraDir,up);

        const float *viewM = (const float*)glm::value_ptr(view);

        glLoadMatrixf(viewM);

        drawCircuite();

        //movementController();
        x -= (rightWheel + leftWheel) * ((wheelRadius * qSin(rot*M_PI/180))/2) * dt;
        z -= (rightWheel + leftWheel) * ((wheelRadius * qCos(rot*M_PI/180))/2) * dt;
        rot += (rightWheel - leftWheel)* (wheelRadius/wheelSeparation) * dt;

        /*glPushMatrix();
            glTranslatef(x,0.0f,z);
            glRotatef(rot,0.0f,1.0f,0.0f);

            drawRobot();
        glPopMatrix();
        */

        model = glm::translate(glm::mat4(1.0),glm::vec3(x,0.0f,z));
        model = glm::rotate(model,(float)((rot*M_PI)/180),glm::vec3(0.0f,1.0f,0.0f));

        mvp = projection * view * model;


        const float *modelM = (const float*)glm::value_ptr(model);
        glPushMatrix();
            glMultMatrixf(modelM);
            drawRobot();
        glPopMatrix();

        //qDebug()<<circuite.at(0).at(0);
        //qDebug()<<circuite.at(0).at(2);
        /*
        qDebug()<<x;
        qDebug()<<z;
        */

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

    //perspective(fov,aspect,zNear,zFar);

}

/*void GLWidget::perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan( fovy * M_PI / 360.0 );
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = -xmin;

    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}*/



/*void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        leftWheel = 0.0f;
        break;
    case Qt::Key_D:
        rightWheel = 0.0f;
        break;
    }
}*/


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
    /*
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
    */
    /*
    glBegin(GL_QUAD_STRIP);
        glVertex3f(-robotWidth/2,0,robotHigh/2);
        glVertex3f(-robotWidth/2,0,-robotHigh/2);
        glVertex3f(robotWidth/2,0,robotHigh/2);
        glVertex3f(robotWidth/2,0,-robotHigh/2);
    glEnd();
    */
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

    /*
        x = x ... y = z
        Ecuaciones a utilizar
        z-z1 = m * (x-x1)  -->  z = m*x - m*x1 + z1
        m = z2-z1 / x2-x1
        por lo tanto segun la primera formula --> n = -m*x1 + z1
        finalmente la formula quedara como .. z = m*x +n || z - m*x - n = 0
    */
        float m = (circuite.at(i+1).at(2) - circuite.at(i).at(2)) / (circuite.at(i+1).at(0) - circuite.at(i).at(0));
        float n = -m*circuite.at(i).at(0) + circuite.at(i).at(2);
        float moveSensorZ = z-(robotWidth/2);
        float moveRightSensorX = x+(sensorSeparation / 2.0f);
        float moveLeftSensorX = x+(-sensorSeparation / 2.0f);

        /*
          Condiciones para que el punto (x2,z2) este en el segmento dado
          -Estar en la recta infinita : m*x2 + n - z2 >= -threshold && m*x2 + n - z2 <= threshold
          -Coordenada x2 entre las cordenadas x de los puntos extremos del segmento : min(x0,x1) <= x2 <= max(x0,x1)
          -Misma situacion que la anterior con la coordenada z : min(z0,z1) <= z2 <= max(z0,z1)
        */

        if(moveSensorZ - m*moveLeftSensorX - n >= -threshold && moveSensorZ - m*moveLeftSensorX - n <= threshold){
           leftWheel=0.0;
        }
        if(moveSensorZ - m*moveRightSensorX - n >= -threshold && moveSensorZ - m*moveRightSensorX - n <= threshold){
           rightWheel=0.0;
        }

        /*
            Ecuacion de la recta perpendicular que pasa por un punto
            z-z1 = -1/m * x - x1
        */
        /*
            Calculo para saber a que lado de la recta esta un punto
            (x0,z0) es el punto que queremos saber a que lado de la recta esta situado
            d = (z2-z1)*x0 + (x1-x2)*z0 + (x2*z1-z2*x1)
            d=0 pertenece
            d>0 derecha
            d<0 izquierda
            sentido p1--->p2
        */
        float nuevaRectaPunto1X = 0;
        float nuevaRectaPunto1Z;
        float nuevaRectaPunto2X;
        float nuevaRectaPunto2Z = 0;
        // ecuacion de la recta perpendicular : z - circuite.at(i+1).at(2) = -1/m * x - circuite.at(i+1).at(0);
        nuevaRectaPunto1Z = -1/m * nuevaRectaPunto1X - circuite.at(i+1).at(0) + circuite.at(i+1).at(2) ;
        nuevaRectaPunto2X = (nuevaRectaPunto2Z - circuite.at(i+1).at(2) + circuite.at(i+1).at(0))/(-1/m);
        float dRectaAntigua = (nuevaRectaPunto2Z - nuevaRectaPunto1Z)*circuite.at(i).at(0) + (nuevaRectaPunto1X - nuevaRectaPunto2X)*circuite.at(i).at(2)+(nuevaRectaPunto2X*nuevaRectaPunto1Z - nuevaRectaPunto2Z*nuevaRectaPunto1X);
        float dNuevo = (nuevaRectaPunto2Z - nuevaRectaPunto1Z)*x + (nuevaRectaPunto1X - nuevaRectaPunto2X)*(moveSensorZ-1)+(nuevaRectaPunto2X*nuevaRectaPunto1Z - nuevaRectaPunto2Z*nuevaRectaPunto1X);
        if(dRectaAntigua>0 && dNuevo<0){
            i++;
        }else if(dRectaAntigua<0 && dNuevo>0){
            i++;
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
    //sensorZ = -robotDiameter/2.0f;
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
    start= true;
}
