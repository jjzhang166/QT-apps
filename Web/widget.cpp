#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    m_value = 0;
}

Widget::~Widget()
{

}

void Widget::setTitle(QString Title)
{
    m_title = Title;
}

void Widget::setValue(int value)
{
    m_value = value;
}

QString Widget::title()
{
    return m_title;
}

int Widget::value()
{
    return m_value;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QFont serifFont("Times", 10, QFont::Bold);
    QFontMetrics SF(serifFont);
    int UP = SF.height();
    qDebug()<<QString("LOL")<<UP; //
    QPainter painter(this);
    painter.setFont(serifFont);
    painter.drawText(0, 0, 100, 20, 0, m_title);

    QRect rect;
    rect.setRect(0, UP, 150, 150);

    painter.setBrush(Qt::darkCyan);
    painter.drawPie(rect, 16 * 90, 16 * 36/10 * m_value + 1 );

}
