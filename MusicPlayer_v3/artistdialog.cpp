#include "artistdialog.h"
#include "ui_artistdialog.h"
#include "item.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDataWidgetMapper>
#include <QModelIndex>
ArtistDialog::ArtistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArtistDialog)
{

    ui->setupUi(this);
    m_mapper.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

ArtistDialog::~ArtistDialog()
{
    delete ui;
}

void ArtistDialog::setModel(MusicModel *model)
{
    m_mapper.setModel(model);
    m_mapper.addMapping(ui->lineEdit_3,0);
    m_mapper.toFirst();
}

void ArtistDialog::setModelIndex(const QModelIndex &index)
{
    QModelIndex parent = index.parent();
    m_mapper.setRootIndex(parent);
    m_mapper.setCurrentModelIndex(index);
    item=static_cast<Item*>(index.internalPointer());
    ui->lineEdit->setText(item->toArtist()->m_country);//+
    ui->lineEdit_3->setText(item->m_name);
    ui->textEdit->setText(item->m_comment);//+
    ui->label_6->setPixmap(item->toArtist()->m_photo);//+
}

void ArtistDialog::accept()
{
   qDebug() << m_mapper.submit();
   QDialog::accept();
   item->setComment(ui->textEdit->toPlainText());
   item->toArtist()->setCountry(ui->lineEdit->text());
   item->toArtist()->setPhoto(*ui->label_6->pixmap());

}


void ArtistDialog::on_pushButton_2_clicked()
{
    m_fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "/Users/",
                                                    tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    ui->label_6->setPixmap(QPixmap(m_fileName));
    update();
}

void ArtistDialog::on_buttonBox_accepted()
{
    qDebug() << m_mapper.submit();
    QDialog::accept();
    item->setComment(ui->textEdit->toPlainText());
    item->toArtist()->setCountry(ui->lineEdit->text());
    item->toArtist()->setPhoto(*ui->label_6->pixmap());
}
