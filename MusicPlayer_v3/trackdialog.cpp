#include "trackdialog.h"
#include "ui_trackdialog.h"

TrackDialog::TrackDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrackDialog)
{
    ui->setupUi(this);
    m_mapper.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    this->setWindowTitle("Песня");
}

TrackDialog::~TrackDialog()
{
    delete ui;
}

void TrackDialog::setModel(MusicModel *model)
{
    m_mapper.setModel(model);
    m_mapper.addMapping(ui->lineEdit,0);
    m_mapper.toFirst();
}

void TrackDialog::setModelIndex(const QModelIndex &index)
{
    QModelIndex parent = index.parent();
    m_mapper.setRootIndex(parent);
    m_mapper.setCurrentModelIndex(index);
    item=static_cast<Item*>(index.internalPointer());

    ui->lineEdit->setText(item->m_name);
    ui->plainTextEdit->setPlainText(item->m_comment);
    ui->spinBox->setValue(item->toSong()->m_rating);
    ui->timeEdit->setTime(item->toSong()->m_duration);
}

void TrackDialog::accept()
{
    m_mapper.submit();
    QDialog::accept();

    item->setComment(ui->plainTextEdit->toPlainText());
    item->toSong()->setRating(ui->spinBox->value());
    item->toSong()->setDuration(ui->timeEdit->time());
}
