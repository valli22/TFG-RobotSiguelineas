#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include "glm/gtc/matrix_transform.hpp"

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
    void setSensorPosition(GLdouble separation,GLdouble distance);
    void setRobotSize(GLdouble width, GLdouble high);
    void setWheelPosition(GLdouble dToWheel);
    void setCircuite(QString circuite);
    void startRace();

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

    //Distancia desde el borde del robot a los sensores
    GLfloat sensorDistance;

    //Dimensiones del robot
    GLfloat robotWidth;
    GLfloat robotHigh;

    //Distancia desde el borde del robot a las ruedas
    GLfloat distanceToWheels;

    //Posiciones de los sensores en cada momento
    GLfloat leftSensorX;
    GLfloat rightSensorX;
    GLfloat sensorZ;

    bool start;

    //FOV de la camara
    const GLdouble fov = 75.0;

    //Posicion de la camara que se posicionara segun la posicion del circuito
    QList<float> cameraPosCircuite;

    //Lista de puntos que conforman el circuito
    QList< QList<float> > circuite;

    //Umbral de cercania de los sensores a las lineas del circuito
    GLfloat threshold;

    //Velocidad de las ruedas
    GLfloat wheelSpeed;

    //Punto del circuito que indica en la recta en la que se encuentra
    int i;

    //Matrices
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 mvp;

    //void keyPressEvent(QKeyEvent *event);
    void drawCircuite();
    void drawRobot();
    void movementController();
};

#endif // GLWIDGET_H
