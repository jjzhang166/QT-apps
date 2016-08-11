#include <QApplication>
#include "configurationdialog.h"
#include <QGraphicsView>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigurationDialog dlg;
    dlg.show();

    QGraphicsView gv;
    QGraphicsScene gs;

    //gv.setScene(&gs);
    //gv.show();



    return a.exec();
}
