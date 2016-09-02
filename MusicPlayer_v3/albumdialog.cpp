#include "albumdialog.h"
#include "ui_albumdialog.h"

AlbumDialog::AlbumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlbumDialog)
{
    ui->setupUi(this);
    m_mapper.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

AlbumDialog::~AlbumDialog()
{
    delete ui;
}

void AlbumDialog::setModel(MusicModel *model)
{
    m_mapper.setModel(model);
    m_mapper.addMapping(ui->lineEdit,0);
    m_mapper.toFirst();
}

void AlbumDialog::setModelIndex(const QModelIndex &index)
{
    QModelIndex parent = index.parent();
    m_mapper.setRootIndex(parent);
    m_mapper.setCurrentModelIndex(index);
    item=static_cast<Item*>(index.internalPointer());
    ui->label_2->setText(item->parent()->m_name);
    ui->lineEdit->setText(item->m_name);
    ui->lineEdit_2->setText(item->toAlbum()->m_genre);
    ui->spinBox->setValue(item->toAlbum()->m_year);
    ui->textEdit->setText(item->m_comment);
    ui->label_6->setPixmap(item->toAlbum()->m_cover);
}

void AlbumDialog::accept()
{
   qDebug() << m_mapper.submit();
   QDialog::accept();
   item->setComment(ui->textEdit->toPlainText());
   item->toAlbum()->setGenre(ui->lineEdit_2->text());
   item->toAlbum()->setYear(ui->spinBox->value());
   item->toAlbum()->setCover(*ui->label_6->pixmap());
}

bool AlbumDialog::addAlbum(MusicModel *model,
    const QModelIndex &parent) {
    setModel(model);
    int row = model->rowCount(parent);
    if(!model->insertRow(row, parent))
        return false;
    QModelIndex index = model->index(row, 0, parent);
    setModelIndex(index);
    if(!exec()){
        model->removeRow(row, parent);
        return false;
    }
    return true;
}

void AlbumDialog::on_pushButton_clicked()
{

    m_fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "/Users/",
                                                    tr("Images (*.png *.jpg *.jpeg *.bmp)"));

    ui->label_6->setPixmap(QPixmap(m_fileName));
    update();
}

void AlbumDialog::on_buttonBox_accepted()
{
    qDebug() << m_mapper.submit();
    QDialog::accept();
    item->setComment(ui->textEdit->toPlainText());
    item->toAlbum()->setGenre(ui->lineEdit_2->text());
    item->toAlbum()->setYear(ui->spinBox->value());
    item->toAlbum()->setCover(*ui->label_6->pixmap());
}
