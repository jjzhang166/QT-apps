#ifndef WEBPLUGIN_H
#define WEBPLUGIN_H
#include <QWebPluginFactory>
#include <QString>
#include <QFont>
#include "mainwindow.h"
#include "widget.h"
#include <QtWebKit>

class WebPlugin : public QWebPluginFactory
{
    Q_OBJECT
public:
    explicit WebPlugin(QObject *parent = 0);
    ~WebPlugin();
    QList<Plugin> plugins() const;
    QObject *create(const QString &mimeType,
                    const QUrl &url,
                    const QStringList &argumentNames,
                    const QStringList &argumentValues) const;




private:

};

#endif // WEBPLUGIN_H
