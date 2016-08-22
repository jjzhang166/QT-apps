#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "item.h"
#include "musicmodel_v3.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeView *MainWindow::treeView() const
{
    return ui->treeView;
}
