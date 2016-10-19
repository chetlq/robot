#ifndef ANGLES_H
#define ANGLES_H
#include <math.h>
#include "kinect.h"

struct AngVec
{
    float rightElbowAngle;
    float leftElbowAngle;

    float rightShoulderPlaneParallelAngle;
    float rightShoulderPlanePerpendicularAngle;
    float leftShoulderPlaneParallelAngle;
    float leftShoulderPlanePerpendicularAngle;

    Point3D rightHandElbowVector;
    Point3D rightShoulderElbowVector;
    Point3D leftHandElbowVector;
    Point3D leftShoulderElbowVector;

    Point3D rightShoulderPlanePerpendicular;
    Point3D rightShoulderPlaneParallel;
    Point3D leftShoulderPlanePerpendicular;
    Point3D leftShoulderPlaneParallel;


};

class Angles
{
public:
    Angles();
    ~Angles();
    void Count(Man &man);
    void Plane(float X1, float Y1, float Z1, float X2, float Y2,float Z2, float X3, float Y3, float Z3, float *A, float *B, float *C);
    AngVec ang;
    int rightFlag;
    int leftFlag;



private:
    float Angle(Point3D v1, Point3D v2);
    float Angle2(Point3D v1, Point3D v2);
    float rightparal;
    float leftparal;
    float rightperp;
    float leftperp;

    int rightflag2;
    int leftflag2;

};

#endif // ANGLES_H
