#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "artistdialog.h"
#include"albumdialog.h"
#include"item.h"
#include<QPoint>
#include<QAction>
#include<QMenu>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->action_delete->setEnabled(false);
    ui->action_new_song->setEnabled(false);
    ui->action_new_album->setEnabled(false);

     connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(positionofelement(QModelIndex)));
     connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(setWindow_Modified()));

     model = new MusicModel();
     const int RatingColumn = 2;
     RatingDelegate *delegate = new RatingDelegate(ui->treeView);
     setWindowTitle(QString("%1[*] ­ %2").arg(curFile.isNull()?"Музыкальная коллекция":QFileInfo(curFile).fileName()).arg(QApplication::applicationName()));
     ui->treeView->setModel(model);
     ui->treeView->setItemDelegateForColumn(RatingColumn, delegate);

}
MainWindow::~MainWindow()
{
    delete ui;
}

QTreeView *MainWindow::view() const
{
    return ui->treeView;
}

    void MainWindow::setWindow_Modified()
    {
        setWindowModified(true);
    }


    void MainWindow::loadFile(const QString &fileName)
    {


        delete model->m_root;
        model->m_root = new Item();
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this,tr("Ошибка"),tr("Невозможно открыть файл "));
            return;
        }
        curFile=fileName;
        QDataStream stream(&file);
        int c_art;
        int c_alb;
        int c_song;
        stream >> c_art;
        for(int i=0; i<c_art; ++i)
        {
            Artist *art = new Artist();
                stream >> *art;
                stream >> c_alb;
                for(int j=0; j<c_alb; ++j)
                {
                    Album *alb = new Album();
                        stream >> *alb;
                        stream >> c_song;
                        for(int k=0; k<c_song; ++k)
                        {
                            Song *sng = new Song();
                                stream >> *sng;
                                alb->insertChild(sng,k);
                        }
                        art->insertChild(alb,j);
                }
                model->m_root->insertChild(art,i);
        }

        qDebug() << model->m_root->childCount();
        setWindowTitle(QString("%1[*] ­ %2").arg(curFile.isNull()?"Музыкальная коллекция":QFileInfo(curFile).fileName()).arg(QApplication::applicationName()));

    file.close();
    ui->treeView->setModel(model);
    ui->treeView->reset();
    }

    void MainWindow::closeEvent(QCloseEvent *e)
    {
        if(isWindowModified())

        {
                switch(QMessageBox::warning(this,tr("Документ изменен."),tr("Вы хотите сохранить документ?"),
                                            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                            QMessageBox::No))
                {
                case QMessageBox::Yes:
                    e->accept();
                    if(saveFileAs())
                    {  e->accept();}
               else{ e->ignore();}
               break;
              case QMessageBox::No:
                e->accept();
                    break;
            case QMessageBox::Cancel:
                e->ignore();
                    break;
                }
        }
        else {e->accept();}
    }


    void MainWindow::on_action_Save_As_triggered()
    {
         saveFileAs();
    }

    void MainWindow::on_action_Save_triggered()
    {


       saveFile();
    }

    bool MainWindow::saveFile()
    {
        if(curFile.isNull())
        {
            return saveFileAs();

        }
      else
        {
        QFile file(curFile);

            if(!file.open(QIODevice::WriteOnly))
            {
                QMessageBox::warning(this, tr("%1").arg(this->windowTitle()),
                                     tr("Не удается сохранить"));

             return false;
            }

             else{



                    QDataStream stream(&file);

                    stream << *model->m_root;

                    if(stream.status() != QDataStream::Ok)
                    {
                        qDebug() << "Ошибка записи";
                    }
                    else setWindowModified(false);
                }

                setWindowModified(false);
                setWindowTitle(QString("%1[*] ­ %2").arg(curFile.isNull()?"Музыкальная коллекция":QFileInfo(curFile).fileName()).arg(QApplication::applicationName()));
                file.close();
                return true;

           }
        }


    bool MainWindow::saveFileAs()
    {
        QString fileName = QFileDialog::getSaveFileName(this,"Сохранить документ",curFile.isNull()?QDir::currentPath():curFile,"Text documents(*.txt)");
         if(!fileName.isEmpty())
          {
         curFile=fileName;
         return saveFile();
         }
         return false;
    }

    void MainWindow::on_action_open_triggered()
    {
        QString fileName= QFileDialog::getOpenFileName(this,"Открыть файл",QDir::currentPath(),"Text documents(*.txt)");
       if(!fileName.isEmpty())
        {

       loadFile(fileName);
         }
    }
    void MainWindow::positionofelement(QModelIndex index)
    {
        Item *item=static_cast<Item*>(index.internalPointer());
            if(item->toAlbum())
            {

                //ui->action_show_properties->setEnabled(true);
                ui->action_delete->setEnabled(true);
                ui->action_new_song->setEnabled(true);
                ui->action_new_album->setEnabled(false);

            }
            if(item->toArtist())
            {
                //ui->action_show_properties->setEnabled(true);
                ui->action_delete->setEnabled(true);
                ui->action_new_album->setEnabled(true);
                ui->action_new_song->setEnabled(false);
            }
            if(item->toSong())
            {

                //ui->action_show_properties->setEnabled(false);
                ui->action_delete->setEnabled(true);
                ui->action_new_album->setEnabled(false);
                ui->action_new_song->setEnabled(false);
            }
    }


void MainWindow::on_action_new_artist_triggered()
{
    model->insertRows(model->m_root->childCount(), 1, QModelIndex());
    ArtistDialog *artist = new ArtistDialog();
    artist->setModel(model);
    artist->setModelIndex(model->index(model->m_root->childCount()-1,0,QModelIndex()));
    artist->show();
    setWindowModified(true);
}

void MainWindow::on_action_new_album_triggered()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    Item *item=static_cast<Item*>(index.internalPointer());
    model->insertRows(item->childCount(), 1, index);
    AlbumDialog *album = new AlbumDialog();
    album->setModel(model);
    album->setModelIndex(model->index(item->childCount()-1,0,index));
    album->show();
    setWindowModified(true);
}


void MainWindow::on_action_new_song_triggered()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    Item *item=static_cast<Item*>(index.internalPointer());
    model->insertRows(item->childCount(), 1, index);
    TrackDialog *song = new TrackDialog();
    song->setModel(model);
    song->setModelIndex(model->index(item->childCount()-1,0,index));
    song->show();
    setWindowModified(true);

}
/*void MainWindow::on_action_new_song_triggered()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeView->model();
    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }


    if (!model->insertRow(index.row(), index))
        return;


    ui->treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                                QItemSelectionModel::ClearAndSelect);
}*/

void MainWindow::on_action_delete_triggered()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QModelIndex parent = index.parent();
    Item *item=static_cast<Item*>(index.internalPointer());
    model->removeRows(item->parent()->indexOf(item),1,parent);
    setWindowModified(true);
}




void MainWindow::on_action_show_properties_triggered()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    Item *item=static_cast<Item*>(index.internalPointer());
        if(item->toAlbum())
        {
                AlbumDialog *album = new AlbumDialog();
                album->setModel(model);
                album->setModelIndex(index);
                album->show();
        }
        if(item->toArtist())
        {
                ArtistDialog *artist = new ArtistDialog();
                artist->setModel(model);
                artist->setModelIndex(index);
                artist->show();
        }
}
