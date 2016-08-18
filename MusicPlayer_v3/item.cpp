#include "item.h"

Item::Item()
{
    m_parent = 0;
}
Item::~Item()
{
    SetParent(0);
    foreach (Item *child, m_children)
    {
        try
        {
            delete(child);
        }
        catch(...){}
    }

}

void Item::insertChild(Item *p, int pos)
{
    m_children.insert(pos, p);
    p->setParent(this);
    /*QSet<QString> set = m_children.toSet();
    m_children = set.toList();*/
    /*if (m_children.contains(p))
        p->setParent(this);
    else
    {
        if (pos<0 || pos>m_children.size())
            m_children.insert(m_children.size(), p);
        else
            m_children.insert(pos, p);
        p->setParent(this);
    }*/
}

Item *Item::takeChild(int pos)
{
    Item *p=m_children.takeAt(pos);
    try
    {
        p->setParent(0);
        return p;
    }
    catch(...){}
}
