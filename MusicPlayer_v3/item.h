#ifndef ITEM_H
#define ITEM_H
#include <QList>
#include <QString>
#include <QSet>
#include <QDebug>
#include <QPixmap>
#include <QTime>
#include <QFile>
#include <QDataStream>

class Artist;
class Album;
class Song;

class Item
{
public:
    Item();
    Item(QString name,Item* parent=0);
    ~Item();
    Item *parent() const;
    void setParent(Item *Parent);
    void insertChild(Item *, int position = -1);
    Item *takeChild(int position);
    Item *childAt(int position) const;
    int indexOf(Item* item) const;
    int childCount() const;
    QString name() const;
    QString comment() const;
    void setName(const QString &name);
    void setComment(const QString &name);
    virtual Artist* toArtist();
    virtual Album* toAlbum();
    virtual Song* toSong();
private:
    Item *m_parent;
    QList<Item*> m_children;
    QString m_name;
    QString m_comment;
};
////////////////////// ARTIST ///////////////////////
class Artist : public Item
{
public:
    Artist() : Item()
    {}//" ; " ЛИШНЕЕЕЕ???
    Artist(QString name, Item *parent=0);
    QString country() const;
    QPixmap photo() const;
    QList<Album*> albums() const;
    void setPhoto(const QPixmap &photo);
    void setCountry(const QString &country);
    void setAlbums(QList<Album *> &albums);
    Artist* toArtist();
    Album* toAlbum();
    Song* toSong();
private:
    QPixmap m_photo;
    QString m_country;
    QList<Album*> m_albums;
};
///////////////////// ALBUM ////////////////////////
class Album : public Item
{
public:
    Album() : Item()
    {}//" ; " ЛИШНЕЕЕЕ???
    Album(QString name, Item *parent=0);
    int year() const;
    QPixmap cover() const;
    QString genre() const;
    QList<Song*> songs() const;
    Artist* artist() const;
    void setYear(const int &year);
    void setCover(const QPixmap &cover);
    void setGenre(const QString &genre);
    void setSongs(QList<Song*> &songs);
    void setArtist(Artist *&artist);
    Artist* toArtist();
    Album* toAlbum();
    Song* toSong();
private:
    int m_year;
    QPixmap m_cover;
    QString m_genre;
    QList<class Song*> m_songs;
    class Artist *m_artist;
};
////////////////// SONG ////////////////////
class Song : public Item
{
public:
    Song() : Item()
    {}//" ; " ЛИШНЕЕЕЕ???
    Song(QString name, Item *parent=0);
    QTime duration() const;
    int rating() const;
    Album* album() const;
    void setRating(const int &rating);
    void setDuration(const QTime &duration);
    void setAlbum(Album* &album);
    Artist* toArtist();
    Album* toAlbum();
    Song* toSong();
private:
    int m_rating;
    QTime m_duration;
    Album *m_album;
};

QDataStream & operator<<(QDataStream &stream, Song &song);
QDataStream & operator>>(QDataStream &stream, Song &song);

QDataStream & operator<<(QDataStream &stream, Artist &artist);
QDataStream & operator>>(QDataStream &stream, Artist &artist);

QDataStream & operator<<(QDataStream &stream, Album &album);
QDataStream & operator>>(QDataStream &stream, Album &album);

QDataStream & operator<<(QDataStream &stream, Item &root);




#endif // ITEM_H
