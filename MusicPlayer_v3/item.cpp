#include "item.h"

Item::Item()
{
    m_parent = 0;
}

Item::Item(QString name, Item *parent)
{ qDebug()<<QString("create item")<<name; // не логгится
    m_name=name;
    m_parent=parent;
}

Item::~Item()
{
    //qDebug()<<QString("deleting item");
    setParent(0);
    foreach (Item *child, m_children)
    {
        try
        {
            delete(child);
        }
        catch(...){}
    }

}

void Item::insertChild(Item *p, int position)//rough version
{
    m_children.insert(position, p);
    p->setParent(this);
    /*QSet<QString> set = m_children.toSet();
    m_children = set.toList();*/
    /*if (m_children.contains(p))
        p->setParent(this);
    else
    {
        if (position<0 || position>m_children.size())
            m_children.insert(m_children.size(), p);
        else
            m_children.insert(position, p);
        p->setParent(this);
    }*/
}

Item *Item::takeChild(int position)//WARNING
{
    Item *p=m_children.takeAt(position);
    try
    {
        p->setParent(0);
        return p;
    }
    catch(...){/*qWarning() << "No pointer catched ";*/}
}

void Item::setParent(Item *Parent)// check
{
    if (Parent)
    {
        if (m_parent)// disconnect
        {
            m_parent->takeChild(m_parent->indexOf(this));
        }
        m_parent=Parent;//connect
        m_parent->insertChild(this);
    }
}

int Item::indexOf(Item *item) const// type of m_children consistents?
{
    if(m_children.contains(item))
    {
        return m_children.indexOf(item);
    }
    else
    {
        return NULL;
    }
}

Item *Item::childAt(int position) const
{
    if ( position>m_children.size() || position<0)
        return NULL;
    Item *p=m_children.at(position);
    return p;
}

QString Item::name() const
{
    return m_name;
}

QString Item::comment() const
{
    return m_comment;}

void Item::setName(const QString &name)
{
    m_name = name;
}

void Item::setComment(const QString &name)
{
    m_comment = name;
}

int Item::childCount() const
{
    return m_children.count();
}

Item *Item::parent() const
{
    return m_parent;
}

//////////////////// ARTIST //////////////////////////

Artist::Artist(QString name, Item *parent) : Item(name)
{
    setParent(parent);
    m_photo=QPixmap();
    m_country=QString();
    m_albums=QList<Album*>();
}

QPixmap Artist::photo() const
{
    return m_photo;
}

QString Artist::country() const
{
    return m_country;
}

QList<Album*> Artist::albums() const
{
    return m_albums;
}

void Artist::setAlbums(QList<Album *> &albums)
{
    m_albums = albums;
}

void Artist::setPhoto(const QPixmap &photo)
{
    m_photo = photo;
}

void Artist::setCountry(const QString &country)
{
    m_country = country;
}

//////////////////// ALBUM ///////////////////////////

Album::Album(QString name, Item *parent) : Item(name)
{
    setParent(parent);
    m_year=0;
    m_cover=QPixmap();
    m_genre= QString();
    m_songs=QList<Song*>();
    m_artist=NULL;
}

int Album::year() const
{
    return m_year;
}

QPixmap Album::cover() const
{
    return m_cover;
}

QString Album::genre() const
{
    return m_genre;
}

QList<Song*> Album::songs() const
{
    return m_songs;
}

Artist* Album::artist() const
{
    return m_artist;
}

void Album::setYear(const int &year)
{
    m_year = year;
}

void Album::setCover(const QPixmap &cover)
{
    m_cover = cover;
}

void Album::setGenre(const QString &genre)
{
    m_genre = genre;
}

void Album::setSongs(QList<Song*> &songs)
{
    m_songs = songs;
}

void Album::setArtist(Artist *&artist)
{
    m_artist = artist;
}

/////////////////// SONG //////////////////////////////

Song::Song(QString name, Item *parent) : Item(name)
{
    setParent(parent);
    m_rating=0;
    m_duration=QTime::currentTime();
    m_album=NULL;
    m_rating=0;
}

int Song::rating() const
{
    return m_rating;
}

QTime Song::duration() const
{
    return m_duration;
}

Album *Song::album() const
{
    return m_album;
}

void Song::setDuration(const QTime &duration)
{
    m_duration = duration;
}

void Song::setRating(const int &rating)
{
    m_rating = rating;
}

void Song::setAlbum(Album* &album)
{
    m_album = album;
}

////////////////

Artist *Item::toArtist()
{
    return NULL;
}

Album *Item::toAlbum()
{
    return NULL;
}

Song *Item::toSong()
{
    return NULL;
}

Artist *Artist::toArtist()
{
    return this;
}

Album *Artist::toAlbum()
{
    return NULL;
}

Song *Artist::toSong()
{
    return NULL;
}

Artist *Album::toArtist()
{
    return NULL;
}

Album *Album::toAlbum()
{
    return this;
}

Song *Album::toSong()
{
    return NULL;
}

Artist *Song::toArtist()
{
    return NULL;
}

Album *Song::toAlbum()
{
    return NULL;
}

Song *Song::toSong()
{
    return this;
}

////////////// SERIALIZATION ////////////////////
/// \brief operator <<
/// \param stream
/// \param song
/// \return
///
QDataStream & operator<<(QDataStream &stream, Song &song)
{
    stream<<"passing the song unit"<<song.name()<<song.duration()<<song.rating()<<song.comment();
    //stream<<song.name()<<song.duration()<<song.rating()<<song.comment();
    return stream;
}

QDataStream & operator>>(QDataStream &stream, Song &song)
{
    QString name;
    QTime duration;
    int rating;
    QString comment;
    stream >> name >> duration >> rating >> comment;
    song.setName(name);
    song.setDuration(duration);
    song.setRating(rating);
    song.setComment(comment);
    return stream;
}

QDataStream & operator<<(QDataStream &stream, Artist &artist)
{
    stream << "passing artist unit";//<<artist.name()<<artist.photo()<<artist.country()<<artist.comment();
    stream<<artist.name()<<artist.photo()<<artist.country()<<artist.comment();
    int cnt = artist.childCount();
    stream << cnt;
    for(int i=0; i<cnt; ++i)
    {
        Album *album = artist.childAt(i)->toAlbum();
        if(album)
        {
             stream << *album;
        }
    }
    return stream;
}

QDataStream & operator>>(QDataStream &stream, Artist &artist)
{
    QString name;
    QPixmap photo;
    QString country;
    QString comment;
    stream >> name >> photo >> country >> comment;
    artist.setName(name);
    artist.setPhoto(photo);
    artist.setCountry(country);
    artist.setComment(comment);
    return stream;
}

QDataStream & operator<<(QDataStream &stream, Album &album)
{
    stream << "ALBUM";
    stream<<album.name()<<album.year()<<album.cover()<<album.genre()<<album.comment();
    int cnt = album.childCount();
    stream << cnt;
    for(int i=0; i<cnt; ++i)
    {
        Song *song = album.childAt(i)->toSong();
        if(song)
        {
             stream << *song;
        }
    }
    return stream;
}

QDataStream & operator>>(QDataStream &stream, Album &album);

QDataStream & operator<<(QDataStream &stream, Item &root);
