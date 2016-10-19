#include "robotcontrol.h"
#include "comport.h"
#include <QDebug>

// 11 servo: 50 - 190
//

RobotControl::RobotControl()
{

    port = new ComPort;
    unsigned char h[] = {0xFF , 0xFF , 0xAA , 0x55 , 0xAA , 0x55 , 0x37 , 0xBA,
                        0x10, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01};


    qDebug() << port->openPort(3);

    for(int i=0;i<sizeof(h);i++)
    {
        *port << (h[i]);
    }
    for(int i=0;i<sizeof(h);i++)
    {
        int s;
        port->readByte(s);
    }


}

RobotControl::~RobotControl()
{
    delete port;
}

void RobotControl::sendPosition(unsigned char pos, unsigned char id)
{
    unsigned char byte1 = ((1 << 5) | id); // 2B for 11
    unsigned char checkSum =  (byte1 ^ pos) & 0x7F ;
    int status;

    *port << 0xFF << byte1 << pos << checkSum;

    port->readByte(status) ;
}
