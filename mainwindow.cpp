#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_serial_port_setup.h"
#include "serialportdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSerial_port_triggered()
{
    ui->label->setText("Hello");

    /**QDialog *d = new QDialog(0,0);
    Ui_Dialog ui;
    ui.setupUi(d);
    d->exec();**/

    SerialPortDialog *d = new SerialPortDialog();
    d->exec();

}
