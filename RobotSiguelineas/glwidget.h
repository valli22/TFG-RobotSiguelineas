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

    //Diamentro del robot
    GLfloat robotDiameter;

    //Posiciones de los sensores en cada momento
    GLfloat leftSensorX;
    GLfloat rightSensorX;
    GLfloat sensorZ;

    //Path del archivo del circuito
    QString path;

    bool start;

    QList< QList<float> > circuite;

    //Umbral de cercania de los sensores a las lineas del circuito
    GLfloat threshold;

    //Velocidad de las ruedas
    GLfloat wheelSpeed;

    //void keyPressEvent(QKeyEvent *event);
    void drawCircuite();
    void drawRobot();
    void movementController();
};

#endif // GLWIDGET_H
