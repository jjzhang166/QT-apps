#include "webplugin.h"

WebPlugin::WebPlugin(QObject *parent)
{

}

WebPlugin::~WebPlugin()
{}

QList<QWebPluginFactory::Plugin> WebPlugin::plugins() const
{
    MimeType MT;
    MT.name = "application/x-chart";
    QWebPluginFactory::Plugin plugin;
    QList<QWebPluginFactory::Plugin> pluginList;
    plugin.mimeTypes.append(MT);
    pluginList.append(plugin);
    return pluginList;
}

QObject *WebPlugin::create(const QString &mimeType,
                const QUrl &url,
                const QStringList &argumentNames,
                const QStringList &argumentValues) const
{
    Widget *result = 0;
    if (mimeType == "application/x-chart")
    {
        result = new Widget();
        for (int i = 0; i < argumentNames.count(); i++)
        {
            if (argumentNames[i]=="title")
            {
                result->setTitle(argumentValues[i]);
            }
            if (argumentNames[i]=="value")
            {
                result->setValue(argumentValues[i].toInt());
            }
        }
        return result;
    }
    else
    {
        return 0;
    }
}
