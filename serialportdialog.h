#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include <QDialog>
#include "serial_port.h"
namespace Ui {
class SerialPortDialog;
}

class SerialPortDialog : public QDialog
{
    Q_OBJECT

public:
    //explicit SerialPortDialog(QWidget *parent = nullptr);
    explicit SerialPortDialog(SerialPort *sp);
    ~SerialPortDialog();

private slots:    
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

    void on_checkBox_enable_parity_toggled(bool checked);

private:
    Ui::SerialPortDialog *ui;
    SerialPort *serial;

};

#endif // SERIALPORTDIALOG_H
