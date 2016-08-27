#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWebKit>
#include <QPainter>
#include <QFont>
#include <QFontMetrics>
#include <QDebug>

class Widget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)//зачем?
    Q_PROPERTY(int value READ value WRITE setValue)//зачем?
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setTitle(QString Title);
    void setValue(int Value);
    QString title();
    int value();
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    QString m_title;
    int m_value;
};

#endif // WIDGET_H
