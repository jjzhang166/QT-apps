#ifndef MUSICMODEL_H
#define MUSICMODEL_H
#include <QAbstractItemModel>
#include "item.h"
#include <QModelIndex>
#include <QVariant>
#include <QMainWindow>
#include <QtGui>
#include <QPixmap>
#include <QTime>
#include <QtGlobal>
#include <QDataStream>
#include <QTreeView>
#include <QStyledItemDelegate>
#include <QSize>
#include <QAbstractItemView>
#include <QTreeWidgetItem>
#include <QMouseEvent>

// model test?!

class MusicModel : public QAbstractItemModel
{
public:
    MusicModel();
    ~MusicModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
private:
    Item *m_root;
};

#endif // MUSICMODEL_H
