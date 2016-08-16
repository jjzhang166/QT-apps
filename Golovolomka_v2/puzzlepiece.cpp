#include "puzzlepiece.h"
#include <QSet>

PuzzlePiece::PuzzlePiece(ConnectorPosition north, ConnectorPosition south,
                         ConnectorPosition west, ConnectorPosition east)
{

    con_pos[North] = north;
    con_pos[South] = south;
    con_pos[West] = west;
    con_pos[East] = east;

    m_size = PIECE_SIZE;

    QPainterPath sh;
    constructPath(sh);
    setPath(sh);

    m_coordinates = QPoint(0,0);
    m_neighbours[North] = 0;//1-4(разобраны)?? откуда?
    m_neighbours[South] = 0;
    m_neighbours[West] = 0;
    m_neighbours[East] = 0;


    m_image.load(":/Image/Neyronnyie-seti.jpg");
    update();
}

void PuzzlePiece::constructPath(QPainterPath &p)
{
    p.moveTo(-1*m_size/2., -1*m_size/2.);

    //north side
    con_pos[North] == Out ? p.arcTo(-1*m_size/4., -3*m_size/4., m_size/2., m_size/2., 180., -180.) :
                            con_pos[North] == In ? p.arcTo(-1*m_size/4., -3*m_size/4., m_size/2., m_size/2., 180., 180.) : // 1/4 -1/4 1/2 1/2 90 180
                                                   p.lineTo(m_size/4., -1*m_size/2.);  // 1/2 1/2
    p.lineTo(m_size/2., -1*m_size/2.);

    //east side
    p.lineTo(m_size/2., -1*m_size/4.);

    con_pos[East] == Out ? p.arcTo(m_size/4., -1*m_size/4., m_size/2., m_size/2., 90., -180.) :
                            con_pos[East] == In ? p.arcTo(m_size/4., -1*m_size/4., m_size/2., m_size/2., 90., 180.) :
                                                   p.lineTo(m_size/2., m_size/4.);
    p.lineTo(m_size/2., m_size/2.);

    //south
    p.lineTo(m_size/4., m_size/2.);

    con_pos[South] == Out ? p.arcTo(-1*m_size/4., m_size/4., m_size/2., m_size/2., 0., -180.) :
                            con_pos[South] == In ? p.arcTo(-1*m_size/4., m_size/4., m_size/2., m_size/2., 0., 180.) :
                                                   p.lineTo(-1*m_size/4., m_size/2.);
    p.lineTo(-1*m_size/2., m_size/2.);

    //West
    p.lineTo(-1*m_size/2., m_size/4.);

    con_pos[West] == Out ? p.arcTo(-3*m_size/4., -1*m_size/4., m_size/2., m_size/2., 270., -180.) :
                            con_pos[West] == In ? p.arcTo(-3*m_size/4.,-1*m_size/4., m_size/2., m_size/2., 270., 180.) :
                                                   p.lineTo(-1*m_size/2., -1*m_size/4.);
    p.lineTo(-1*m_size/2., -1*m_size/2.);

    p.closeSubpath();
}

void PuzzlePiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setClipPath(path());
    QRect rect = boundingRect().toRect();

    painter->drawPixmap(rect.x(), rect.y(), m_image );

    painter->setPen(Qt::black);
    painter->drawPath(path());

}

QPixmap PuzzlePiece::pixmap()
{
    return m_image;
}

void PuzzlePiece::setPixmap(const QPixmap& image)
{
    m_image = image;
    update();
}

void PuzzlePiece::setCoordinates(QPoint &cor)
{
    m_coordinates = cor;
}

QPoint PuzzlePiece::coordinates()
{
    return m_coordinates;
}

void PuzzlePiece::link(PuzzlePiece *StaticElement, PuzzlePiece::Direction direction)
{
    switch(direction)
    {
        case (PuzzlePiece::North):
            StaticElement->m_neighbours[PuzzlePiece::South]=this;
            m_neighbours[PuzzlePiece::North] = StaticElement;
            break;
        case (PuzzlePiece::South):
            StaticElement->m_neighbours[PuzzlePiece::North]=this;
            m_neighbours[PuzzlePiece::South] = StaticElement;
            break;
        case (PuzzlePiece::West):
            StaticElement->m_neighbours[PuzzlePiece::East]=this;//EAST
            m_neighbours[PuzzlePiece::West] = StaticElement;
            break;
        case (PuzzlePiece::East):
            StaticElement->m_neighbours[PuzzlePiece::West]=this;// WEST
            m_neighbours[PuzzlePiece::East] = StaticElement;
            break;
        default: break;
    }
}

