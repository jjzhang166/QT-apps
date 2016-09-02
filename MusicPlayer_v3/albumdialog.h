#ifndef ALBUMDIALOG_H
#define ALBUMDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataWidgetMapper>
#include "musicmodel.h"
#include <QDataWidgetMapper>
#include "item.h"
namespace Ui {
class AlbumDialog;
}

class AlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumDialog(QWidget *parent = 0);
    ~AlbumDialog();
    void setModel(MusicModel *model);
    void setModelIndex(const QModelIndex &index);
    void accept();
    bool addAlbum(MusicModel *model,
                  const QModelIndex &parent);

private:
    Ui::AlbumDialog *ui;
    QString m_fileName;
    QPixmap m_pixmap;
    QDataWidgetMapper m_mapper;
    Item *item;
    void on_pushButton_clicked();
    void on_buttonBox_accepted();
};

#endif // ALBUMDIALOG_H
