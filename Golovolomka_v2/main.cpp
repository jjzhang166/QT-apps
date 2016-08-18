#include <QApplication>
#include "configurationdialog.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "puzzlepiece.h"
#include <QRect>
#include "logic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigurationDialog dlg;
    dlg.exec();
    //dlg.show();

    QGraphicsView gv;
    QGraphicsScene gs;

    PuzzlePiece item(PuzzlePiece::None, PuzzlePiece::Out, PuzzlePiece::In, PuzzlePiece::Out);

    int cellSize = PIECE_SIZE;
    QRect rect = item.boundingRect().toRect();
    rect.translate(0.5 * cellSize + cellSize, 0.5 * cellSize + 5 * cellSize);

    Logic logic;
    QString P= ":/Image/Neyronnyie-seti.jpg";
    logic.setup(dlg.puzzleSize(), dlg.imageFilePath());


    //gs.addItem(&item);

    gv.setScene(&logic);
    gv.setWindowTitle("pazzles scheme");
    gv.show();

    a.exec();
    /*  int exitFlag = 0;
    while(!exitFlag)
    {
        QApplication a(argc, argv);
        ConfigurationDialog dlg;
        dlg.exec();
        //dlg.show();

        QGraphicsView gv;
        QGraphicsScene gs;

        PuzzlePiece item(PuzzlePiece::None, PuzzlePiece::Out, PuzzlePiece::In, PuzzlePiece::Out);

        int cellSize = PIECE_SIZE;
        QRect rect = item.boundingRect().toRect();
        rect.translate(0.5 * cellSize + cellSize, 0.5 * cellSize + 5 * cellSize);

        Logic logic;
        QString P= ":/Image/Neyronnyie-seti.jpg";
        logic.setup(dlg.puzzleSize(), dlg.imageFilePath());


        //gs.addItem(&item);

        gv.setScene(&logic);
        gv.setWindowTitle("pazzles scheme");
        gv.show();

        a.exec();
        exitFlag = item.exitFlag;
    }

*/




}
