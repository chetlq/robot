#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

class ComPort;

class RobotControl
{
public:
    RobotControl();
    ~RobotControl();
    //void updatePosition(?);
    void sendPosition(unsigned char pos, unsigned char id);

private:
    ComPort *port;
    //void sendPosition(unsigned char pos, unsigned char id);
};

#endif // ROBOTCONTROL_H
