#include "glwidget.h"
#include "GL/freeglut.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "QKeyEvent"
#include "QTextStream"
#include <qmath.h>

GLWidget::GLWidget(QWidget *parent):
        QOpenGLWidget(parent)
{

    //Inicio del robot en origen de coordenadas con rotacion 0
    x = 0.0f;
    z = 5.0f;
    rot = 0.0f;

    //Velocidad inicial de las ruedas
    leftWheel = 0.0f;
    rightWheel = 0.0f;

    wheelRadius = 1.0f;
    wheelSeparation = 0.01f;

    dt = 0.05f;

    sensorSeparation = 0.5f;
    robotDiameter = 0.5f;

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

    drawCircuite();

    x -= (rightWheel + leftWheel) * ((wheelRadius * qSin(rot*M_PI/180))/2) * dt;
    z -= (rightWheel + leftWheel) * ((wheelRadius * qCos(rot*M_PI/180))/2) * dt;
    rot += (rightWheel - leftWheel)* (wheelRadius/wheelSeparation) * dt;

    glPushMatrix();
        glTranslatef(x,0.0f,z);
        glRotatef(rot,0.0f,1.0f,0.0f);

        drawRobot();
    glPopMatrix();

    rightWheel = 0.1f;
    leftWheel = 0.1f;

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
    glColor3f(255,0,0);

    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,1,0);
    glEnd();
}

void GLWidget::drawRobot(){

    GLfloat distanceToTheCenter = sensorSeparation / 2.0f;
    //Sensor derecho
    glPushMatrix();
        glTranslatef(distanceToTheCenter,0,-robotDiameter/2.0f);
        glutSolidCube(0.1);
    glPopMatrix();

    //Sensor izquierdo
    glPushMatrix();
        glTranslatef(-distanceToTheCenter,0,-robotDiameter/2.0f);
        glutSolidCube(0.1);
    glPopMatrix();

    glutSolidCube(robotDiameter);
}

void GLWidget::setWheelSpeed(GLdouble speed){
    leftWheel = speed;
    rightWheel = speed;
}

void GLWidget::setWheelRadius(GLdouble radius){
    wheelRadius = radius;
}

void GLWidget::setWheelSeparation(GLdouble separation){
    wheelSeparation = separation;
}

void GLWidget::setSensorSeparation(GLdouble separation){
    sensorSeparation = separation;
}

void GLWidget::setRobotDiameter(GLdouble diameter){
    robotDiameter = diameter;
}

