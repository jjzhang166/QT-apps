#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPainter>
#include <QMessageBox>
#include <QGraphicsView>
#include <QObject>
#include <QPainterPath>

#define PIECE_SIZE 100

class PuzzlePiece : public QGraphicsPathItem
{
public:


    enum ConnectorPosition {None, In, Out};
    enum Direction {North, South, West, East};
    PuzzlePiece(ConnectorPosition north, ConnectorPosition south,
                ConnectorPosition west, ConnectorPosition east);


private:

    ConnectorPosition con_pos[4];
    qreal m_size;
    QPixmap m_image;
    QPoint m_coordinates;
    PuzzlePiece* m_neighbours[4];

    void constructPath(QPainterPath& p);
};

#endif // PUZZLEPIECE_H
