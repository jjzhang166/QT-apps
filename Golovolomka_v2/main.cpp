#include <QApplication>
#include "configurationdialog.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "puzzlepiece.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigurationDialog dlg;
    //dlg.show();

    QGraphicsView gv;
    QGraphicsScene gs;

    PuzzlePiece item(PuzzlePiece::None, PuzzlePiece::Out, PuzzlePiece::In, PuzzlePiece::Out);

    gs.addItem(&item);

    gv.setScene(&gs);
    gv.setWindowTitle("Item");
    gv.show();



    return a.exec();
}
