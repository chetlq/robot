#include "comport.h"
#include <QDebug>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

ComPort::ComPort() : portNumber(0),
                     opened(false)
{
    dcb=(DCB*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(DCB));
    dcb->DCBlength = sizeof(DCB);
    BuildCommDCB(TEXT("parity=N data=8 stop=1"), dcb);
    ct.ReadIntervalTimeout = 0;
    ct.ReadTotalTimeoutMultiplier = 0;
    ct.ReadTotalTimeoutConstant = 100;
    ct.WriteTotalTimeoutMultiplier = ct.WriteTotalTimeoutConstant = 0;
    dcb->BaudRate = 115200;
}
ComPort::~ComPort()
{
    closePort();
}

int ComPort::openPort(int number)
{

    if(!opened)
    {
        if(number < 1 || number > 4)
        {
            return WRONG_PORT_NUMBER;
        }

        portNumber = number;
        switch(portNumber)
        {
        case 1: port = CreateFile(TEXT("COM1"), GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                  OPEN_EXISTING, 0, NULL); break;
        case 2: port = CreateFile(TEXT("COM2"), GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                  OPEN_EXISTING, 0, NULL); break;
        case 3: port = CreateFile(TEXT("COM3"), GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                  OPEN_EXISTING, 0, NULL); break;
        case 4: port = CreateFile(TEXT("COM4"), GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                  OPEN_EXISTING, 0, NULL); break;
        }
        if(port == INVALID_HANDLE_VALUE)
        {
            return PORT_OPEN_ERROR;
        }

        SetCommState(port, dcb);
        SetCommTimeouts(port, &ct);
        HeapFree(GetProcessHeap(), 0, dcb);
        PurgeComm(port, PURGE_TXCLEAR | PURGE_RXCLEAR);
        opened = true;

        return PORT_OPEN_OK;
    }
    else
    {
        return PORT_IS_ALREADY_OPENED;
    }
}

void ComPort::closePort()
{
    if(opened)
    {
        CloseHandle(port);
        opened = false;
    }
}
unsigned char ComPort::readByte(int &status)
{
    unsigned char byte;
    if(opened)
    {
        ReadFile(port, &byte, 1, &bc, NULL);
    }
    else
    {
        status = PORT_CLOSED;
        return byte;
    }
    if(!bc)
    {
        status = BYTE_READ_TIMEOUT;
    }
    else
    {
        status = BYTE_READ_OK;
    }

    return byte;
}

void ComPort::sendByte(unsigned char byte)
{

    WriteFile(port, &byte, 1, &bc, NULL);

}

ComPort &ComPort::operator <<(unsigned char number)
{

    WriteFile(port, &number, 1, &bc, NULL);
    return *this;
}
ComPort &ComPort::operator <<(unsigned char *string)
{

    while(*string)
    {
        WriteFile(port, string, 1, &bc, NULL);
        ++string;
    }
    return *this;}
