#ifndef MUSICMODEL_H
#define MUSICMODEL_H
#include<QAbstractItemModel>
#include"item.h"
class MusicModel : public QAbstractItemModel
{

public:
    MusicModel();
    ~MusicModel();
    Item* m_root;
    QModelIndex index(int row,int column, const QModelIndex &parent=QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

};

#endif // MUSICMODEL_H
