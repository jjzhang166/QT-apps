#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "puzzlewidget.h"

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = 0);
    ~ConfigurationDialog();
    QSize puzzleSize() const;// опять почему именно эти назначили конст
    QString imageFilePath() const;

private slots:

    void on_pushButton_clicked(bool checked);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ConfigurationDialog *ui;
};

#endif // CONFIGURATIONDIALOG_H
