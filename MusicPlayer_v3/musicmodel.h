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

class musicmodel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit musicmodel(QObject *parent = 0);


    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

   // bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    Item *m_root;
};

#endif // MUSICMODEL_H
