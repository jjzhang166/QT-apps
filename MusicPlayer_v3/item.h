#ifndef ITEM_H
#define ITEM_H

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

class Album;
class Song;
class Artist;
class Item {
public:
    Item();
    ~Item();
    Item *parent() const;
    Item(QString name,Item* parent=0);
    void setParent(Item *p);
    void insertChild(Item *p, int pos = -1);
    Item* takeChild(int pos);
    Item *childAt(int pos) const;
    int indexOf(Item* item) const;
    int childCount() const;
    bool insertChildren(int position, int count);
    bool removeChildren(int position, int count);
    void setName(QString name);
    void setComment(QString comment);
    virtual int colomnCount();
    virtual Artist* toArtist();
    virtual Album* toAlbum();
    virtual Song* toSong();
    QList<Item*> m_children;
    QString m_name;

    QString m_comment;
private:
    Item *m_parent;

};

class Artist : public Item
{
public:
    Artist();
    Artist* toArtist();
    Album* toAlbum();
    Song* toSong();
    int colomnCount();
    void setPhoto(QPixmap photo);
    void setCountry(QString country);

    QPixmap m_photo;
    QString m_country;
};

class Album : public Item
{
public:
    Album();
    Artist* toArtist();
    Album* toAlbum();
    Song* toSong();
    int colomnCount();
    void setCover(const QPixmap cover);
    void setYear(int year);
    void setGenre(QString genre);

    QPixmap m_cover;
    int m_year;
    QString m_genre;
};

class Song : public Item
{
public:
    Song();
    Artist* toArtist();
    Album* toAlbum();
    Song* toSong();
    int colomnCount();
    void setDuration(QTime time);
    void setRating(int rating);
    int m_rating;

    QTime m_duration;

};
QDataStream& operator <<(QDataStream &stream, Item &root);
QDataStream& operator <<(QDataStream &stream, Artist &artist);
QDataStream& operator >>(QDataStream &stream, Artist &artist);
QDataStream& operator <<(QDataStream &stream, Album &album);
QDataStream& operator <<(QDataStream &stream, Song &song);
QDataStream& operator >>(QDataStream &stream, Album &album);
QDataStream& operator >>(QDataStream &stream, Song &song);
#endif // ITEM_H

