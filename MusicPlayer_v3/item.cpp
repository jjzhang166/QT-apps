#include "item.h"


Item::Item()
{
    m_parent=0;
    m_name=QString("");
    m_comment=QString("");
}

Item::~Item()
{
    setParent(0);
    foreach (Item* child,m_children)
    {
        if (child) delete child;
    }
}

Item *Item::parent() const
{
    return m_parent;
}

Item::Item(QString name, Item *parent)
{
    m_parent=parent;
    m_name=name;
    m_comment=QString("");

}

void Item::setParent(Item *p)
{
    if (m_parent==p)
        return;
    if (p)
    {
        if(m_parent)
        {
            m_parent->takeChild(m_parent->indexOf(p));
        }
        m_parent=p;
        m_parent->insertChild(this);
    }
}

void Item::insertChild(Item *p, int pos)
{
    if (!p) return;
    if(m_children.contains(p))
        p->setParent(this);
    else
    {
        if(pos<0||pos>m_children.size())
            m_children.insert(m_children.size(),p);
        else
            m_children.insert(pos,p);
        p->setParent(this);
    }
}

Item *Item::takeChild(int pos)
{
    Item* p=m_children.takeAt(pos);
    if (p)
        p->setParent(0);
    qDebug()<<QString("CHECK 1!!")<<p->m_name<<" to item "<<m_name<<" at pos "<<pos;
    return p;
}

Item *Item::childAt(int pos) const
{
    if(pos<0||pos>m_children.size())
        return 0;
    Item* p=m_children.at(pos);
    qDebug()<<QString("KTO ETO")<<pos;

    return p;
}

int Item::indexOf(Item *item) const
{
    return m_children.indexOf(item,0);
}

int Item::childCount() const
{
    return m_children.count();
}

bool Item::insertChildren(int pos, int count)
{
    if (pos < 0 || pos > m_children.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QString data;
        Item *item = new Item(data,this);
        m_children.insert(pos, item);
    }

    return true;
}

bool Item::removeChildren(int pos, int count)
{
    if (pos < 0 || pos + count > m_children.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_children.takeAt(pos);

    return true;
}


void Item::setName(QString name)
{
    m_name=name;
}


void Item::setComment(QString comment)
{
    m_comment=comment;
}

int Item::colomnCount()
{
    return 4;
}

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

Song::Song():Item()
{
    m_rating=0;
}

Artist *Song::toArtist()
{
    return NULL;
}

Album *Song::toAlbum()
{
    return NULL;
}

Song* Song::toSong() { return this; }

int Song::colomnCount()
{
    return 1;
}

void Song::setDuration(QTime time)
{
    m_duration= time;
}

void Song::setRating(int rating)
{
    m_rating = rating;
}



Album::Album():Item()
{

}

Artist *Album::toArtist()
{
    return NULL;
}

Album* Album::toAlbum()
{
    return this;
}

Song *Album::toSong()
{
    return NULL;
}

int Album::colomnCount()
{
    return 3;
}

void Album::setCover(QPixmap cover)
{
    m_cover = cover;
}

void Album::setYear(int year)
{
    m_year = year;
}

void Album::setGenre(QString genre)
{
    m_genre = genre;
}


Artist::Artist():Item()
{

}

Artist* Artist::toArtist() { return this; }

Album *Artist::toAlbum()
{
    return NULL;
}

Song *Artist::toSong()
{
    return NULL;
}

int Artist::colomnCount()
{
    return 1;
}

void Artist::setPhoto(QPixmap photo)
{
    m_photo=photo;
}

void Artist::setCountry(QString country)
{
    m_country=country;
}
QDataStream& operator <<(QDataStream &stream, Artist &artist) {
  // stream << "ARTIST";
    stream << artist.m_name << artist.m_photo << artist.m_comment << artist.m_country;

    int cnt = artist.childCount();
    stream << cnt;
    for(int i=0; i<cnt; ++i){
        Album *album = artist.childAt(i)->toAlbum();
        if(album) {
            stream << *album; }
    }
    return stream;
}



QDataStream& operator <<(QDataStream &stream, Album &album) {
  // stream << "ALBUM";
    stream << album.m_name << album.m_cover<< album.m_comment << album.m_year << album.m_genre;

    int cnt = album.childCount();
    stream << cnt;
    for(int i=0; i<cnt; ++i){
        Song *song = album.childAt(i)->toSong();
        if(song) {
            stream << *song; }
    }
    return stream;
}

QDataStream& operator <<(QDataStream &stream, Song &song) {
    //stream << "SONG";
    stream << song.m_name << song.m_duration << song.m_comment << song.m_rating;

    return stream;
}

QDataStream& operator << (QDataStream &stream, Item &root)
{
    int cnt = root.childCount();
    stream << cnt;
    for(int i=0; i<cnt; ++i){
        Artist *artist = root.childAt(i)->toArtist();
        if(artist) {
            stream << *artist; }
    }
    return stream;
}

QDataStream& operator >>(QDataStream &stream, Artist &artist) {

    stream >>artist.m_name >> artist.m_photo >> artist.m_comment >> artist.m_country;

    return stream;
}

QDataStream& operator >>(QDataStream &stream, Album &album) {

    stream >>album.m_name >> album.m_cover >> album.m_comment >> album.m_year >> album.m_genre;

    return stream;
}

QDataStream& operator >>(QDataStream &stream, Song &song) {

    stream >> song.m_name >> song.m_duration>> song.m_comment >> song.m_rating;

    return stream;
}
