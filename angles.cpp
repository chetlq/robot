#include "angles.h"
#include <QDebug>
#include "comport.h"
#define PI            3.14159265358979323846





Angles::Angles()
{

}

Angles::~Angles()
{

}


void Angles::Count(Man &man)
{


    Point3D rightPlane;
    Point3D leftPlane;


    Point3D rightHorNormal;
    Point3D rightVerNormal;

    Point3D leftHorNormal;
    Point3D leftVerNormal;



    int dg;



        rightparal = Angle(ang.rightShoulderElbowVector,ang.rightShoulderPlaneParallel);
        rightperp = Angle(ang.rightShoulderElbowVector,ang.rightShoulderPlanePerpendicular);

        leftparal = Angle(ang.leftShoulderElbowVector,ang.leftShoulderPlaneParallel);
        leftperp = Angle(ang.leftShoulderElbowVector,ang.leftShoulderPlanePerpendicular);

    {//......................углы правого плеча
    ang.rightHandElbowVector.x = (man.rightHand.x - man.rightElbow.x);
    ang.rightHandElbowVector.y = (man.rightHand.y - man.rightElbow.y);
    ang.rightHandElbowVector.z = (man.rightHand.z - man.rightElbow.z);
    ang.rightShoulderElbowVector.x = (man.rightShoulder.x  - man.rightElbow.x);
    ang.rightShoulderElbowVector.y = (man.rightShoulder.y  - man.rightElbow.y);
    ang.rightShoulderElbowVector.z = (man.rightShoulder.z  - man.rightElbow.z);

    ang.rightElbowAngle = Angle2(ang.rightHandElbowVector, ang.rightShoulderElbowVector);

    Plane(man.rightShoulder.x, man.rightShoulder.y, man.rightShoulder.z,
          man.leftShoulder.x, man.leftShoulder.y, man.leftShoulder.z,
          man.head.x, man.head.y,man.head.z,
          &ang.rightShoulderPlaneParallel.x, &ang.rightShoulderPlaneParallel.y, &ang.rightShoulderPlaneParallel.z);

    ang.rightShoulderElbowVector.x = (-man.rightShoulder.x  + man.rightElbow.x);
    ang.rightShoulderElbowVector.y = (-man.rightShoulder.y  + man.rightElbow.y);
    ang.rightShoulderElbowVector.z = (-man.rightShoulder.z  + man.rightElbow.z);



        rightHorNormal.x = (0 - man.rightShoulder.z/ ang.rightShoulderPlaneParallel.z)*ang.rightShoulderPlaneParallel.x + man.rightShoulder.x;
        rightHorNormal.y = (0 - man.rightShoulder.z / ang.rightShoulderPlaneParallel.z)*ang.rightShoulderPlaneParallel.y - man.rightShoulder.y;
        rightHorNormal.z = 0;


        rightVerNormal.x = man.rightShoulder.x;
        rightVerNormal.y = -1500;
        rightVerNormal.z = man.rightShoulder.z;


        Plane(rightHorNormal.x ,rightHorNormal.y ,rightHorNormal.z ,
              rightVerNormal.x,rightVerNormal.y,rightVerNormal.z,
              man.rightShoulder.x, man.rightShoulder.y, man.rightShoulder.z,
              &ang.rightShoulderPlanePerpendicular.x, &ang.rightShoulderPlanePerpendicular.y, &ang.rightShoulderPlanePerpendicular.z);

        rightVerNormal.x = 0;
        rightVerNormal.y = -1500- man.rightShoulder.y;
        rightVerNormal.z = 0;

        if ((rightparal<20)&&(rightperp>50)&&(ang.rightElbowAngle<140))
        {
            rightFlag = 1;
            Plane(man.rightShoulder.x, man.rightShoulder.y, man.rightShoulder.z,
                  man.rightElbow.x, man.rightElbow.y, man.rightElbow.z,
                  man.rightHand.x, man.rightHand.y, man.rightHand.z,
                  &rightPlane.x, &rightPlane.y, &rightPlane.z);
                ang.rightShoulderPlaneParallelAngle = Angle2(ang.rightShoulderPlaneParallel,rightPlane);
            ang.rightShoulderPlanePerpendicularAngle = Angle2(ang.rightShoulderElbowVector,rightVerNormal);


        }
        else
        {
            rightFlag = 0;

            if (man.rightElbow.y>man.rightShoulder.y)
            {
                dg = 20;
                if (rightparal>rightperp)
                {
                    rightFlag =0;
                    if ((rightperp>dg)||(rightparal>dg))
                    {
                        rightflag2 = 1;
                    }

                    ang.rightShoulderPlaneParallelAngle = Angle2(ang.rightShoulderElbowVector,rightVerNormal);
                    ang.rightShoulderPlanePerpendicularAngle = Angle(ang.rightShoulderElbowVector,ang.rightShoulderPlanePerpendicular);
                }
                if (rightperp>rightparal)
                {
                    rightFlag = 2;
                    if((rightperp>dg)||(rightparal>dg))
                    {
                        rightflag2 = 0;
                    }
                    ang.rightShoulderPlanePerpendicularAngle = Angle2(ang.rightShoulderElbowVector,rightVerNormal);
                    ang.rightShoulderPlaneParallelAngle =Angle(ang.rightShoulderElbowVector,ang.rightShoulderPlaneParallel);
                }

                if ((rightperp<=dg)&&(rightparal<=dg))
                {


                    if (rightflag2==1)
                    {
                        rightFlag = 0;
                        ang.rightShoulderPlaneParallelAngle = Angle2(ang.rightShoulderElbowVector,rightVerNormal);
                        ang.rightShoulderPlanePerpendicularAngle = Angle(ang.rightShoulderElbowVector,ang.rightShoulderPlanePerpendicular);
                    }
                    if (rightflag2==0)
                    {
                        rightFlag = 2;
                        ang.rightShoulderPlanePerpendicularAngle = Angle2(ang.rightShoulderElbowVector,rightVerNormal);
                        ang.rightShoulderPlaneParallelAngle =Angle(ang.rightShoulderElbowVector,ang.rightShoulderPlaneParallel);

                    }
                }

            }

            else
            {
                rightFlag = 0;
                ang.rightShoulderPlaneParallelAngle =Angle(ang.rightShoulderElbowVector,ang.rightShoulderPlaneParallel);
                ang.rightShoulderPlanePerpendicularAngle= Angle(ang.rightShoulderElbowVector,ang.rightShoulderPlanePerpendicular);
            }

            if (ang.rightShoulderPlanePerpendicularAngle<0)ang.rightShoulderPlanePerpendicularAngle=0;
            if (ang.rightShoulderPlaneParallelAngle<0)ang.rightShoulderPlaneParallelAngle=0;
        }
    }

        {//......................углы левого плеча
        ang.leftHandElbowVector.x = (man.leftHand.x - man.leftElbow.x);
        ang.leftHandElbowVector.y = (man.leftHand.y - man.leftElbow.y);
        ang.leftHandElbowVector.z = (man.leftHand.z - man.leftElbow.z);
        ang.leftShoulderElbowVector.x = (man.leftShoulder.x  - man.leftElbow.x);
        ang.leftShoulderElbowVector.y = (man.leftShoulder.y  - man.leftElbow.y);
        ang.leftShoulderElbowVector.z = (man.leftShoulder.z  - man.leftElbow.z);

        ang.leftElbowAngle = Angle2(ang.leftHandElbowVector, ang.leftShoulderElbowVector);

        Plane(man.rightShoulder.x, man.rightShoulder.y, man.rightShoulder.z,
              man.leftShoulder.x, man.leftShoulder.y, man.leftShoulder.z,
              man.head.x, man.head.y,man.head.z,
              &ang.leftShoulderPlaneParallel.x, &ang.leftShoulderPlaneParallel.y, &ang.leftShoulderPlaneParallel.z);

        ang.leftShoulderElbowVector.x = (-man.leftShoulder.x  + man.leftElbow.x);
        ang.leftShoulderElbowVector.y = (-man.leftShoulder.y  + man.leftElbow.y);
        ang.leftShoulderElbowVector.z = (-man.leftShoulder.z  + man.leftElbow.z);



            leftHorNormal.x = (0 - man.leftShoulder.z/ ang.leftShoulderPlaneParallel.z)*ang.leftShoulderPlaneParallel.x + man.leftShoulder.x;
            leftHorNormal.y = (0 - man.leftShoulder.z / ang.leftShoulderPlaneParallel.z)*ang.leftShoulderPlaneParallel.y - man.leftShoulder.y;
            leftHorNormal.z = 0;


            leftVerNormal.x = man.leftShoulder.x;
            leftVerNormal.y = -1500;
            leftVerNormal.z = man.leftShoulder.z;


            Plane(leftHorNormal.x ,leftHorNormal.y ,leftHorNormal.z ,
                  leftVerNormal.x,leftVerNormal.y,leftVerNormal.z,
                  man.leftShoulder.x, man.leftShoulder.y, man.leftShoulder.z,
                  &ang.leftShoulderPlanePerpendicular.x, &ang.leftShoulderPlanePerpendicular.y, &ang.leftShoulderPlanePerpendicular.z);

            leftVerNormal.x = 0;
            leftVerNormal.y = -1500- man.leftShoulder.y;
            leftVerNormal.z = 0;

            if ((leftparal<30)&&(leftperp>50)&&(ang.leftElbowAngle<140))
            {
                leftFlag = 1;
                Plane(man.leftShoulder.x, man.leftShoulder.y, man.leftShoulder.z,
                      man.leftElbow.x, man.leftElbow.y, man.leftElbow.z,
                      man.leftHand.x, man.leftHand.y, man.leftHand.z,
                      &leftPlane.x, &leftPlane.y, &leftPlane.z);
                    ang.leftShoulderPlaneParallelAngle = Angle2(ang.leftShoulderPlaneParallel,leftPlane);
                ang.leftShoulderPlanePerpendicularAngle = Angle2(ang.leftShoulderElbowVector,leftVerNormal);
                //qDebug() << "qawabunga";

            }
            else
            {
                //qDebug() << "no";
                //Qdebnug
                leftFlag = 0;

                if (man.leftElbow.y>man.leftShoulder.y)
                {
                    dg = 30;
                    if (leftparal>leftperp)
                    {
                        leftFlag =0;
                        if ((leftperp>dg)||(leftparal>dg))
                        {
                            leftflag2 = 1;
                        }

                        ang.leftShoulderPlaneParallelAngle = Angle2(ang.leftShoulderElbowVector,leftVerNormal);
                        ang.leftShoulderPlanePerpendicularAngle = Angle(ang.leftShoulderElbowVector,ang.leftShoulderPlanePerpendicular);
                    }
                    if (leftperp>leftparal)
                    {
                        leftFlag = 2;
                        if((leftperp>dg)||(leftparal>dg))
                        {
                            leftflag2 = 0;
                        }
                        ang.leftShoulderPlanePerpendicularAngle = Angle2(ang.leftShoulderElbowVector,leftVerNormal);
                        ang.leftShoulderPlaneParallelAngle =Angle(ang.leftShoulderElbowVector,ang.leftShoulderPlaneParallel);
                    }

                    if ((leftperp<=dg)&&(leftparal<=dg))
                    {


                        if (leftflag2==1)
                        {
                            leftFlag = 0;

                            ang.leftShoulderPlaneParallelAngle = Angle2(ang.leftShoulderElbowVector,leftVerNormal);
                            ang.leftShoulderPlanePerpendicularAngle = Angle(ang.leftShoulderElbowVector,ang.leftShoulderPlanePerpendicular);

                        }
                        if (leftflag2==0)
                        {
                            leftFlag = 2;
                            ang.leftShoulderPlanePerpendicularAngle = Angle2(ang.leftShoulderElbowVector,leftVerNormal);
                            ang.leftShoulderPlaneParallelAngle =Angle(ang.leftShoulderElbowVector,ang.leftShoulderPlaneParallel);
                        }
                    }

                }

                else
                {
                    leftFlag = 0;
                    ang.leftShoulderPlaneParallelAngle =Angle(ang.leftShoulderElbowVector,ang.leftShoulderPlaneParallel);
                    ang.leftShoulderPlanePerpendicularAngle= Angle(ang.leftShoulderElbowVector,ang.leftShoulderPlanePerpendicular);

                }

                if (ang.leftShoulderPlanePerpendicularAngle<0)ang.leftShoulderPlanePerpendicularAngle=0;
                if (ang.leftShoulderPlaneParallelAngle<0)ang.leftShoulderPlaneParallelAngle=0;
            }
        }
}

