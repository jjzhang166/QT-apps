#include "puzzlewidget.h"

puzzleWidget::puzzleWidget(QWidget *parent):QFrame(parent)
{

}

QSize puzzleWidget::SizeHint() const
{
    return QSize(300,300);
}

void puzzleWidget::paintEvent(QPaintEvent *)
{
    m_size = QSize(6, 5);
    m_minimum = QSize(2, 2);
    m_maximum = QSize(8, 8);
}

void puzzleWidget::setValue(const QSize &s)
{
    QSize previus = m_size;

    if (s == m_size) return;

    m_size = s;

    if (s.height() > m_maximum.height()){return;}
    if (s.width() > m_maximum.width()){return;}
    if (s.height() < m_minimum.height()){return;}
    if (s.width() < m_minimum.width()){return;}

    emit valueChanged(s);
    if (previus.height() != m_size.height()) emit heightChanged(s.height());
    if (previus.width() != m_size.width()) emit widthChanged(s.width());

    m_size = s;
    update();
}

void puzzleWidget::setMinimum(const QSize &s)
{
    if (s == m_minimum) return;
    m_minimum = s;
    update();
}

void puzzleWidget::setMaximum(const QSize &s)
{
    if (s == m_maximum) return;
    m_maximum = s;
    update();
}

void puzzleWidget::setPreview(const QPixmap &s)
{
    m_preview = s;
    update();
}
