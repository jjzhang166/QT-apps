#include "puzzlewidget.h"

void puzzleWidget::renderValue(QPainter *painter)
{
    QSize cell_size = cellSize();
    if(!m_preview.isNull())//есть картинка
    {
        QSize sz(cell_size.width()*value().width(), cell_size.height()*value().height());
        painter->drawPixmap(0, 0, m_preview.scaled(sz));
    }
    else//нет рисунка
    {
        painter->setBrush((Qt::gray));
        painter->drawRect(0, 0, cell_size.width()*value().width(), cell_size.height()*value().height());
    }
}

void puzzleWidget::renderGrid(QPainter *painter)
{

}

QSize puzzleWidget::cellSize() const
{
    int w = width();
    int h = height();
    int mw = m_maximum.width();
    int mh = m_maximum.height();
    int extent = qMin(w/mw, h/mh);
    return QSize(extent, extent).expandedTo(QApplication::globalStrut()).expandedTo(QSize(4,4));//Use the expandedTo() function to retrieve a size which holds the maximum height and width of this size and a given size.
}

QPoint puzzleWidget::cellAt(QPoint &mp) const
{
    QSize cs = cellSize();
    int x = mp.x()/ cs.width() + 1;
    int y = mp.y()/ cs.height() + 1;
    return QPoint(x,y);
}

puzzleWidget::puzzleWidget(QWidget *parent):QFrame(parent)
{
    m_size = QSize(6, 5);
    m_minimum = QSize(2, 2);
    m_maximum = QSize(8, 8);
    m_preview.load(":/Image/Neyronnyie-seti.jpg");
}

QSize puzzleWidget::SizeHint() const
{
    return QSize(600,600);
}

void puzzleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    renderValue(&painter);
    renderGrid(&painter);
}

void puzzleWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint mp = event->pos();
    QPoint cell = cellAt(mp);
    setValue(QSize(cell.x(),cell.y()));

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
