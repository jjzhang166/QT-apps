#ifndef ARTISTDIALOG_H
#define ARTISTDIALOG_H

#include <QDialog>
#include<QDataWidgetMapper>
#include "musicmodel.h"
#include "item.h"
namespace Ui {
class ArtistDialog;
}

class ArtistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArtistDialog(QWidget *parent = 0);
    ~ArtistDialog();
    void setModel(MusicModel *model);
    void setModelIndex(const QModelIndex &index);
    void accept();
    //void on_buttonBox_accepted();

private:
    Ui::ArtistDialog *ui;
    QString m_fileName;
    QPixmap m_pixmap;
    QDataWidgetMapper m_mapper;
    Item *item;
    void on_pushButton_2_clicked();
    void on_buttonBox_accepted();
};

#endif // ARTISTDIALOG_H
