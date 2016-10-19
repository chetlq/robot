#include "kinect.h"
// STL Header
#include <iostream>

// 1. include NiTE Header
#include <NiTE.h>

#include <QImage>
#include <QColor>
#include <QRgb>

#include <QDebug>

// using namespace
using namespace std;

Kinect::Kinect()
{
    nite::NiTE::initialize();
    mUserTracker.create();
}

Kinect::~Kinect()
{
    nite::NiTE::shutdown();
}



void Kinect::connect(Man &man, QImage &image)
{

    Scelet scelet;

    static uchar frameMas[320 * 240];
    man.isValid = false;
    nite::UserTrackerFrameRef mUserFrame;
    mUserTracker.readFrame( &mUserFrame );
    openni::VideoFrameRef &frame = mUserFrame.getDepthFrame(); //ссылается на данные кот возвр mUserFrame.getDepthFrame(); - массив черно-белый

    image = QImage((const uchar*)frameMas, 320, 240, QImage::Format_Indexed8);
    const nite::Array<nite::UserData>& aUsers = mUserFrame.getUsers();

    if (aUsers.getSize()>0)
    {
        const nite::UserData& rUser = aUsers[0];
        if( rUser.isNew() )
        {
            cout << "New User [" << rUser.getId() << "] found." << endl << flush;
            // 5a. start tracking skeleton
            mUserTracker.startSkeletonTracking( rUser.getId() );
        }
        if( rUser.isLost() )
        {
            cout << "User [" << rUser.getId()  << "] lost." << endl << flush;
        }

        // 5b. get skeleton
        const nite::Skeleton& rSkeleton = rUser.getSkeleton();
        if( rSkeleton.getState() == nite::SKELETON_TRACKED )
        {
            // if is tracked, get joints
            const nite::SkeletonJoint& rHead
                    = rSkeleton.getJoint( nite::JOINT_HEAD );
            const nite::Point3f& rPos = rHead.getPosition();
            man.head.x=rPos.x;
            man.head.y=rPos.y;
            man.head.z=rPos.z;


            mUserTracker.convertJointCoordinatesToDepth(rPos.x, rPos.y, rPos.z,  &scelet.head.tempX,
                                                        &scelet.head.tempY);


            const nite::SkeletonJoint &rRHand =
                    rSkeleton.getJoint(nite::JOINT_RIGHT_HAND);
            const nite::Point3f &rHandPos = rRHand.getPosition();
            man.rightHand.x = rHandPos.x;
            man.rightHand.y  = rHandPos.y;
            man.rightHand.z  = rHandPos.z;

            mUserTracker.convertJointCoordinatesToDepth(rHandPos.x, rHandPos.y, rHandPos.z,
                                                        &scelet.rightHand.tempX, &scelet.rightHand.tempY);

            const nite::SkeletonJoint &rLHand =
                    rSkeleton.getJoint(nite::JOINT_LEFT_HAND);
            const nite::Point3f &lHandPos = rLHand.getPosition();
            man.leftHand.x = lHandPos.x;
            man.leftHand.y = lHandPos.y;
            man.leftHand.z = lHandPos.z;

            mUserTracker.convertJointCoordinatesToDepth(lHandPos.x, lHandPos.y, lHandPos.z,
                                                        &scelet.leftHand.tempX, &scelet.leftHand.tempY);


            const nite::SkeletonJoint &rRShoulder =
                    rSkeleton.getJoint(nite::JOINT_RIGHT_SHOULDER);
            const nite::Point3f &rShoulderPos = rRShoulder.getPosition();
            man.rightShoulder.x = rShoulderPos.x;
            man.rightShoulder.y = rShoulderPos.y;
            man.rightShoulder.z = rShoulderPos.z;

            mUserTracker.convertJointCoordinatesToDepth(rShoulderPos.x, rShoulderPos.y, rShoulderPos.z,
                                                        &scelet.rightShoulder.tempX, &scelet.rightShoulder.tempY);


            const nite::SkeletonJoint &rLShoulder =
                    rSkeleton.getJoint(nite::JOINT_LEFT_SHOULDER);
            const nite::Point3f &lShoulderPos = rLShoulder.getPosition();
            man.leftShoulder.x = lShoulderPos.x;
            man.leftShoulder.y = lShoulderPos.y;
            man.leftShoulder.z = lShoulderPos.z;

            mUserTracker.convertJointCoordinatesToDepth(lShoulderPos.x, lShoulderPos.y, lShoulderPos.z,                                                     &scelet.leftShoulder.tempX, &scelet.leftShoulder.tempY);

            const nite::SkeletonJoint &rRElbow =
                    rSkeleton.getJoint(nite::JOINT_RIGHT_ELBOW);
            const nite::Point3f &rElbowPos = rRElbow.getPosition();
            man.rightElbow.x = rElbowPos.x;
            man.rightElbow.y = rElbowPos.y;
            man.rightElbow.z = rElbowPos.z;

            mUserTracker.convertJointCoordinatesToDepth(rElbowPos.x, rElbowPos.y, rElbowPos.z,
                                                        &scelet.rightElbow.tempX, &scelet.rightElbow.tempY);


            const nite::SkeletonJoint &rLElbow =
                    rSkeleton.getJoint(nite::JOINT_LEFT_ELBOW);
            const nite::Point3f &lElbowPos = rLElbow.getPosition();
            man.leftElbow.x = lElbowPos.x;
            man.leftElbow.y = lElbowPos.y;
            man.leftElbow.z = lElbowPos.z;

            mUserTracker.convertJointCoordinatesToDepth(lElbowPos.x, lElbowPos.y, lElbowPos.z,
                                                        &scelet.leftElbow.tempX, &scelet.leftElbow.tempY);
            man.isValid = true;

            for(int i = 0; i < frame.getWidth(); ++i)
            {
                for(int j = 0; j < frame.getHeight(); ++j)
               {
                    uint16_t pixelValue = *((uint16_t*)frame.getData() + i + j * 320);//getData() - адр первого эл массива
                    // преведение типов указ
                    if (
                                        (i==(int)scelet.head.tempX && j==(int)scelet.head.tempY) ||
                                        (i==(int)scelet.leftElbow.tempX && j==(int)scelet.leftElbow.tempY) ||
                                        (i==(int)scelet.leftHand.tempX && j==(int)scelet.leftHand.tempY) ||
                                        (i==(int)scelet.leftShoulder.tempX && j==(int)scelet.leftShoulder.tempY) ||
                                        (i==(int)scelet.rightElbow.tempX && j==(int)scelet.rightElbow.tempY) ||
                                        (i==(int)scelet.rightHand.tempX && j==(int)scelet.rightHand.tempY) ||
                                        (i==(int)scelet.rightShoulder.tempX && j==(int)scelet.rightShoulder.tempY)
                                     )
                                   {frameMas[i + j * 320] = (255);}
                                else

                    {frameMas[i + j * 320] = (pixelValue >> 6);}//сдвигаем на 6 //берем 8 но не самых старших бит
                    //qDebug() << pixelValue;
                }
            }
        }    }}
