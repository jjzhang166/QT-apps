#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QInputDialog>
#include <QTextStream>
#include <QString>
#include <QFontDialog>
#include <QSettings>
#include <QCloseEvent>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString m_fileName;


public:
    explicit MainWindow(const QString &fileName=QString(),QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void documentModified();

    void on_actionSelectFont_triggered();

    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

    bool saveFile();

    bool saveFileAs();

private:
    Ui::MainWindow *ui;
    void loadFile(const QString &fileName);//extra qualification MainWindow on loadfile
    void setFileName (const QString &fileName);


protected:
    void closeEvent(QCloseEvent *e);

};

#endif // MAINWINDOW_H
