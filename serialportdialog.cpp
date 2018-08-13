#include "serialportdialog.h"
#include "ui_serialportdialog.h"
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string_list.h>
#include <QDebug>
#include <QSettings>
#include "my_constants.h"
#include "serial_port.h"
#include <Qt>
#include <QMessageBox>
#include <string.h>
#define MAX_LENGTH (1024)

static str_list_t *find_devices(str_list_t *list)
{
    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir("/sys/class/tty");

    if (dr == nullptr)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return nullptr;
    }

    while ((de = readdir(dr)) != nullptr)
    {
            char check_driver[MAX_LENGTH];
            if (strlen("/sys/class/tty/") + strlen(de->d_name) + strlen("/device/driver") < MAX_LENGTH )
            {
                sprintf(check_driver,"%s%s%s","/sys/class/tty/",de->d_name,"/device/driver");
                if( access( check_driver, F_OK ) != -1 )
                {
                    // file exists
                        list->add(list,de->d_name);
                }
            }                        
    }
    closedir(dr);
    return list;
}
/**SerialPortDialog::SerialPortDialog(QWidget *parent) : QDialog(parent),ui(new Ui::SerialPortDialog)
{
    ui->setupUi(this);
    str_list_t *device_list = create_list();
    if (device_list)
    {
        char *dev;

        find_devices(device_list);
        device_list->sort(device_list);
        while ( (dev=device_list->next(device_list)) )
        {
            ui->portComboBox->addItem(dev);
        }
        device_list->destroy(device_list);
    }
    else
    {
        //error message box
    }
}**/

SerialPortDialog::SerialPortDialog(SerialPort *sp) : QDialog(nullptr,Qt::WindowTitleHint
                                                             | Qt::CustomizeWindowHint),ui(new Ui::SerialPortDialog)
{
    serial = sp;

    ui->setupUi(this);
    //Initialize parity combobox
    ui->comboBox_parity->setEnabled(sp->getParityEnable());
    if (sp->getOddParity())
        ui->comboBox_parity->setCurrentIndex(1);
    else
        ui->comboBox_parity->setCurrentIndex(0);

    //Initialize parity enable
    if (sp->getParityEnable())
    {
        ui->checkBox_enable_parity->setCheckState(Qt::Checked);
    }
    else
        ui->checkBox_enable_parity->setCheckState(Qt::Unchecked);

    //Initialize baud
    QString currentBaud = QString::number(serial->getBaud());
    int b = ui->comboBox_baud->findText(currentBaud);
    if (b > -1)
    {
        ui->comboBox_baud->setCurrentIndex(b);
    }
    //Initialize stop bits
    QString currentStop = QString::number(serial->getStopbits());
    int s = ui->comboBox_stopbits->findText(currentStop);
    if (s > -1)
    {
        ui->comboBox_stopbits->setCurrentIndex(s);
    }

    //Initialize data bits
    QString currentData = QString::number(serial->getDatabits());
    int d = ui->comboBox_databits->findText(currentData);
    if (d >= 0)
    {
        ui->comboBox_databits->setCurrentIndex(d);
    }
    //Initialize device list
    str_list_t *device_list = create_list();
    if (device_list)
    {
        char *dev;

        find_devices(device_list);
        device_list->sort(device_list);
        while ( (dev=device_list->next(device_list)) )
        {
            ui->portComboBox->addItem(dev);
            if (strcmp(dev,serial->getDevice().toLatin1().data())==0)
            {
                ui->portComboBox->setCurrentText(serial->getDevice());//
            }
        }
        device_list->destroy(device_list);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Could not create device list");
        msgBox.exec();
    }
}

SerialPortDialog::~SerialPortDialog()
{
    delete ui;
}
void SerialPortDialog::on_pushButton_ok_clicked()
{
    //printf("Device selected=%s\n",ui->portComboBox->currentText().toLatin1().data());
    if ( serial->setBaud(ui->comboBox_baud->currentText().toUInt()) )
    {
        serial->setParityEnable(ui->checkBox_enable_parity->checkState());
        serial->setOddParity(ui->comboBox_parity->currentText());
        serial->setDevice(ui->portComboBox->currentText());
        serial->setDatabits(ui->comboBox_databits->currentText().toUInt());
        serial->setStopbits(ui->comboBox_stopbits->currentText().toUInt());

        if (! serial->open())
        {
            QMessageBox msgBox;
            msgBox.setText("Could not open port");
            msgBox.exec();
        }
    }
    else
    {

    }
    close();
}

void SerialPortDialog::on_pushButton_cancel_clicked()
{
    this->close();
}

void SerialPortDialog::on_checkBox_enable_parity_toggled(bool checked)
{
    ui->comboBox_parity->setEnabled(checked);
}
