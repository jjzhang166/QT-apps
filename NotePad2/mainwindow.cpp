#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QInputDialog>
#include <QTextStream>
#include <QString>
#include <QFontDialog>
#include <QSettings>
#include <QCloseEvent>

MainWindow::MainWindow(const QString &fileName,QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionClose,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->actionExit,SIGNAL(triggered(bool)),qApp,SLOT(closeAllWindows()));
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(documentModified()));
    QSettings settings;
    QFont font=settings.value("viewFont").value<QFont>();
    ui->textEdit->setFont(font);
    connect(ui->actionAboutQT,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));
    ui->actionCut->setEnabled(false);
    connect(ui->actionCut,SIGNAL(triggered(bool)),ui->textEdit,SLOT(cut()));
    ui->actionCopy->setEnabled(false);
    connect(ui->actionCopy, SIGNAL(triggered(bool)), ui->textEdit, SLOT(copy()));
    connect(ui->actionPaste,SIGNAL(triggered(bool)),ui->textEdit, SLOT(paste()));
    ui->actionRedo->setEnabled(false);
    connect(ui->actionUndo, SIGNAL(triggered(bool)), ui->textEdit, SLOT(undo()));
    ui->actionUndo->setEnabled(false);
    connect(ui->actionRedo, SIGNAL(triggered(bool)), ui->textEdit, SLOT(redo()));
    connect(ui->textEdit,SIGNAL(copyAvailable(bool)),ui->actionCopy,SLOT(setEnabled(bool)));
    connect(ui->textEdit,SIGNAL(copyAvailable(bool)),ui->actionCut,SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(undoAvailable(bool)), ui->actionUndo, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(redoAvailable(bool)), ui->actionRedo, SLOT(setEnabled(bool)));
    //QApplication::font()//?????
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionSaveAs, SIGNAL(triggered(bool)), this, SLOT(saveFileAs()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionNew_triggered()
{
    MainWindow *pNew = new MainWindow();
    pNew->show();
}
void MainWindow::documentModified()
{
    setWindowModified(true);
    setWindowTitle(tr("MainWindow[*]"));
}
void MainWindow::closeEvent(QCloseEvent *e)
{
    if(isWindowModified())
    {
        switch(QMessageBox::warning(this, tr("Document modified"),tr("The document has been modified, do you want to close it? You will loose all ur changes."), QMessageBox::Yes |  QMessageBox::No | QMessageBox::Cancel, QMessageBox::Cancel))
        {
            case QMessageBox::Yes:
                e->accept();
                break;
            case QMessageBox::No:
                e->ignore();
                break; //НО ПОЧЕМУ БЕЗ БРЕЙКА НЕ РАБОТАЕТ?!
            case QMessageBox::Cancel:
                e->ignore();
                break;
        }
    }
    else
    {
        e->accept();
    }
}
void MainWindow::on_actionSelectFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
    if (ok)
    {
        ui->textEdit->setFont(font);
        // the user clicked OK and font is set to the font the user selected
        QSettings Set;
        Set.setValue("ViewFont",font);
    }
    else
    {
        // the user canceled the dialog; font is set to the initial
        // value, in this case Helvetica [Cronyx], 10
    }
}
void MainWindow::on_actionAbout_triggered()
{
    //QMessageBox::about(qApp);
}
void MainWindow::loadFile(const QString &fileName)
{
    if (fileName.isNull())
        setFileName(QString());
    QFile file(fileName);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         QMessageBox::warning(this, tr("Ошибка"), tr("Файл не открыт"), tr("Ок"), tr("Отмена"), 0, 0, -1);
         setFileName(QString());
         return;
     }
     QTextStream in(&file);
     while (!in.atEnd())
     {
         ui->textEdit->setText(in.readAll());
     }
     file.close();
     setFileName(fileName);
     setWindowModified(false);

}
void MainWindow::setFileName (const QString &fileName)
{
   m_fileName=fileName;
   setWindowTitle(QString("%1[*] - %2").arg(m_fileName.isNull() ? tr("Новый") : QFileInfo(m_fileName).fileName()).arg(QApplication::applicationName()));
}
void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть документ"), QDir::currentPath(), "Text documents (*.txt)");
    if (fileName.isNull())
      return;
    if ((m_fileName.isNull())&&(!isWindowModified()))//??
            loadFile(fileName);
    else
    {
        MainWindow *pNewDoc = new MainWindow();
        pNewDoc->show();
        pNewDoc->loadFile(fileName);
    }
    // при открытии файла в окне и закрытии окна сразу выходит, но так и надо же??
}
bool MainWindow::saveFile()
{
    if (m_fileName.isNull())
    {
        return saveFileAs();
    }
    QFile file(m_fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Файл нельзя открыть"), tr("Ок"), 0, 0, -1);
        setFileName(QString());
        return false;
    }
    else
    {
        QTextStream in(&file);
        in << ui->textEdit->toPlainText();
        file.close();
        setWindowModified(false);
        return true;
    }
    //Слоты не зациклятся, так как поосле первого вызова другого слота, не будут выполняться условия для вызова другого

}
bool MainWindow::saveFileAs()
{
     QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить документ"), m_fileName.isNull() ? QDir::currentPath() : m_fileName, "Text documents (*.txt)");
     if (fileName.isNull())
     {
         return false;
     }
     else
     {
         setFileName(fileName);
         return saveFile();
     }

}
