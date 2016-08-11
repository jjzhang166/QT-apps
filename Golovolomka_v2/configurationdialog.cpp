#include "configurationdialog.h"
#include "ui_configurationdialog.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(on_pushButton_clicked(bool checked)));
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::on_pushButton_clicked(bool checked)//почему bool предотвращает повторный вызов диалога
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), QDir::currentPath(),/*"/home",*/ "Images (*.png *.xpm *.jpg)");
    ui->lineEdit->setText(fileName);
    QPixmap Pm;
    Pm.load(fileName);
    ui->puzzleQidget->setPreview(Pm);
}

QSize ConfigurationDialog::puzzleSize() const
{
    return ui->puzzleQidget->value();
}

QString ConfigurationDialog::imageFilePath() const
{
    return ui->lineEdit->text();
}




void ConfigurationDialog::on_buttonBox_accepted()
{

}

void ConfigurationDialog::on_buttonBox_rejected()
{

}