/*void GLWidget::drawCircuite()
{

    glColor3f(255,0,0);

    glBegin(GL_LINES);

        glVertex3f(0.625, 500.5,0);
        glVertex3f(0.875, 507.5,0);
        glVertex3f(1.125, 511.5,0);
        glVertex3f(1.375, 513.5,0);
        glVertex3f(1.625, 516.5,0);
        glVertex3f(1.875, 517.5,0);
        glVertex3f(2.125, 519.5,0);
        glVertex3f(2.375, 520.5,0);
        glVertex3f(2.625, 522.5,0);
        glVertex3f(2.875, 523.5,0);
        glVertex3f(3.125, 524.5,0);
        glVertex3f(3.375, 525.5,0);
        glVertex3f(3.625, 526.5,0);
        glVertex3f(3.875, 527.5,0);
        glVertex3f(4.125, 528.5,0);
        glVertex3f(4.375, 529.5,0);
        glVertex3f(4.625, 530.5,0);
        glVertex3f(4.875, 531.5,0);
        glVertex3f(5.125, 532.5,0);
        glVertex3f(5.375, 533.5,0);
        glVertex3f(5.625, 534.5,0);
        glVertex3f(5.875, 535.5,0);
        glVertex3f(6.125, 536.5,0);
        glVertex3f(6.375, 536.5,0);
        glVertex3f(6.625, 537.5,0);
        glVertex3f(6.875, 538.5,0);
        glVertex3f(7.125, 539.5,0);
        glVertex3f(7.375, 540.5,0);
        glVertex3f(7.625, 540.5,0);
        glVertex3f(7.875, 541.5,0);
        glVertex3f(8.125, 542.5,0);
        glVertex3f(8.375, 543.5,0);
        glVertex3f(8.625, 543.5,0);
        glVertex3f(8.875, 544.5,0);
        glVertex3f(9.125, 545.5,0);
        glVertex3f(9.375, 545.5,0);
        glVertex3f(9.625, 546.5,0);
        glVertex3f(9.875, 547.5,0);
        glVertex3f(10.125, 547.5,0);
        glVertex3f(10.375, 548.5,0);
        glVertex3f(10.625, 549.5,0);
        glVertex3f(0.875, 549.5,0);
        glVertex3f(11.125, 550.5,0);
        glVertex3f(11.375, 551.5,0);
        glVertex3f(11.625, 551.5,0);
        glVertex3f(11.875, 552.5,0);
        glVertex3f(12.125, 553.5,0);
        glVertex3f(12.375, 553.5,0);
        glVertex3f(12.625, 554.5,0);
        glVertex3f(12.875, 555.5,0);
        glVertex3f(13.125, 555.5,0);
        glVertex3f(13.375, 556.5,0);
        glVertex3f(13.625, 556.5,0);
        glVertex3f(13.875, 557.5,0);
        glVertex3f(14.125, 558.5,0);
        glVertex3f(14.375, 558.5,0);
        glVertex3f(14.625, 559.5,0);
        glVertex3f(14.875, 559.5,0);
        glVertex3f(15.125, 560.5,0);
        glVertex3f(15.375, 561.5,0);
        glVertex3f(15.625, 561.5,0);
        glVertex3f(15.875, 562.5,0);
        glVertex3f(16.125, 562.5,0);
        glVertex3f(16.375, 563.5,0);
        glVertex3f(16.625, 563.5,0);
        glVertex3f(16.875, 564.5,0);
        glVertex3f(17.125, 565.5,0);
        glVertex3f(17.375, 565.5,0);
        glVertex3f(17.625, 566.5,0);
        glVertex3f(17.875, 566.5,0);
        glVertex3f(18.125, 567.5,0);
        glVertex3f(18.375, 567.5,0);
        glVertex3f(18.625, 568.5,0);
        glVertex3f(18.875, 569.5,0);
        glVertex3f(19.125, 569.5,0);
        glVertex3f(19.375, 570.5,0);
        glVertex3f(19.625, 570.5,0);
        glVertex3f(19.875, 571.5,0);
        glVertex3f(20.125, 571.5,0);
        glVertex3f(20.375, 572.5,0);
        glVertex3f(20.625, 573.5,0);
        glVertex3f(20.875, 573.5,0);
        glVertex3f(21.125, 574.5,0);
        glVertex3f(21.375, 574.5,0);
        glVertex3f(21.625, 575.5,0);
        glVertex3f(21.875, 575.5,0);
        glVertex3f(22.125, 576.5,0);
        glVertex3f(22.375, 576.5,0);
        glVertex3f(22.625, 577.5,0);
        glVertex3f(22.875, 578.5,0);
        glVertex3f(23.125, 578.5,0);
        glVertex3f(23.375, 579.5,0);
        glVertex3f(23.625, 579.5,0);
        glVertex3f(23.875, 580.5,0);
        glVertex3f(24.125, 580.5,0);
        glVertex3f(24.375, 581.5,0);
        glVertex3f(24.625, 581.5,0);
        glVertex3f(24.875, 582.5,0);
        glVertex3f(25.125, 582.5,0);
        glVertex3f(25.375, 583.5,0);
        glVertex3f(25.625, 583.5,0);
        glVertex3f(25.875, 584.5,0);
        glVertex3f(26.125, 585.5,0);
        glVertex3f(26.375, 585.5,0);
        glVertex3f(26.625, 586.5,0);
        glVertex3f(26.875, 586.5,0);
        glVertex3f(27.125, 587.5,0);
        glVertex3f(27.375, 587.5,0);
        glVertex3f(27.625, 588.5,0);
        glVertex3f(27.875, 588.5,0);
        glVertex3f(28.125, 589.5,0);
        glVertex3f(28.375, 589.5,0);
        glVertex3f(28.625, 590.5,0);
        glVertex3f(28.875, 590.5,0);
        glVertex3f(29.125, 591.5,0);
        glVertex3f(29.375, 592.5,0);
        glVertex3f(29.625, 592.5,0);
        glVertex3f(29.875, 593.5,0);
        glVertex3f(30.125, 593.5,0);
        glVertex3f(30.375, 594.5,0);
        glVertex3f(30.625, 594.5,0);
        glVertex3f(30.875, 595.5,0);
        glVertex3f(31.125, 595.5,0);
        glVertex3f(31.375, 596.5,0);
        glVertex3f(31.625, 596.5,0);
        glVertex3f(31.875, 597.5,0);
        glVertex3f(32.125, 597.5,0);
        glVertex3f(32.375, 598.5,0);
        glVertex3f(32.625, 599.5,0);
        glVertex3f(32.875, 599.5,0);
        glVertex3f(33.125, 600.5,0);
        glVertex3f(33.375, 600.5,0);
        glVertex3f(33.625, 601.5,0);
        glVertex3f(33.875, 601.5,0);
        glVertex3f(34.125, 602.5,0);
        glVertex3f(34.375, 602.5,0);
        glVertex3f(34.625, 603.5,0);
        glVertex3f(34.875, 603.5,0);
        glVertex3f(35.125, 604.5,0);
        glVertex3f(35.375, 604.5,0);
        glVertex3f(35.625, 604.5,0);
        glVertex3f(35.875, 605.5,0);
        glVertex3f(36.125, 605.5,0);
        glVertex3f(36.375, 605.5,0);
        glVertex3f(36.625, 606.5,0);
        glVertex3f(36.875, 606.5,0);
        glVertex3f(37.125, 606.5,0);
        glVertex3f(37.375, 607.5,0);
        glVertex3f(37.625, 607.5,0);
        glVertex3f(37.875, 607.5,0);
        glVertex3f(38.125, 608.5,0);
        glVertex3f(38.375, 608.5,0);
        glVertex3f(38.625, 608.5,0);
        glVertex3f(38.875, 608.5,0);
        glVertex3f(39.125, 609.5,0);
        glVertex3f(39.375, 609.5,0);
        glVertex3f(39.625, 609.5,0);
        glVertex3f(39.875, 609.5,0);
        glVertex3f(40.125, 610.5,0);
        glVertex3f(40.375, 610.5,0);
        glVertex3f(40.625, 610.5,0);
        glVertex3f(40.875, 610.5,0);
        glVertex3f(41.125, 610.5,0);
        glVertex3f(41.375, 611.5,0);
        glVertex3f(41.625, 611.5,0);
        glVertex3f(41.875, 611.5,0);
        glVertex3f(42.125, 611.5,0);
        glVertex3f(42.375, 611.5,0);
        glVertex3f(42.625, 611.5,0);
        glVertex3f(42.875, 611.5,0);
        glVertex3f(43.125, 611.5,0);
        glVertex3f(43.375, 611.5,0);
        glVertex3f(43.625, 611.5,0);
        glVertex3f(43.875, 611.5,0);
        glVertex3f(44.125, 611.5,0);
        glVertex3f(44.375, 611.5,0);
        glVertex3f(44.625, 611.5,0);
        glVertex3f(44.875, 611.5,0);
        glVertex3f(45.125, 611.5,0);
        glVertex3f(45.375, 611.5,0);
        glVertex3f(45.625, 611.5,0);
        glVertex3f(45.875, 611.5,0);
        glVertex3f(46.125, 611.5,0);
        glVertex3f(46.375, 611.5,0);
        glVertex3f(46.625, 611.5,0);
        glVertex3f(46.875, 611.5,0);
        glVertex3f(47.125, 611.5,0);
        glVertex3f(47.375, 611.5,0);
        glVertex3f(47.625, 611.5,0);
        glVertex3f(47.875, 611.5,0);
        glVertex3f(48.125, 610.5,0);
        glVertex3f(48.375, 610.5,0);
        glVertex3f(48.625, 610.5,0);
        glVertex3f(48.875, 610.5,0);
        glVertex3f(49.125, 609.5,0);
        glVertex3f(49.375, 609.5,0);
        glVertex3f(49.625, 608.5,0);
        glVertex3f(49.875, 608.5,0);
        glVertex3f(50.125, 608.5,0);
        glVertex3f(50.375, 607.5,0);
        glVertex3f(50.625, 606.5,0);
        glVertex3f(50.875, 606.5,0);
        glVertex3f(51.125, 605.5,0);
        glVertex3f(51.375, 604.5,0);
        glVertex3f(51.625, 604.5,0);
        glVertex3f(51.875, 603.5,0);
        glVertex3f(52.125, 602.5,0);
        glVertex3f(52.375, 601.5,0);
        glVertex3f(52.625, 600.5,0);
        glVertex3f(52.875, 598.5,0);
        glVertex3f(53.125, 597.5,0);
        glVertex3f(53.375, 594.5,0);
        glVertex3f(53.625, 592.5,0);
        glVertex3f(53.875, 589.5,0);
        glVertex3f(54.125, 580.5,0);
        glVertex3f(54.375, 530.5,0);
        glVertex3f(54.625, 530.5,0);
        glVertex3f(54.875, 529.5,0);
        glVertex3f(55.125, 528.5,0);
        glVertex3f(55.375, 528.5,0);
        glVertex3f(55.625, 527.5,0);
        glVertex3f(55.875, 527.5,0);
        glVertex3f(56.125, 526.5,0);
        glVertex3f(56.375, 526.5,0);
        glVertex3f(56.625, 525.5,0);
        glVertex3f(56.875, 525.5,0);
        glVertex3f(57.125, 525.5,0);
        glVertex3f(57.375, 524.5,0);
        glVertex3f(57.625, 524.5,0);
        glVertex3f(57.875, 524.5,0);
        glVertex3f(58.125, 524.5,0);
        glVertex3f(58.375, 523.5,0);
        glVertex3f(58.625, 523.5,0);
        glVertex3f(58.875, 523.5,0);
        glVertex3f(59.125, 522.5,0);
        glVertex3f(59.375, 522.5,0);
        glVertex3f(59.625, 522.5,0);
        glVertex3f(59.875, 522.5,0);
        glVertex3f(60.125, 522.5,0);
        glVertex3f(60.375, 521.5,0);
        glVertex3f(60.625, 521.5,0);
        glVertex3f(60.875, 521.5,0);
        glVertex3f(61.125, 521.5,0);
        glVertex3f(61.375, 521.5,0);
        glVertex3f(61.625, 520.5,0);
        glVertex3f(61.875, 520.5,0);
        glVertex3f(62.125, 520.5,0);
        glVertex3f(62.375, 520.5,0);
        glVertex3f(62.625, 520.5,0);
        glVertex3f(62.875, 520.5,0);
        glVertex3f(63.125, 520.5,0);
        glVertex3f(63.375, 520.5,0);
        glVertex3f(63.625, 519.5,0);
        glVertex3f(63.875, 519.5,0);
        glVertex3f(64.125, 519.5,0);
        glVertex3f(64.375, 519.5,0);
        glVertex3f(64.625, 519.5,0);
        glVertex3f(64.875, 519.5,0);
        glVertex3f(65.125, 519.5,0);
        glVertex3f(65.375, 519.5,0);
        glVertex3f(65.625, 519.5,0);
        glVertex3f(65.875, 519.5,0);
        glVertex3f(66.125, 518.5,0);
        glVertex3f(66.375, 518.5,0);
        glVertex3f(66.625, 518.5,0);
        glVertex3f(66.875, 518.5,0);
        glVertex3f(67.125, 518.5,0);
        glVertex3f(67.375, 518.5,0);
        glVertex3f(67.625, 518.5,0);
        glVertex3f(67.875, 518.5,0);
        glVertex3f(68.125, 518.5,0);
        glVertex3f(68.375, 518.5,0);
        glVertex3f(68.625, 518.5,0);
        glVertex3f(68.875, 518.5,0);
        glVertex3f(69.125, 518.5,0);
        glVertex3f(69.375, 518.5,0);
        glVertex3f(69.625, 517.5,0);
        glVertex3f(69.875, 517.5,0);
        glVertex3f(70.125, 517.5,0);
        glVertex3f(70.375, 517.5,0);
        glVertex3f(70.625, 517.5,0);
        glVertex3f(70.875, 517.5,0);
        glVertex3f(71.125, 517.5,0);
        glVertex3f(71.375, 517.5,0);
        glVertex3f(71.625, 517.5,0);
        glVertex3f(71.875, 517.5,0);
        glVertex3f(72.125, 517.5,0);
        glVertex3f(72.375, 517.5,0);
        glVertex3f(72.625, 517.5,0);
        glVertex3f(72.875, 517.5,0);
        glVertex3f(73.125, 516.5,0);
        glVertex3f(73.375, 516.5,0);
        glVertex3f(73.625, 516.5,0);
        glVertex3f(73.875, 516.5,0);
        glVertex3f(74.125, 516.5,0);
        glVertex3f(74.375, 516.5,0);
        glVertex3f(74.625, 516.5,0);
        glVertex3f(74.875, 516.5,0);
        glVertex3f(75.125, 516.5,0);
        glVertex3f(75.375, 516.5,0);
        glVertex3f(75.625, 516.5,0);
        glVertex3f(75.875, 516.5,0);
        glVertex3f(76.125, 515.5,0);
        glVertex3f(76.375, 515.5,0);
        glVertex3f(76.625, 515.5,0);
        glVertex3f(76.875, 515.5,0);
        glVertex3f(77.125, 515.5,0);
        glVertex3f(77.375, 515.5,0);
        glVertex3f(77.625, 515.5,0);
        glVertex3f(77.875, 515.5,0);
        glVertex3f(78.125, 515.5,0);
        glVertex3f(78.375, 514.5,0);
        glVertex3f(78.625, 514.5,0);
        glVertex3f(78.875, 514.5,0);
        glVertex3f(79.125, 514.5,0);
        glVertex3f(79.375, 514.5,0);
        glVertex3f(79.625, 514.5,0);
        glVertex3f(79.875, 513.5,0);
        glVertex3f(80.125, 513.5,0);
        glVertex3f(80.375, 513.5,0);
        glVertex3f(80.625, 513.5,0);
        glVertex3f(80.875, 513.5,0);
        glVertex3f(81.125, 513.5,0);
        glVertex3f(81.375, 512.5,0);
        glVertex3f(81.625, 512.5,0);
        glVertex3f(81.875, 512.5,0);
        glVertex3f(82.125, 512.5,0);
        glVertex3f(82.375, 512.5,0);
        glVertex3f(82.625, 511.5,0);
        glVertex3f(82.875, 511.5,0);
        glVertex3f(83.125, 511.5,0);
        glVertex3f(83.375, 511.5,0);
        glVertex3f(83.625, 510.5,0);
        glVertex3f(83.875, 510.5,0);
        glVertex3f(84.125, 510.5,0);
        glVertex3f(84.375, 509.5,0);
        glVertex3f(84.625, 509.5,0);
        glVertex3f(84.875, 508.5,0);
        glVertex3f(85.125, 508.5,0);
        glVertex3f(85.375, 507.5,0);
        glVertex3f(85.625, 507.5,0);
        glVertex3f(85.875, 507.5,0);
        glVertex3f(86.125, 506.5,0);
        glVertex3f(86.375, 505.5,0);
        glVertex3f(86.625, 505.5,0);
        glVertex3f(86.875, 504.5,0);
        glVertex3f(87.125, 504.5,0);
        glVertex3f(87.375, 503.5,0);
        glVertex3f(87.625, 502.5,0);
        glVertex3f(87.875, 502.5,0);
        glVertex3f(88.125, 501.5,0);
        glVertex3f(88.375, 500.5,0);
        glVertex3f(88.625, 499.5,0);
        glVertex3f(88.875, 498.5,0);
        glVertex3f(89.125, 497.5,0);
        glVertex3f(89.375, 496.5,0);
        glVertex3f(89.625, 495.5,0);
        glVertex3f(89.875, 493.5,0);
        glVertex3f(90.125, 491.5,0);
        glVertex3f(90.375, 489.5,0);
        glVertex3f(90.625, 486.5,0);
        glVertex3f(90.875, 482.5,0);
        glVertex3f(91.125, 476.5,0);
        glVertex3f(91.375, 472.5,0);
        glVertex3f(91.625, 471.5,0);
        glVertex3f(91.875, 470.5,0);
        glVertex3f(92.125, 469.5,0);
        glVertex3f(92.375, 468.5,0);
        glVertex3f(92.625, 467.5,0);
        glVertex3f(92.875, 466.5,0);
        glVertex3f(93.125, 465.5,0);
        glVertex3f(93.375, 464.5,0);
        glVertex3f(93.625, 463.5,0);
        glVertex3f(93.875, 463.5,0);
        glVertex3f(94.125, 462.5,0);
        glVertex3f(94.375, 461.5,0);
        glVertex3f(94.625, 460.5,0);
        glVertex3f(94.875, 459.5,0);
        glVertex3f(95.125, 458.5,0);
        glVertex3f(95.375, 457.5,0);
        glVertex3f(95.625, 456.5,0);
        glVertex3f(95.875, 455.5,0);
        glVertex3f(96.125, 454.5,0);
        glVertex3f(96.375, 453.5,0);
        glVertex3f(96.625, 452.5,0);
        glVertex3f(96.875, 451.5,0);
        glVertex3f(97.125, 450.5,0);
        glVertex3f(97.375, 449.5,0);
        glVertex3f(97.625, 448.5,0);
        glVertex3f(97.875, 447.5,0);
        glVertex3f(98.125, 446.5,0);
        glVertex3f(98.375, 445.5,0);
        glVertex3f(98.625, 444.5,0);
        glVertex3f(98.875, 443.5,0);
        glVertex3f(99.125, 442.5,0);
        glVertex3f(99.375, 441.5,0);
        glVertex3f(99.625, 440.5,0);
        glVertex3f(99.875, 439.5,0);
        glVertex3f(100.125, 438.5,0);
        glVertex3f(100.375, 437.5,0);
        glVertex3f(100.625, 436.5,0);
        glVertex3f(100.875, 435.5,0);
        glVertex3f(101.125, 434.5,0);
        glVertex3f(101.375, 433.5,0);
        glVertex3f(101.625, 432.5,0);
        glVertex3f(101.875, 431.5,0);
        glVertex3f(102.125, 430.5,0);
        glVertex3f(102.375, 429.5,0);
        glVertex3f(102.625, 428.5,0);
        glVertex3f(102.875, 427.5,0);
        glVertex3f(103.125, 425.5,0);
        glVertex3f(103.375, 424.5,0);
        glVertex3f(103.625, 423.5,0);
        glVertex3f(103.875, 422.5,0);
        glVertex3f(104.125, 420.5,0);
        glVertex3f(104.375, 419.5,0);
        glVertex3f(104.625, 418.5,0);
        glVertex3f(104.875, 416.5,0);
        glVertex3f(105.125, 415.5,0);
        glVertex3f(105.375, 413.5,0);
        glVertex3f(105.625, 411.5,0);
        glVertex3f(105.875, 408.5,0);
        glVertex3f(106.125, 404.5,0);

    glEnd();

}*/
