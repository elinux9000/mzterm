#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("rafari");        //These are used to store settings
    QCoreApplication::setOrganizationDomain("rafari.com");
    QCoreApplication::setApplicationName("mzterm");

    SerialPort sp;
    MainWindow w(&sp);
    w.show();
    return a.exec();
}
