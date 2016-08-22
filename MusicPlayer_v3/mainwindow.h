#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTreeView>
#include <QMainWindow>
#include "musicmodel_v3.h"
#include <QTreeWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTreeView *treeView() const;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
