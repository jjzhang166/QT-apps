#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H
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

#define PIECE_SIZE 100

class PuzzlePiece : public QGraphicsPathItem
{
public:


    enum ConnectorPosition {None, In, Out};
    enum Direction {North, South, West, East};

    PuzzlePiece(ConnectorPosition north, ConnectorPosition south,
                ConnectorPosition west, ConnectorPosition east);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



private:

    ConnectorPosition con_pos[4];
    qreal m_size;
    QPixmap m_image;
    QPoint m_coordinates;
    PuzzlePiece* m_neighbours[4];

    void constructPath(QPainterPath& p);
};

#endif // PUZZLEPIECE_H
