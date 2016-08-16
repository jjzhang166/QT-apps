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
#include <QGraphicsView>
#include <QMessageBox>

#define PIECE_SIZE 50

class PuzzlePiece : public QGraphicsPathItem
{
public:


    enum ConnectorPosition {None, In, Out};

    PuzzlePiece(ConnectorPosition north, ConnectorPosition south,
                ConnectorPosition west, ConnectorPosition east);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPixmap pixmap();
    void setPixmap(const QPixmap& image);

    void setCoordinates(QPoint &cor);
    QPoint coordinates();

    enum Direction {North, South, West, East};

    void link(PuzzlePiece *StaticElement, Direction direction);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event); //checkNeighboor needed

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public slots:

    void findneighbor(PuzzlePiece::Direction direction);

    void checkNeighbours(QList<QPoint> &checked);//findNeighboor needed


private:

    ConnectorPosition con_pos[4];
    qreal m_size;
    QPixmap m_image;
    QPoint m_coordinates;// этот coordinatrs? почему еще один тогда?

    void constructPath(QPainterPath& p);


    PuzzlePiece* m_neighbours[4];
};

#endif // PUZZLEPIECE_H
