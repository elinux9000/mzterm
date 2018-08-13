#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H
#include <QString>
#include <QSettings>

class SerialPort
{
public:
    SerialPort();

    void setDevice(QString);
    QString getDevice();

    bool setBaud(unsigned int);
    unsigned getBaud();

    void setOddParity(QString);
    bool getOddParity();

    void setParityEnable(bool);
    bool getParityEnable();

    void setDatabits(unsigned);
    unsigned getDatabits(void);

    void setStopbits(unsigned);
    unsigned getStopbits(void);

    bool open(void);

    //int debug;
private:
    QSettings setting;
    QString device;
    unsigned int baud_nominal;
    unsigned int baud_mask;
    bool oddParity;
    bool parity_enable;
    unsigned stop_bits;
    unsigned data_bits;
    unsigned data_bits_mask;
    int fd; /* File descriptor for the port */

};

#endif // SERIAL_PORT_H
