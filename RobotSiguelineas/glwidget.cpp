#include "glwidget.h"
#include "GL/freeglut.h"

GLWidget::GLWidget(QWidget *parent):
        QOpenGLWidget(parent)
{
}

void GLWidget::initializeGL(){
    glClearColor(0.2,0.2,0.2,1);

}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    glutWireTeapot(0.6);
}

void GLWidget::resizeGL(int w, int h){

}
