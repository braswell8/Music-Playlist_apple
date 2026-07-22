//
// Created by Corey Braswell on 7/21/26.
//

#ifndef UNTITLED_MAINWINDOW_H
#define UNTITLED_MAINWINDOW_H

#include <QMainWindow>
#include "playlist_linked_list.h"
#include "Song.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    vector<Song> library;
    playlist_linked_list playlist;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_LoadInCSV_clicked();
    void on_AddSong_clicked();
    void on_PlaySongButton_clicked();
    void on_RSongButton_clicked();
    //void on_MoveSongButton_clicked();
    void on_LibrarySearchBar_textChanged(const QString &text);
    void on_PlaylistSearchBar_textChanged(const QString &text);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
