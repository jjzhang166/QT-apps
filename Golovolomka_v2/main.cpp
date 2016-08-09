#include <QApplication>
#include "configurationdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigurationDialog dlg;
    dlg.show();

    return a.exec();
}
