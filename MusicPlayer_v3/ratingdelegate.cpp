#include "ratingdelegate.h"
#include"item.h"

QSize RatingDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(100,20);
}
void RatingDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid() || !index.parent().isValid())
        return;
    painter->setPen(Qt::black);
    painter->setBrush(Qt::cyan);
    int a=0;
    int b=option.rect.left();
    Item *item=static_cast<Item*>(index.internalPointer());
    if(item->parent()->toAlbum() )
    {
        if (index.column()==2)
            a = index.model()->data(index).toInt();
        if(a<0) a=0;
        for (int i=1; i<=5; i++)
        {
            if(i==(a+1))
                painter->setBrush(Qt::NoBrush);
            painter->drawEllipse(QPoint(b+10,option.rect.top()+10),8,8);
            b+=20;
        }
    }
}
RatingDelegate::RatingDelegate(QAbstractItemView *view)
{
    m_view=view;
}

