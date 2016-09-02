#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include "ratingdelegate.h"
#include "albumdialog.h"
#include "artistdialog.h"
#include "item.h"
#include "trackdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MusicModel *model;
    QTreeView* view()const;
    void positionofelement(QModelIndex index);
    void setWindow_Modified();

protected:
    void closeEvent(QCloseEvent *e);

private slots:

    void on_action_new_artist_triggered();
    void on_action_new_album_triggered();
    void on_action_new_song_triggered();
    void on_action_delete_triggered();
    void loadFile(const QString &fileName);
    void on_action_Save_As_triggered();
    void on_action_Save_triggered();
    void on_action_open_triggered();
    void on_action_show_properties_triggered();

private:
    Ui::MainWindow *ui;
    QString curFile;
    bool saveFile();
    bool saveFileAs();

};

#endif // MAINWINDOW_H
