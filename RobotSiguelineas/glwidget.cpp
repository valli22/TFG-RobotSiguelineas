#include "glwidget.h"
#include "GL/freeglut.h"

GLWidget::GLWidget(QWidget *parent):
        QOpenGLWidget(parent)
{
}

void GLWidget::initializeGL(){
    glClearColor(0.2,0.2,0.2,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotatef(0.5,1,1,1);
    glColor3f(1,0.6,0);
    //glTranslatef(-0.5,0,0);
    glutWireTeapot(0.6);
    update();
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);

    /*glLoadIdentity();

    GLdouble aspect = w / h;
    const GLdouble zNear = 1.0;
    const GLdouble zFar = 25.0;
    const GLdouble fov = 75.0;

    perspective(fov,aspect,zNear,zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/
    //gluLookAt(0,0,5, 0,0,0, 0,1,0);
}

/*void GLWidget::perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan( fovy * M_PI / 360.0 );
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}*/

/*void GLWidget::perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar){
    GLdouble top, bottom, left, right;
    top = zNear * tan(M_PI*fovy/2);
    bottom = -top;
    right = aspect*top;
    left = -right;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(left, right, bottom, top, zNear, zFar);
    glMatrixMode(GL_MODELVIEW);
}*/
