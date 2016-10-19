#ifndef KINECT_H
#define KINECT_H

#include <NiTE.h>
#include <QImage>


struct Point3D
{
    float x;
    float y;
    float z;
};



struct Man
{
    Point3D head;
    Point3D rightHand;
    Point3D leftHand;
    Point3D rightElbow;
    Point3D leftElbow;
    Point3D rightShoulder;
    Point3D leftShoulder;
    bool isValid;
};

struct Pixel
{
float tempX, tempY;
};

struct Scelet
{
    Pixel head;
    Pixel rightHand;
    Pixel leftHand;
    Pixel rightElbow;
    Pixel leftElbow;
    Pixel rightShoulder;
    Pixel leftShoulder;
};

class Kinect
{
public:
    Kinect();
    ~Kinect();
    void connect(Man &man, QImage &image);


private:
    nite::UserTracker mUserTracker;

};

#endif // KINECT_H