float Angles::Angle(Point3D v1, Point3D v2)//plane straight
{
    return (180/PI)*asin( abs(v1.x*v2.x+v1.y*v2.y+v1.z*v2.z)/( sqrt(pow(v1.x,2) + pow(v1.y,2) + pow(v1.z,2)) * sqrt(pow(v2.x,2) + pow(v2.y,2) + pow(v2.z,2)) ) ) ;

}

void Angles::Plane(float X1, float Y1, float Z1, float X2, float Y2,float Z2, float X3, float Y3, float Z3, float *A, float *B, float *C)
{
    float X21;
    float Y21;
    float Z21;

    float X31;
    float Y31;
    float Z31;


    //float D;

    X21 = X2 - X1;
    Y21 = Y2 - Y1;
    Z21 = Z2 - Z1;

    X31 = X3 - X1;
    Y31 = Y3 - Y1;
    Z31 = Z3 - Z1;

    *A  = (Y21*Z31-Z21*Y31) ;//det1
    *B  = -(X21*Z31-Z21*X31);//det2
    *C  = (X21*Y31-Y21*X31);//det3
    //D = det1* X1 + det2*Y1 + det3*Z1;
}

float Angles::Angle2(Point3D v1, Point3D v2)//vec vec
{
    return (180/PI)*acos( (v1.x*v2.x+v1.y*v2.y+v1.z*v2.z)/( sqrt(pow(v1.x,2) + pow(v1.y,2) + pow(v1.z,2)) * sqrt(pow(v2.x,2) + pow(v2.y,2) + pow(v2.z,2)) ) ) ;

}
