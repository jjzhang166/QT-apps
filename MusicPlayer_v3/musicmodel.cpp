#include "musicmodel.h"
#include "albumdialog.h"
#include "artistdialog.h"
MusicModel::MusicModel()
{
    m_root = new Item();
    Artist *artist = new Artist();
    m_root->insertChild(artist,0);
}

MusicModel::~MusicModel()
{
    if(m_root)
        delete m_root;
    m_root=0;
}

QModelIndex MusicModel::index(int row, int column, const QModelIndex &parent) const
{
    Item* parentItem=m_root;
    if (parent.isValid())
    {
        parentItem=static_cast<Item*>(parent.internalPointer());
    }
    qDebug()<<row;
    qDebug()<<column;
    if (  parentItem->m_children.value(row))
    return createIndex(row, column, parentItem->childAt(row));
    else
        return QModelIndex();
}

QModelIndex MusicModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
    {
        return QModelIndex();
    }
    Item *item = static_cast<Item*>(child.internalPointer());
    if(item == m_root)
        return QModelIndex();
    Item *parentItem = item->parent();
    if(parentItem == m_root)
        return QModelIndex();

    Item *grandItem = parentItem->parent();
    if(!grandItem)
        return QModelIndex();
    else
        return createIndex(grandItem->indexOf(parentItem),
                           0,(void*)parentItem);
}

int MusicModel::columnCount(const QModelIndex &parent) const
{
       return 4;
}

int MusicModel::rowCount(const QModelIndex &parent) const
{
    Item* parentItem=m_root;
    if(parent.isValid())
        parentItem=static_cast<Item*>(parent.internalPointer());
    return parentItem->childCount();
}

QVariant MusicModel::data(const QModelIndex &index, int role) const
{
    Item *item=m_root;
    if(index.isValid())
        item=static_cast<Item*>(index.internalPointer());
    else return QVariant();

    switch(role)  {
    case Qt::DisplayRole:
        switch(index.column()){

        case 0:
        return item->m_name;
        break;

        case 1:
            if(item->toSong()){
           return item->toSong()-> m_duration;}
            return "";

            break;
        case 2:
            if(item->toSong()){
            return item->toSong()->m_rating;}
            return "";

            break;
        case 3:
            if(item->toSong()){
            return  item->toSong()->m_comment;}
            return "";
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

QVariant MusicModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation==Qt::Horizontal && role==Qt::DisplayRole){
        switch(section){
        case 0: return QObject::tr("Track");
         case 1: return QObject::tr("Duratiob");
            case 2: return QObject::tr("Rating");
            case 3: return QObject::tr("Notes");
        default:
            break;
        }
    }
    return QVariant();
}

Qt::ItemFlags MusicModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
             return 0;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MusicModel::setData(const QModelIndex &index, const QVariant &value, int role)
{


    if (index.isValid() && (role == Qt::EditRole || role ==Qt::DisplayRole))
    {
        if(index.column() == 0)
            static_cast<Item*>(index.internalPointer())->setName(value.toString());
        if(static_cast<Song*>(index.internalPointer())->toSong())
        {

            if(index.column() == 1)
                static_cast<Song*>(index.internalPointer())->setDuration(value.toTime());
            if(index.column() == 2)

                static_cast<Song*>(index.internalPointer())->setRating(value.toInt());
            if(index.column() == 3)
                static_cast<Song*>(index.internalPointer())->setComment(value.toString());
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool MusicModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Item *parentItem;
    if(parent.isValid())
        parentItem = static_cast<Item*>(parent.internalPointer());
    else parentItem=m_root;

    for ( int i = row; i <= (row + count - 1); i++ )
    {

        Item* item;
        if(parentItem==m_root)
            item = new Artist();
        if(parentItem->toArtist())
            item = new Album();
        if(parentItem->toAlbum())
            item = new Song();
        beginInsertRows(parent, row, row+count-1);
        parentItem->insertChild(item, i);
        endInsertRows();
    }

    return true;
}

bool MusicModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Item *parentItem;
    if(parent.isValid())
        parentItem = static_cast<Item*>(parent.internalPointer());
    else parentItem=m_root;

        for ( int i = (row + count - 1); i >= row; i-- )
        {
            QModelIndex child = index(i, 0, parent);
            removeRows(0, rowCount(child), child);
            beginRemoveRows(parent, 0, 0);
            parentItem->takeChild(i);
            endRemoveRows();
        }
        return true;
}

