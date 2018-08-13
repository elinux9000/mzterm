#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include "serial_port.h"
#include "QSettings"
#include "my_constants.h"
#include <QDebug>
#include <termios.h>
#include <QMessageBox>

SerialPort::SerialPort()
{
    device = setting.value(DEVICE_KEY).toString();

    baud_nominal = setting.value(BAUD_KEY).toUInt();
    baud_mask = setting.value(BAUD_MASK_KEY).toUInt();

    parity_enable = setting.value(PARITY_ENABLE_KEY).toBool();
    oddParity = setting.value(PARITY_KEY).toBool();

    data_bits = setting.value(DATA_BITS_KEY).toUInt();
    data_bits_mask = setting.value(DATA_BITS_MASK_KEY).toUInt();

    stop_bits = setting.value(STOP_BITS_KEY).toUInt();

    //qDebug()<<"device="<<device<<" baud="<<baud_nominal<<" parity="<<oddParity<<" parity_enable="<<parity_enable;
}
QString SerialPort::getDevice(void)
{
    return device;
}
void SerialPort::setDevice(QString d)
{
    device = d;
    setting.setValue(DEVICE_KEY,device);
}
unsigned SerialPort::getDatabits(void)
{
    return data_bits;
}
void SerialPort::setDatabits(unsigned d)
{
    switch (d)
    {
        case 5: data_bits = 5;
                data_bits_mask = CS5;
                setting.setValue(DATA_BITS_KEY,data_bits);
                setting.setValue(DATA_BITS_MASK_KEY,data_bits_mask);
            break;
        case 6: data_bits = 6;
                data_bits_mask = CS6;
                setting.setValue(DATA_BITS_KEY,data_bits);
                setting.setValue(DATA_BITS_MASK_KEY,data_bits_mask);
            break;
        case 7: data_bits = 7;
                data_bits_mask = CS7;
                setting.setValue(DATA_BITS_KEY,data_bits);
                setting.setValue(DATA_BITS_MASK_KEY,data_bits_mask);
            break;
        case 8: data_bits = 8;
                data_bits_mask = CS8;
                setting.setValue(DATA_BITS_KEY,data_bits);
                setting.setValue(DATA_BITS_MASK_KEY,data_bits_mask);
            break;
        default:
            QMessageBox msgBox;
            msgBox.setText("Invalid data size");
            msgBox.exec();
            break;
    }
}
unsigned SerialPort::getStopbits(void)
{
    return stop_bits;
}
void SerialPort::setStopbits(unsigned s)
{
    switch (s)
    {
        case 1: stop_bits = 1;
            setting.setValue(STOP_BITS_KEY,stop_bits);
            break;
        case 2: stop_bits = 2;
            setting.setValue(STOP_BITS_KEY,stop_bits);
            break;
        default:
            QMessageBox msgBox;
            msgBox.setText("Invalid stop bits");
            msgBox.exec();
            break;
    }
}
bool SerialPort::open(void)
{
    QString filename("/dev/");
    filename += device;
    fd = ::open(filename.toLatin1().data(), O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
    if (fd == -1)
    {
        perror("open_port: Unable to open port");
        qDebug()<<"Unable to open "<<filename.toLatin1().data();
        return false;
    }
    else
    {
        struct termios options;
        tcgetattr(fd, &options);
        //set baud
        cfsetispeed(&options, baud_mask);
        cfsetospeed(&options, baud_mask);
        options.c_cflag |= (CLOCAL | CREAD); 
        
        //
        if (parity_enable)
        {
            options.c_cflag |= PARENB;
            if (oddParity)
            {
                options.c_cflag |= PARODD;
            }
            else
            {
                options.c_cflag &= static_cast<unsigned int>(~PARODD);
            }
        }
        else
        {
            options.c_cflag &= static_cast<unsigned int>(~PARENB);
        }

        //set data bits
        options.c_cflag &= static_cast<unsigned int>(~CS5);
        options.c_cflag &= static_cast<unsigned int>(~CS6);
        options.c_cflag &= static_cast<unsigned int>(~CS7);
        options.c_cflag &= static_cast<unsigned int>(~CS8);
        options.c_cflag |= data_bits_mask;

        //set stop bits
        if (stop_bits == 2)
        {
            options.c_cflag |= CSTOPB;
        }
        else
        {
            options.c_cflag &= static_cast<unsigned int>(~CSTOPB);
        }
        tcsetattr(fd, TCSANOW, &options);
        return true;
    }
    return false;
}
bool SerialPort::setBaud(unsigned int b)
{
    switch (b)
    {
        case 115200: baud_mask =  0010002;
            baud_nominal = b;
            setting.setValue(BAUD_KEY,baud_nominal);
            setting.setValue(BAUD_MASK_KEY,baud_mask);
            return true;
            break;
        case 230400: baud_mask = 0010003;
            baud_nominal = b;
            setting.setValue(BAUD_KEY,baud_nominal);
            setting.setValue(BAUD_MASK_KEY,baud_mask);
            return true;
            break;
        default:
            QMessageBox msgBox;
            msgBox.setText("Invalid baud rate");
            msgBox.exec();
            baud_mask =  0010002;
            return false;
            break;
    }

}
void SerialPort::setParityEnable(bool b)
{
    parity_enable = b;
    setting.setValue(PARITY_ENABLE_KEY,parity_enable);
}
void SerialPort::setOddParity(QString p)
{
    if (p=="Odd")
    {
        oddParity = true;
        setting.setValue(PARITY_KEY,oddParity);
    }
    else if (p=="Even")
    {
        oddParity = false;
        setting.setValue(PARITY_KEY,oddParity);
    }    
}
bool SerialPort::getParityEnable(void)
{
    return parity_enable;
}
bool SerialPort::getOddParity(void)
{
    return oddParity;
}
unsigned SerialPort::getBaud(void)
{
    return baud_nominal;
}


