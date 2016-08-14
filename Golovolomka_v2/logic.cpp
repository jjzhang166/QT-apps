#include "logic.h"


Logic::Logic()
{

}
PuzzlePiece::ConnectorPosition reverse(PuzzlePiece::ConnectorPosition pos)
{
    switch(pos)
    {

    case PuzzlePiece::None: return PuzzlePiece::None;

    case PuzzlePiece::In: return PuzzlePiece::Out;

    case PuzzlePiece::Out: return PuzzlePiece::In;

    }

    return PuzzlePiece::None; // safeguard
}

void Logic::setup(QSize ImageSize, /*QSize PuzzleSize,*/ QString FileName)
{
    QGraphicsScene::clear();

    PuzzlePiece::ConnectorPosition storedWest;
    QVector <PuzzlePiece::ConnectorPosition> prev(ImageSize.width(),PuzzlePiece::None);

    for(int row = 0; row < ImageSize.height(); row++)
    {
        storedWest = PuzzlePiece::None;
        for(int col = 0; col < ImageSize.width(); col++)
        {
            PuzzlePiece::ConnectorPosition curr[4]; // N, E, S, W // N S W E!!!!!
            curr[0] = reverse(prev[col]);
            curr[3] = qrand() % 2 ? PuzzlePiece::In : PuzzlePiece::Out;
            curr[1] = qrand() % 2 ? PuzzlePiece::In : PuzzlePiece::Out;
            curr[2] = reverse(storedWest);
            if (col==ImageSize.width()-1) curr[1]= PuzzlePiece::None;
            if (row==ImageSize.height()-1) curr[2]= PuzzlePiece::None;

            PuzzlePiece *piece = new PuzzlePiece(curr[0], curr[1], curr[2], curr[3]);

            addItem(piece); // add item to scene
            piece->setFlag(QGraphicsItem::ItemIsMovable);
            piece->setPos(col*100, row*100); // put the piece in place

            storedWest = curr[1]; // store east for next column
            prev[col] = curr[2]; // store south for next row


            QRect rect = piece->boundingRect().toRect(); // (0,0) в центре
            const int cellSize = PIECE_SIZE;
            rect.translate(0.5*cellSize+col*cellSize, 0.5*cellSize+row*cellSize);
            QPixmap px;
            px.load(FileName);
            QSize scaled_size(cellSize*ImageSize.width(), cellSize*ImageSize.height());
            px = px.scaled(scaled_size);
            px = px.copy(rect);
            piece->setPixmap(px);




            /*
            QRect rect = piece->boundingRect().toRect();
            const int cellSize = 100;
            rect.translate(0.5*cellSize+col*cellSize, 0.5*cellSize+row*cellSize);

            QPixmap op;
            op.load(p);
            QSize scaled_size(cellSize*sz.width(), cellSize*sz.height());
            op = op.scaled(scaled_size);
            op = op.copy(rect);
            piece->setPixmap(op);

            QPoint pnt(col, row);
            piece->setCoordinates(pnt);

            addItem(piece);
            piece->setFlag(QGraphicsItem::ItemIsMovable);
            piece->setFlag((QGraphicsItem::ItemSendsGeometryChanges));
            piece->setPos(100*(qrand() % 11) + 10*(qrand() % 11), 100*(qrand() % 11) + 10*(qrand() % 11));
            storedWest = curr[1];
            prev[col] = curr[2];*/
        }
    }
}
