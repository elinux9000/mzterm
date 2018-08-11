#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialportdialog.h"
#include "string_list.h"

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

void MainWindow::on_actionRun_triggered()
{
    //Run unit tests
    str_list_t *list = create_list();
    if (list)
    {
        for (int i=0;i<10;i++)
            list->add(list,"123");
    }
    list->destroy(list);

}
