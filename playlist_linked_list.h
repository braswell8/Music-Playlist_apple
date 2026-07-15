//
// Created by Corey Braswell on 7/13/26.
//

#ifndef UNTITLED_LINKEDLIST_H
#define UNTITLED_LINKEDLIST_H
#include <iostream>
#include "Song.h"
using namespace std;

class playlist_linked_list {

    private:
        Song* head;
    public:

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output);
    playlist_linked_list();
    void addSong();
    void removeSong();
    void shufflePlaylist();
    void moveSong();
    void reversePlaylist();
    void playSong();
    void printPlaylist();
    vector<Song> readInCSV(const string& filename);
    void printLibrary(const vector<Song>& Songs);


        //static void addToQueue();
    //void playPreviousSong();

};

#endif //UNTITLED_LINKEDLIST_H
