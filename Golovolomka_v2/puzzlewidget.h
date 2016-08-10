#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H
#include <QFrame>
#include <QObject>


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
public:
    puzzleWidget(QWidget *parent=0);

    QSize SizeHint() const;
    void paintEvent(QPaintEvent *);

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
    void valueChanged(const QSize& );
    void heightChanged(int);
    void widthChanged(int);
};

#endif // PUZZLEWIDGET_H
