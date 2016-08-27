#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCalendarWidget>
#include <QWebView>
#include <QString>
#include <QFileDialog>
#include <QWebFrame>
#include <QWebElementCollection>
#include <QMap>
#include <QDate>
#include <QDebug>
#include <QTextCharFormat>
#include <QBrush>
#include "webplugin.h"




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_action_triggered(bool checked);

    void on_webView_loadFinished(bool arg1);

    void on_calendarWidget_selectionChanged();

private:
    Ui::MainWindow *ui;
    QMap<QDate,QWebElement> Dates;
    QTextCharFormat TCF;
    QWebElement PreviusReport;
};

#endif // MAINWINDOW_H
