#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    SerialPortDialog *d = new SerialPortDialog();
    d->exec();
    delete(d);

}
