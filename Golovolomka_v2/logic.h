#ifndef LOGIC_H
#define LOGIC_H
#include "logic.h"
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPainter>
#include <QMessageBox>
#include <QGraphicsView>
#include <QObject>
#include <QPainterPath>
#include <QRect>
#include <QFrame>
#include <QApplication>
#include <QPixmap>
#include <QSize>
#include <QPoint>
#include "puzzlepiece.h"
#include <QVector>
#include <QString>

class Logic : public QGraphicsScene
{
public:
    Logic();

    void setup(QSize ImageSize, /*QSize PuzzleSize,*/ QString FileName);
    PuzzlePiece::ConnectorPosition reverse_pos(PuzzlePiece::ConnectorPosition);
};

#endif // LOGIC_H
