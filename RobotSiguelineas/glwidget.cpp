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
#include <mainwindow.h>

GLWidget::GLWidget(QWidget *parent):
        QOpenGLWidget(parent)
{
    start = false;
    totalTime = 0.0f;
    sleepValue = 20;
    dt = 0.01;

    threshold = 0.3;

    connect(&timer, SIGNAL(timeout()),this,SLOT(update()));
    timer.start(sleepValue);
}

void GLWidget::initializeGL(){
    glEnable(GL_DEPTH_TEST);
    // Modelo de Iluminación
        glEnable(GL_LIGHTING);

     // Parámetros de la Luz ambiental global
        GLfloat IA[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, IA);

     // Parámetros de la Luz 0 (direccional=sol)
        GLfloat Ia0[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat Id0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
        GLfloat Is0[] = { 0.3f, 0.3f, 0.3f, 1.0f };
        glLightfv(GL_LIGHT0, GL_AMBIENT , Ia0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE , Id0);
        glLightfv(GL_LIGHT0, GL_SPECULAR, Is0);
        glEnable(GL_LIGHT0);

     // Parámetros de la Luz 1 (posicional=bombilla)
        GLfloat Ia1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat Id1[] = { 0.9f, 0.9f, 0.9f, 1.0f };
        GLfloat Is1[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        glLightfv(GL_LIGHT1, GL_AMBIENT , Ia1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE , Id1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, Is1);
        glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION , 0.90f);
        glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION   , 0.05f);
        glLightf (GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01f);
        glEnable(GL_LIGHT1);

     // Modelo de sombreado
        glShadeModel(GL_SMOOTH);

     // Normalizado de coordenadas normales
        glEnable(GL_NORMALIZE);

}

