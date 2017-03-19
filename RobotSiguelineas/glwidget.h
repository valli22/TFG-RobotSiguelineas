#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

private:

    //Posicion en X del robot en el instante anterior (t-1)
    GLfloat xPosBefore;
    //Posicion en Y del robot en el instante anterior (t-1)
    GLfloat yPosBefore;
    //Angulo que tenia el robot en el instante anterior (t-1)
    GLfloat rotPosBefore;

    //Velocidad rueda izquierda
    GLfloat leftWheel;
    //Velocidad rueda derecha
    GLfloat rightWheel;

    //Radio de las ruedas
    GLfloat wheelRadius;
    //Distancia entre las dos ruedas
    GLfloat wheelSeparation;

    //Tiempo que transcurre entre dos instantes
    GLfloat dt;

    void keyPressEvent(QKeyEvent *event);
    void drawCircuite();
};

#endif // GLWIDGET_H
