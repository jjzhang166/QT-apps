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
    QPixmap pm;
    pm.load(fileName);
    ui->puzzleQidget->setPreview(pm);
}