void GLWidget::paintGL(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    if(start){
        totalTime+=dt*3.1;
        QString s = QString::number((int)totalTime);
        uiWindow->setTimer(s+"s");
        glLoadIdentity();
        glm::vec3 cameraPos;
        if(isPerspective)
            //cameraPos = glm::vec3(cameraPosCircuite.at(0),cameraPosCircuite.at(1),cameraPosCircuite.at(1));
            cameraPos = glm::vec3(4.0*qSin(newX*M_PI/180),4.0*newY,4.0*qSin(newZ*M_PI/180));
        else
            cameraPos = glm::vec3(cameraPosCircuite.at(0),cameraPosCircuite.at(1),cameraPosCircuite.at(2));
        glm::vec3 cameraDir = glm::vec3(cameraPosCircuite.at(0),0.0f,cameraPosCircuite.at(2));
        glm::vec3 up = glm::vec3(0.0f,0.0f,-1.0f);

        view = glm::lookAt(cameraPos,cameraDir,up);

        const float *viewM = (const float*)glm::value_ptr(view);

        glLoadMatrixf(viewM);

        drawCircuite();

        movementController();

        x -= (rightWheel + leftWheel) * (wheelRadius * qSin(rot)/2) * dt;
        z -= (rightWheel + leftWheel) * (wheelRadius * qCos(rot)/2) * dt;
        rot += (rightWheel - leftWheel)* (wheelRadius/wheelSeparation) * dt;

        model = glm::translate(glm::mat4(1.0),glm::vec3(x,0.0f,z));
        model = glm::rotate(model,(float)(rot),glm::vec3(0.0f,1.0f,0.0f));

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

    //update();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
    if(isPerspective){
        newX = w - (GLfloat) event->x();
        newY = (GLfloat) event->y() - h;
        if(newX> w) newX =  w;
        if(newY> h) newY =  h;
        if(newX<-w) newX = -w;
        if(newY<-h) newY = -h;
        newX /= 5.0f;
        newY /= 5.0f;
    }
}

void GLWidget::wheelEvent(QWheelEvent *event){
    if(isPerspective){
        fov -= event->delta()/50;
        this->resize(this->width()+1,this->height()+1);
        this->resize(this->width()-1,this->height()-1);
    }
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
    this->w = w;
    this->h = h;
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    if(start){
        GLdouble aspect = w / h;
        const GLdouble zNear = 1.0;
        const GLdouble zFar = 500.0;

        if(isPerspective){
            projection = glm::perspective(fov*(M_PI/180)/1.5,aspect,zNear,zFar);
        }else{
            //projection = glm::ortho((double)(-w/80)*aspect,(double)(w/80)*aspect,(double)(-h/80)*aspect,(double)(h/80)*aspect,zNear,zFar);
            //projection = glm::ortho((double)-h*aspect,(double)h*aspect,(double)-h,(double)h,(double)zNear,(double)zFar);
            //projection = glm::ortho((-zFar/2)*w/h,(zFar/2)*w/h,-zFar/2,zFar/2,zNear,zFar);
            projection = glm::ortho((-zFar/4)*w/h,(zFar/4)*w/h,(-zFar/4)*w/h,(zFar/4)*w/h,zNear,zFar);
            //projection = glm::ortho(-200.0,300.0,-200.0,300.0,zNear,zFar);
        }
        const float *projectionM = (const float*)glm::value_ptr(projection);

        glLoadMatrixf(projectionM);
    }

}

void GLWidget::drawCircuite()
{
    glLineWidth(2.0f);
    glColor3f(0.7f,0.0f,0.0f);
    glBegin(GL_LINE_STRIP);
        for(int i = 0; i<circuite.length();i++){
            glVertex3f(circuite.at(i).at(0),circuite.at(i).at(1),circuite.at(i).at(2));
        }
    glEnd();
}

void GLWidget:: drawRobot(){

    // Posición/orientación del robot
       //glTranslatef(desX,0.0f,desZ);
       //glRotatef(rotY,0.0f,1.0f,0.0f);

    // Dibujo del robot
       glRotatef(-90.0f,1.0f,0.0f,0.0f); // Como está diseñado en vertical, aquí lo pongo en horizontal
       glTranslatef(0,0,wheelRadius+0.5);
       drawCuerpo();
       drawRuedasDelanteras();
       drawRuedaTrasera();
       drawSensores();

  /*
    //Sensor derecho
    glPushMatrix();
        glTranslatef(rightSensorX,0,-sensorZ);
        glColor3f(0.7f,0.0f,0.0f);
        glutSolidCube(0.5);
    glPopMatrix();

    //Sensor izquierdo
    glPushMatrix();
        glTranslatef(leftSensorX,0,-sensorZ);
        glColor3f(0.0f,7.0f,0.0f);
        glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,((robotHigh/2)-distanceToWheels));
        glScalef(robotWidth,0.5,robotHigh);
        glColor3f(0.0f,0.0f,7.0f);
        glutSolidCube(1.0f);
    glPopMatrix();
    */

}
void GLWidget:: drawCuerpo() {

 // Tornillo central negro
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidSphere(1.0f,20,20);

 // Plataforma
    glPushMatrix();
    // Aspa (red plastic)
        GLfloat Ka[] = { 0.3f, 1.0f, 0.3f, 1.0f };
        GLfloat Kd[] = { 0.3f, 1.0f, 0.3f, 1.0f };
        GLfloat Ks[] = { 0.3f, 1.0f, 0.3f, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
        glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
        glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
        glMaterialf (GL_FRONT, GL_SHININESS, 32.0f);

     // Redimensionamos el cubo para convertirlo en la plataforma
        glTranslatef(0.0f,-(robotHigh/2.0f-distanceToWheels),0.0f);
        glScalef(robotWidth,robotHigh,1.0f);
     // Modelo solido/alambre de un cubo de lado 2
        //glColor3f(0.0f,0.0f,1.0f);
        glutWireCube (1.0f);
        glColor3f(1.0f,1.0f,0.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

}


void GLWidget:: drawRuedasDelanteras() {

 // Colocamos las ruedas en su sitio
    //GLfloat distRueda = distanceToWheels/2.0f + 1.0f;
    GLfloat distRueda = wheelSeparation/2.0f;
    glPushMatrix();
        GLfloat Ka[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat Kd[] = { 0.5f, 0.5f, 0.0f, 1.0f };
        GLfloat Ks[] = { 0.7f, 0.6f, 0.6f, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
        glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
        glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
        glMaterialf (GL_FRONT, GL_SHININESS, 32.0f);
        glPushMatrix();
            glTranslatef(-distRueda,0.0f,0.0f);
            drawRuedaDelantera();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(distRueda,0.0f,0.0f);
            drawRuedaDelantera();
        glPopMatrix();
    glPopMatrix();

}

void GLWidget:: drawRuedaDelantera() {

    glPushMatrix();
        glRotatef(90.0f,0.0f,1.0f,0.0f); // Orientamos la rueda
     // Redimensionamos la esfera para convertirla en la rueda
        glScalef(1.0f,1.0f,1.0f/wheelRadius);
     // Modelo solido/alambre de una esfera de radio wheelradius
        glColor3f(0.0f,1.0f,1.0f);
        glutWireSphere (wheelRadius,10,5);
        glColor3f(0.0f,0.0f,1.0f);
        glutSolidSphere(wheelRadius,10,5);
    glPopMatrix();

}


void GLWidget:: drawRuedaTrasera() {

    glPushMatrix();
      // Ubicamos la rueda dentro del robot
        glTranslatef(0.0f,-(robotHigh-4.0f),-wheelRadius);
     // Modelo solido/alambre del soporte
        glColor3f(1.0f,1.0f,1.0f);
        glutWireCylinder (0.2f,wheelRadius,10,5);
        glColor3f(0.5f,0.5f,0.5f);
        glutSolidCylinder(0.2f,wheelRadius,10,5);
     // Modelo solido/alambre de la frueda
        glRotatef(90.0f,0.0f,1.0f,0.0f);
        glScalef(1.0f, 1.0f, 0.5f);
        glColor3f(0.5f, 0.0f, 0.0f);
        glutWireSphere (1.0f,10,5);
        glColor3f(0.0f, 1.0f, 0.0f);
        glutSolidSphere(1.0f,10,5);
    glPopMatrix();

}


void GLWidget:: drawSensores() {

 // Colocamos los sensores en su sitio
    GLfloat distSensor = sensorSeparation/2.0f;
    glPushMatrix();
        GLfloat Ka[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat Kd[] = { 0.0f, 0.7f, 1.0f, 1.0f };
        GLfloat Ks[] = { 0.7f, 0.6f, 0.6f, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
        glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
        glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
        glMaterialf (GL_FRONT, GL_SHININESS, 32.0f);
        glPushMatrix();
            glTranslatef(-distSensor,distanceToWheels+sensorDistance,-(wheelRadius-0.5f));
            drawSensor();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(distSensor,distanceToWheels+sensorDistance, -(wheelRadius-0.5f));
            drawSensor();
        glPopMatrix();
    glPopMatrix();

}


void GLWidget:: drawSensor() {

 // El soporte del sensor es un modelo solido/alambre de un cilindro de longitud wheelRadius-1 y radio 0.2
    glColor3f(1.0f,1.0f,1.0f);
    glutWireCylinder (0.2f,wheelRadius-0.5f,10,5);
    glColor3f(0.5f,0.5f,0.5f);
    glutSolidCylinder(0.2f,wheelRadius-0.5f,10,5);

 // El sensor es un modelo solido/alambre de un cubo de lado 2
    glPushMatrix();
        glColor3f(1.0f,1.0f,0.0f);
        glutWireCube (1.0f);
        glColor3f(1.0f,0.0f,0.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

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

    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while(!file.atEnd()){
        QList<float> vertex;
        QString line = file.readLine();
        line.replace(',','.');
        int index = line.indexOf('.',4);
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

    //Mediante trigonometria se calcula la altura que deberia tener la camara para que viera todo el circuito
    cameraPosCircuite<<(((high/2)*qSin((90-(fov/2))*M_PI/180))/qSin((fov/2)*M_PI/180)+15);
    //cameraPosCircuite<<(((high/2)*qSin((90-(fov/2))*M_PI/180))/qSin((fov/2)*M_PI/180));

    cameraPosCircuite<<(bottom+top)/2;
    cameraTopPos = (bottom+top)/2;
    newX = cameraPosCircuite.at(0);
    newY = cameraPosCircuite.at(1);
    newZ = cameraPosCircuite.at(2);

    /*
     * para comprobar que los sensores estan bien colocados
    x = cameraPosCircuite.at(0);
    z = cameraPosCircuite.at(2);
    */
    x = this->circuite.at(0).at(0);
    z = this->circuite.at(0).at(2);
    rot = 0.0f;
}

void GLWidget::setCameraType(bool perspectiveCamera){
    isPerspective = perspectiveCamera;
}

void GLWidget::startRace(MainWindow *mWindow){
    sensorZ = sensorDistance + distanceToWheels;
    leftSensorVector = glm::vec4 (leftSensorX,0,-sensorZ,1);
    rightSensorVector = glm::vec4 (rightSensorX,0,-sensorZ,1);
    leftSensorPos = leftSensorVector;
    rightSensorPos = rightSensorVector;
    totalTime = 0;
    uiWindow = mWindow;
    start= true;
    this->resize(this->width()+1,this->height()+1);
    this->resize(this->width()-1,this->height()-1);
}
