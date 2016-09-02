#ifndef TRACKDIALOG_H
#define TRACKDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>
#include "musicmodel.h"
#include "item.h"
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class TrackDialog;
}

class TrackDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrackDialog(QWidget *parent = 0);
    ~TrackDialog();
    void setModel(MusicModel *model);
    void setModelIndex(const QModelIndex &index);
    void accept();

private:
    Ui::TrackDialog *ui;
    QDataWidgetMapper m_mapper;
    Item *item;
};

#endif // SONGDIALOG_H
