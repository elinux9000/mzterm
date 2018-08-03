#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include <QDialog>

namespace Ui {
class SerialPortDialog;
}

class SerialPortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialPortDialog(QWidget *parent = nullptr);
    ~SerialPortDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SerialPortDialog *ui;
};

#endif // SERIALPORTDIALOG_H
