#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPainter>
#include <QMessageBox>
#include <QGraphicsView>

#include <QObject>

#define PIECE_SIZE 100

class PuzzlePiece : public QGraphicsPathItem
{
public:
    PuzzlePiece();
};

#endif // PUZZLEPIECE_H
