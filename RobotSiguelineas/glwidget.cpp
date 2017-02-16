#include "glwidget.h"
#include "GL/freeglut.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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

    glLoadIdentity();

    GLdouble aspect = w / h;
    const GLdouble zNear = 1.0;
    const GLdouble zFar = 25.0;
    const GLdouble fov = 75.0;

    perspective(fov,aspect,zNear,zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glm::vec3 cameraPos = glm::vec3(0.0f,0.0f,5.0f);
    glm::vec3 cameraDir = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);

    glm::mat4 view = glm::lookAt(cameraPos,cameraDir,up);

    const float *viewM = (const float*)glm::value_ptr(view);

    glLoadMatrixf(viewM);
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
