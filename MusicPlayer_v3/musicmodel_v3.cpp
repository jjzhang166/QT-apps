#include "musicmodel_v3.h"

MusicModel::MusicModel()
{
    m_root = new Item();
    Artist *artist = new Artist();
    m_root->insertChild(artist,0);

    Artist* artist1=new Artist("name", m_root);
    Album *album1 =new Album("name", artist1->parent());
}

MusicModel::~MusicModel()
{
    if (m_root)
        delete m_root;
    m_root=0;
}

QModelIndex MusicModel::index(int row, int column, const QModelIndex &parent) const
{
    Item *parentItem=m_root;
    if (parent.isValid())
    {
        parentItem=static_cast<Item *>(parent.internalPointer());
    }

    if ((row<parentItem->childCount())&&((parentItem->toArtist() && column==0)||(parentItem==m_root && column < 1)||(parentItem->toAlbum() && column < 5)))
            return createIndex(row, column, parentItem->childAt(row));
    return QModelIndex();
}

QModelIndex MusicModel::parent(const QModelIndex &child) const
{
    Item *childItem=0;
    if (child.isValid())
    {
        childItem=static_cast<Item *>(child.internalPointer());
    }
    else return QModelIndex();
    if (!childItem)
        return QModelIndex();
    Item *parentItem=childItem->parent();
    if (parentItem)
    {
        Item *grandItem=parentItem->parent();
        if (grandItem)
        {
            return createIndex(grandItem->indexOf(parentItem), child.column(), parentItem);
        }
        else
            return createIndex(m_root->indexOf(parentItem), child.column(), m_root);
    }
    else
        return QModelIndex();
}

int MusicModel::rowCount(const QModelIndex &parent) const
{
    Item *parentItem=m_root;
    if (parent.isValid())
    {
        parentItem=static_cast<Item *>(parent.internalPointer());
    }
    return parentItem->childCount();
}

int MusicModel::columnCount(const QModelIndex &parent) const
{
    Item *parentItem=NULL;
    if (parent.isValid()) parentItem = static_cast<Item*>(parent.internalPointer());
    else return 4;

    if (parentItem->toAlbum()) return 3;
    if (parentItem->toArtist()) return 1;
    if (parentItem->toSong()) return 1;

    return 4;
}

QVariant MusicModel::data(const QModelIndex &index, int role) const
{
    Item *item=m_root;
    if (index.isValid())
        item=static_cast<Item *>(index.internalPointer());
    else
        return QVariant();
    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column())
        {
        case 0:
            return item->name();
            break;
        case 1:
            return item->toSong()->duration();
            break;
        case 2:
            return item->toSong()->rating();
            break;
        case 3:
            return item->comment();
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return QVariant();
}

Qt::ItemFlags MusicModel::flags(const QModelIndex &index) const
{
    if (index.isValid()) return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    return 0;
}

bool MusicModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && (role == Qt::EditRole || role ==Qt::DisplayRole))
    {
        if (index.column() == 0 && value.canConvert(QMetaType::QString))
          static_cast<Item*>(index.internalPointer())->setName(value.toString());
        if(static_cast<Song*>(index.internalPointer())->toSong())
        {
            if(index.column() == 1 && value.canConvert(QMetaType::QTime))
              static_cast<Song*>(index.internalPointer())->setDuration(value.toTime());
            if(index.column() == 2 && value.canConvert(QMetaType::Int))
              static_cast<Song*>(index.internalPointer())->setRating(value.toInt());
            if(index.column() == 3 && value.canConvert(QMetaType::QString))
              static_cast<Song*>(index.internalPointer())->setComment(value.toString());
        }

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool MusicModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Item *parentItem=m_root;
    if (parent.isValid()) parentItem=static_cast<Item *>(parent.internalPointer());
    for (int i=row; i<=row+count-1;i++)
    {
        Item *tmp;
        if (parentItem->toAlbum()) tmp = new Song();
        else
            if (parentItem->toArtist()) tmp = new Album();
        else
            if (parentItem==m_root) tmp = new Artist();
        beginInsertRows(parent, row, row+count-1);
        parentItem->insertChild(tmp, i);
        endInsertRows();
    }
    return true;
}

bool MusicModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Item *parentItem=m_root;
    if (parent.isValid()) parentItem=static_cast<Item *>(parent.internalPointer());
    for (int i=(row+count-1); i>=row;i--)
    {
        QModelIndex tmp = index(i, 0, parent);
        removeRows(0, rowCount(tmp), tmp);

        beginRemoveRows(parent, 0, 0);
        parentItem->takeChild(i);
        endRemoveRows();
    }
    return true;
}
