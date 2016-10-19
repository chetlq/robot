#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "robotcontrol.h"
#include "kinect.h"
#include <QDebug>
#include "angles.h"


int recalcRightElbow(float angle)
{
    int result;
    result = angle * (-0.9222) + 293;
    if(result > 215)
    {
        result = 215;
    }
    if(result < 50)
    {
        result = 50;
    }
    return result;
}




/*правое плечо относительно вертикальной нормали
 * min 210
 * max 50
 * 50 = 180*k + b
 * 210 = 0*k + b
 * b = 210
 * k =  -0.8889
 * */


int recalcRightShoulderVer(float angle)
{
    int result;
    result = angle * (-0.8889) + 210;
    if(result > 210)
    {
        result = 210;
    }
    if(result < 50)
    {
        result = 50;
    }
    return result;
}




/*правое плечо относительно горизонтальной нормали 0-180
 * min 0
 * max 163
 * 163 = 0*k + b
 * 0 = 180*k + b
 * b = 163
 * k =  -0.9056
 * */

int recalcRightShoulderUnderElbow(float angle)
{
    int result;
    result = angle * (-0.9056) + 163;
    if(result > 163)
    {
        result = 163;
    }
    if(result < 1)
    {
        result = 1;
    }
    return result;
}

//165 - вперед на 90
//0 - назад

// max 80m = 180 d вперед на 90
// min 250m = 0 d назад
/*
 *80 = 180k + b
 * 250 = 0k + b
 * b = 250
 * 180k = -250+80=-170
 * k=-170/180=-0.9444
 * */
int recalcRightShoulderElbow(float angle)
{
    int result;
    result = angle * (-0.9444) + 250;
    if(result > 250)
    {
        result = 250;
    }
    if(result < 80)
    {
        result = 80;
    }
    return result;
}

//83 - вниз
//0 - назад
// max 250m = 90 d
// min 163m = 0 d
/*
 *163 = 0k + b
 * 250 = 90k + b
 * b = 163
 * k=0.9667
 * */
int recalcRightShoulderOnElbow(float angle)
{
    int result;
    result = angle * (0.9667) + 163;
    if(result > 250)
    {
        result = 250;
    }
    if(result < 163)
    {
        result = 163;
    }
    return result;
}


/*левый локоть
 * min 45
 * max 120
 * 120 = 180*k + b
 * 45 = 90*k + b
 * k=0.8333
 * b=-30
 * */

int recalcLeftElbow(float angle)
{
    int result;
    result = angle * (0.8333) -30;
    if(result > 120)
    {
        result = 120;
    }
    if(result < 45)
    {
        result = 45;
    }
    return result;
}

/*левое плечо относительно перпендикулярной плоскости
 * min 40
 * max 200
 * 200 = 180*k + b
 * 40 = 0*k + b
 * b = 40
 * k =  0.8889
 * */


int recalcLeftShoulderVer(float angle)
{
    int result;
    result = angle * (0.8889) + 40;
    if(result > 200)
    {
        result = 200;
    }
    if(result < 40)
    {
        result = 40;
    }
    return result;
}

/*
 *max 250m = 180 d
 * min 82m = 0d
 *левое плечо относительно паралельной плоскости
 * min 0
 * max 163
 * 250 = 180*k + b
 * 82 = 0*k + b
 * b = 82
 * k =  0.9333
 * */

int recalcLeftShoulderUnderElbow(float angle)
{
    int result;
    result = angle * (0.9333) + 82;
    if(result > 253)
    {
        result = 253;
    }
    if(result < 82)
    {
        result = 82;
    }
    return result;
}

//165 - вперед на 90
//0 - назад

// max 165m = 180 d вперед на 90
// min 0m = 0 d назад
/*
 *165 = 0k + b
 * 0 = 180k + b
 * b = 165
 * k = -0.9167
 * */
int recalcLeftShoulderElbow(float angle)
{
    int result;
    result = angle * (-0.9167) + 165;
    if(result > 165)
    {
        result = 165;
    }
    if(result < 1)
    {
        result = 1;
    }
    return result;
}

//83 - вниз
//0 - назад
// max 0m = 90 d - назад
// min 83m = 0 d вниз
/*
 *83 = 0k + b
 * 0 = 90k + b
 * b = 83
 * k=-0.9222
 * */
int recalcLeftShoulderOnElbow(float angle)
{
    int result;
    result = angle * (-0.9222) + 83;
    if(result > 83)
    {
        result = 83;
    }
    if(result < 1)
    {
        result = 1;
    }
    return result;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    depthImage = QImage(320, 240, QImage::Format_Indexed8);

    kinect = new Kinect;
    robot = new RobotControl;
    angles = new Angles();
    startTimer(70);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete robot;
    delete kinect;
    delete angles;
}

void MainWindow::on_pushButton_clicked()
{
    //robot->sendPosition(recalcRightShoulderHor(ui->posEdit->text().toInt()), 13);
}

void MainWindow::timerEvent(QTimerEvent *)
{
      Man man;
//      static int i=0;
//      static float i1[5];
//      static float res=0;

    kinect->connect(man, depthImage);

    angles->Count(man);

    angles->man.head.x
    robot->sendPosition(112, 0);
   // robot->sendPosition(220, 1);
    robot->sendPosition(127, 2);
    robot->sendPosition(43, 3);
    robot->sendPosition(100, 4);
    robot->sendPosition(133, 5);
    robot->sendPosition(34, 6);
    robot->sendPosition(102, 7);
    robot->sendPosition(190, 8);
    robot->sendPosition(153, 9);
    ui->depthLabel->setPixmap(QPixmap::fromImage(depthImage));

   if(man.isValid)
    {
//       i1[i] = angles->ang.rightShoulderPlanePerpendicularAngle;
// //qDebug()<< i;
//       res= (i1[0]+i1[1]+i1[2]+i1[3]+i1[4])/5;
//       if (i==5)
//       {
//          i=0;
//       }
//       else
//       {
//         i++;
//       }
//qDebug()<<res;
//      //qDebug() << "x = "<< man.head.x <<"\ny = " << man.head.y <<"\nz = " << man.head.z << "\n";

      robot->sendPosition( recalcRightElbow(angles->ang.rightElbowAngle), 15);
         robot->sendPosition(recalcRightShoulderVer(angles->ang.rightShoulderPlanePerpendicularAngle;), 14);
       if (angles->rightFlag == 1)
           robot->sendPosition(recalcRightShoulderElbow(angles->ang.rightShoulderPlaneParallelAngle-10), 13);
       else
       if(angles->rightFlag == 2)
           robot->sendPosition(recalcRightShoulderOnElbow(angles->ang.rightShoulderPlaneParallelAngle), 13);
       else
           robot->sendPosition(recalcRightShoulderUnderElbow(angles->ang.rightShoulderPlaneParallelAngle), 13);


       robot->sendPosition( recalcLeftElbow(angles->ang.leftElbowAngle), 12);
       robot->sendPosition(recalcLeftShoulderVer(angles->ang.leftShoulderPlanePerpendicularAngle), 11);
       if (angles->leftFlag == 1)
            robot->sendPosition(recalcLeftShoulderElbow(angles->ang.leftShoulderPlaneParallelAngle), 10);
        else
        if(angles->leftFlag == 2)
            robot->sendPosition(recalcLeftShoulderOnElbow(angles->ang.leftShoulderPlaneParallelAngle), 10);
        else
            robot->sendPosition(recalcLeftShoulderUnderElbow(angles->ang.leftShoulderPlaneParallelAngle), 10);
           qDebug() << "yes";
    }
    //else
    {
        //qDebug() << "not";
    }
}



