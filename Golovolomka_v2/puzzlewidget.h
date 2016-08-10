#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H
#include <QFrame>
#include <QObject>
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QPixmap>
#include <QSize>
#include <QPoint>


class puzzleWidget : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(QSize value READ value WRITE setValue)
    Q_PROPERTY(QSize minimum READ minimum  WRITE setMinimum)
    Q_PROPERTY(QSize maximum READ maximum  WRITE setMaximum)
    Q_PROPERTY(QPixmap preview READ preview WRITE setPreview)

    QSize m_size;
    QSize m_maximum;
    QSize m_minimum;
    QPixmap m_preview;

    void renderValue(QPainter* /*painter*/);
    void renderGrid(QPainter* painter);

    QSize cellSize() const;//const???
    QPoint cellAt(QPoint &mp) const;


public:
    puzzleWidget(QWidget *parent=0);

    QSize SizeHint() const;
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent);

    QSize value() {return m_size;}
    QSize minimum() {return m_minimum;}
    QSize maximum() {return m_maximum;}
    QPixmap preview() {return m_preview;}

public slots:
    void setValue(const QSize& s);
    void setMinimum(const QSize& s);
    void setMaximum(const QSize& s);
    void setPreview(const QPixmap& s);

signals:
    void valueChanged(const QSize& );// в moc_puzzlewidget.cpp описания сигнала выдавало ошибку, сделал кастомное изменение "&_t1"
    void heightChanged(int);
    void widthChanged(int);
};

#endif // PUZZLEWIDGET_H
