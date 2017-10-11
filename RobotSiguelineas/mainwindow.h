#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setTimer(QString totalTime);
    ~MainWindow();

private slots:
    void on_insertParameters_clicked();

    void on_showRobotCheckBox_clicked();

private:
    Ui::MainWindow *ui;
    float photoWidth;
    float photoHigh;
};

#endif // MAINWINDOW_H
