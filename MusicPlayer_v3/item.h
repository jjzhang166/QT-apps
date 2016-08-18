#ifndef ITEM_H
#define ITEM_H
#include <QList>
#include <QString>
#include <QSet>


class Item
{
public:
    Item();
    ~Item();
    Item *parent() const;
    void setParent(Item *);
    void insertChild(Item *, int position = 1);
    Item *takeChild(int);
    Item *childAt(int) const;
    int indexOf(Item*) const;
    int childCount() const;
private:
    Item *m_parent;
    QList<Item*> m_children;
    QString m_name;
    QString m_comment;
};

#endif // ITEM_H
