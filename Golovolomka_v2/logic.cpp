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
            if (col==ImageSize.width()-1) curr[3]= PuzzlePiece::None;
            if (row==ImageSize.height()-1) curr[1]= PuzzlePiece::None;

            PuzzlePiece *piece = new PuzzlePiece(curr[0], curr[1]/*curr[3]*/, curr[2], /*curr[1]*/curr[3]);


            addItem(piece); // add item to scene
            piece->setFlag(QGraphicsItem::ItemIsMovable);
            piece->setFlag((QGraphicsItem::ItemSendsGeometryChanges));
            piece->setPos(col*100, row*100); // put the piece in place

            storedWest = curr[3]; // store east for next column
            prev[col] = curr[1]; // store south for next row


            QRect rect = piece->boundingRect().toRect(); // (0,0) в центре

            rect.translate(0.5*PIECE_SIZE+col*PIECE_SIZE, 0.5*PIECE_SIZE+row*PIECE_SIZE);
            QPixmap px;
            px.load(FileName);
            QSize scaled_size(PIECE_SIZE*ImageSize.width(), PIECE_SIZE*ImageSize.height());
            px = px.scaled(scaled_size);
            px = px.copy(rect);
            piece->setPixmap(px);

            QPoint PosOnField(col, row);
            piece->setCoordinates(PosOnField);

        }
    }
}
