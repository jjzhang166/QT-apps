#include <QApplication>
#include "configurationdialog.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "puzzlepiece.h"
#include <QRect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigurationDialog dlg;
    //dlg.show();

    QGraphicsView gv;
    QGraphicsScene gs;

    PuzzlePiece item(PuzzlePiece::None, PuzzlePiece::Out, PuzzlePiece::In, PuzzlePiece::Out);

    int cellSize = PIECE_SIZE;
    QRect rect = item.boundingRect().toRect();
    rect.translate(0.5 * cellSize + cellSize, 0.5 * cellSize + 5 * cellSize);


    gs.addItem(&item);

    gv.setScene(&gs);
    gv.setWindowTitle("Item");
    gv.show();



    return a.exec();
}