void PuzzlePiece::findneighbor(PuzzlePiece::Direction direction)
{
    if(m_neighbours[direction])
    {
        return;
    }
    QPoint TargetedNeigbourField = coordinates();
    QPoint TargetedNeigbourPixel(this->pos().x(), this->pos().y());
    switch(direction)
    {
        case(PuzzlePiece::North):
        TargetedNeigbourField.setY(TargetedNeigbourField.y()-1);//+1
        TargetedNeigbourPixel.setY(TargetedNeigbourPixel.y()-PIECE_SIZE);
        break;
        case(PuzzlePiece::South):
        TargetedNeigbourField.setY(TargetedNeigbourField.y()+1);//-1
        TargetedNeigbourPixel.setY(TargetedNeigbourPixel.y()+PIECE_SIZE);
        break;
        case(PuzzlePiece::West):
        TargetedNeigbourField.setX(TargetedNeigbourField.x()-1);
        TargetedNeigbourPixel.setX(TargetedNeigbourPixel.x()-PIECE_SIZE);
        break;
        case(PuzzlePiece::East):
        TargetedNeigbourField.setX(TargetedNeigbourField.x()+1);
        TargetedNeigbourPixel.setX(TargetedNeigbourPixel.x()+PIECE_SIZE);
        break;
    }
    QTransform Transformation;
    QGraphicsItem *item;
    item = this->scene()->itemAt(TargetedNeigbourPixel.x(), TargetedNeigbourPixel.y(), Transformation);

    //код санька
    if (item)
    {
        PuzzlePiece *pp=dynamic_cast<PuzzlePiece *>(item);
        if (pp)
        {
            if ((pp->coordinates().x()==TargetedNeigbourField.x())&&(pp->coordinates().y()==TargetedNeigbourField.y())&&
                    ((abs(pp->x()-TargetedNeigbourPixel.x())<=5))&&(abs(pp->y()-TargetedNeigbourPixel.y())<=5))
            {
               link(pp, direction);
               item->setPos(TargetedNeigbourPixel.x(), TargetedNeigbourPixel.y());
            }
        }
    }//
}

void PuzzlePiece::checkNeighbours(QList<QPoint> &checked)
{
    if (checked.count()==this->scene()->items().count())
    {
        QMessageBox* pmbx =
                            new QMessageBox("Победа",
                            "Новую?",
                            QMessageBox::Information,
                            QMessageBox::Yes,
                            QMessageBox::No,
                            QMessageBox::Cancel | QMessageBox::Escape);
        int n = pmbx->exec();
        delete pmbx;
        if (n == QMessageBox::No)
        {
          pmbx->close();
        }
    }

    if(checked.contains(coordinates()))   return; // условия прерывания рекурсии

    checked.append(coordinates()); // запомнить посещенный элемент insert(-) = append
    findneighbor(North); // найти N соседа
    findneighbor(East); // найти E соседа
    findneighbor(South); // найти S соседа
    findneighbor(West); // найти W соседа

    if(m_neighbours[North])
        m_neighbours[North]->checkNeighbours(checked);
    if(m_neighbours[East])
        m_neighbours[East]->checkNeighbours(checked);
    if(m_neighbours[South])
        m_neighbours[South]->checkNeighbours(checked);
    if(m_neighbours[West])
        m_neighbours[West]->checkNeighbours(checked);
}

void PuzzlePiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) //checkNeighboor needed
{
    QList<QPoint> CheckedElements;//не приводится QSet->QList Даже если возможны повторения, то это не страшно
    checkNeighbours(CheckedElements);
    QGraphicsPathItem::mouseReleaseEvent(event);
}

QVariant PuzzlePiece::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged)
    {
      if (m_neighbours[PuzzlePiece::North])
          m_neighbours[PuzzlePiece::North]->setPos(this->x(),this->y()-PIECE_SIZE);
      if (m_neighbours[PuzzlePiece::South])
          m_neighbours[PuzzlePiece::South]->setPos(this->x(),this->y()+PIECE_SIZE);
      if (m_neighbours[PuzzlePiece::West])
          m_neighbours[PuzzlePiece::West]->setPos(this->x()-PIECE_SIZE,this->y());
      if (m_neighbours[PuzzlePiece::East])
          m_neighbours[PuzzlePiece::East]->setPos(this->x()+PIECE_SIZE,this->y());
    }
    return QGraphicsItem::itemChange(change, value);
}
