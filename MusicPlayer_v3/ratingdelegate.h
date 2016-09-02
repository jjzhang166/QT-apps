#ifndef RATINGDELEGATE_H
#define RATINGDELEGATE_H
#include<QStyledItemDelegate>

class RatingDelegate : public QStyledItemDelegate
{
public:
    RatingDelegate(QAbstractItemView *view);
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const ;
private:
    QAbstractItemView *m_view;

};

#endif // RATINGDELEGATE_H
