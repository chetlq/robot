#define COMPORT_H
#include <windows.h>

enum Com
{
    PORT_OPEN_OK = 1,
    PORT_IS_ALREADY_OPENED = -1,
    WRONG_PORT_NUMBER = -2,
    PORT_OPEN_ERROR = -3,
    BYTE_READ_OK = 2,
    BYTE_READ_TIMEOUT = -4,
    PORT_CLOSED = -5
};

class ComPort
{
public:
    ComPort();
    ~ComPort();
    int openPort(int number);
    void closePort();
    bool isOpened() {return opened;}
    void sendByte(unsigned char byte);
    unsigned char readByte(int &status);
    ComPort &operator << (unsigned char number);
    ComPort &operator << (unsigned char *string);

private:
    int portNumber;
    bool opened;
    HANDLE port;
    COMMTIMEOUTS ct;
    DCB *dcb;
    COMMCONFIG *cf;
    DWORD sz;
    DWORD bc;
};
