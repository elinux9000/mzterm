#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serial_port.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(SerialPort*sp);
    ~MainWindow();

private slots:
    void on_actionSerial_port_triggered();

    void on_actionRun_triggered();

private:
    Ui::MainWindow *ui;
    SerialPort*serial;
};

#endif // MAINWINDOW_H
