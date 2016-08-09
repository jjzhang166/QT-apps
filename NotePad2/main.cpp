#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.setApplicationName("Text editor");
    a.setApplicationVersion("0.1");
    a.setOrganizationName("MephiSoft");
    a.setOrganizationDomain("mephi.ru");
    a.setWindowIcon(QIcon(":/images/icon.png"));//???????

    return a.exec();
}
