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
    void setWheelSpeed(GLdouble speed);
    void setWheelRadius(GLdouble radius);
    void setWheelSeparation(GLdouble separation);
    void setSensorSeparation(GLdouble separation);
    void setRobotDiameter(GLdouble diameter);

private:

    //Posicion en X del robot en el instante anterior (t-1)
    GLfloat x;
    //Posicion en Z del robot en el instante anterior (t-1)
    GLfloat z;
    //Angulo que tenia el robot en el instante anterior (t-1)
    GLfloat rot;

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

    //Distancia entre sensores
    GLfloat sensorSeparation;

    //Diamentro del robot
    GLfloat robotDiameter;

    void keyPressEvent(QKeyEvent *event);
    void drawCircuite();
    void drawRobot();
};

#endif // GLWIDGET_H
