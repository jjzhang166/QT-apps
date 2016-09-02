#include "mainwindow.h"
#include <QApplication>
#include"item.h"
#include"musicmodel.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


   /* MusicModel model;
    w.treeView()->setModel(&model);*/
    w.show();
    return a.exec();
}



















/*#include "mainwindow.h"
#include <QApplication>
#include "item.h"
#include "musicmodel_v3.h"

#include <QMessageLogger>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //Item *item1;
    //Item *item2;
    //Item *itemp;
    //item1->setParent(itemp);
    //item2->setParent(item1);
    //delete itemp;
  /*  item1.setParent(&itemp);**/
    //qDebug() << "item1 parent:" << itemp->takeChild(0);
   /* item2.setParent(&item1);
    item2.parent();*//*



    MusicModel model;
    w.treeView()->setModel(&model);
    w.show();



    return a.exec();*/

