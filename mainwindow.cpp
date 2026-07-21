//
// Created by Corey Braswell on 7/21/26.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoadInCSV_clicked() {

    library = playlist.readInCSV("Library-Genre.csv");

    for (const Song& song : library)
    {
        ui->LibraryList->addItem(
            QString::fromStdString(song.title + " - " + song.artist)
        );
    }
}

void MainWindow::on_AddSong_clicked() {

    QListWidgetItem* selectedSong = ui->LibraryList->currentItem();

    if (selectedSong == nullptr)
    {
        return;
    }

    QString songName = selectedSong->text();

    ui->PlayList->addItem(songName);
}

void MainWindow::on_PlaySongButton_clicked() {
    QListWidgetItem* selectedSong = ui->PlayList->currentItem();
    if (selectedSong == nullptr)
    {
        return;
    }
    QString songName = selectedSong->text();

    playlist.playSong(songName.toStdString());
}

void MainWindow::on_RSongButton_clicked() {

    QListWidgetItem* selectedSong = ui->PlayList->currentItem();
    if (selectedSong == nullptr) {
        return;
    }
    QString songName = selectedSong->text();

    playlist.removeSong(songName.toStdString());

    // Remove from the QListWidget itself
    int row = ui->PlayList->row(selectedSong);
    ui->PlayList->takeItem(row);
    delete selectedSong;
}

/*void MainWindow::on_MoveSongButton_clicked() {
    QListWidgetItem* selectedSong = ui->PlayList->currentItem();
    if (selectedSong == nullptr)
        return;
    QString songName = selectedSong->text();
    playlist.moveSong(songName.toStdString(), );

}
*/



