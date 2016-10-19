#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class RobotControl;
class Kinect;
class Angles;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent*);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    RobotControl *robot;
    Kinect *kinect;
    Angles *angles;
    QImage depthImage;
};

#endif // MAINWINDOW_H
