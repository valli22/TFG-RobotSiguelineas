#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include "glm/gtc/matrix_transform.hpp"
#include <QMainWindow>
#include <mainwindow.h>
#include <QTimer>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void setWheelSpeed(GLdouble speed);
    void setWheelRadius(GLdouble radius);
    void setWheelSeparation(GLdouble separation);
    void setSensorPosition(GLdouble separation,GLdouble distance);
    void setRobotSize(GLdouble width, GLdouble high);
    void setWheelPosition(GLdouble dToWheel);
    void setCircuite(QString circuite);
    void setCameraType(bool perspectiveCamera);
    void startRace(MainWindow *mWindow);

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
    glm::vec4 leftSensorVector;
    glm::vec4 rightSensorVector;
    glm::vec4 leftSensorPos;
    glm::vec4 rightSensorPos;

    bool start;

    //FOV de la camara
    GLdouble fov = 75.0;

    //Tipo de camara
    bool isPerspective;

    //Posicion de la camara que se posicionara segun la posicion del circuito
    QList<float> cameraPosCircuite;
    float cameraTopPos;

    GLfloat newX = 0.0f;
    GLfloat newY = 0.0f;
    GLfloat newZ = 0.0f;

    //Lista de puntos que conforman el circuito
    QList< QList<float> > circuite;

    //Umbral de cercania de los sensores a las lineas del circuito
    GLfloat threshold;

    //Velocidad de las ruedas
    GLfloat wheelSpeed;

    //Matrices
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;

    //Tiempo total
    float totalTime;
    int sleepValue;
    MainWindow *uiWindow;

    //Viewport
    float w,h;

    //Radio sobre el que se mueve la camara
    GLfloat cameraRadius;

    QTimer timer;

    //void keyPressEvent(QKeyEvent *event);
    void drawCircuite();
    void drawRobot();
    void movementController();
    void drawCuerpo();
    void drawRuedasDelanteras();
    void drawRuedaTrasera();
    void drawSensores();
    void drawRuedaDelantera();
    void drawSensor();
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};

#endif // GLWIDGET_H
