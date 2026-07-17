//
// Created by Corey Braswell on 7/13/26.
//

#ifndef UNTITLED_SONG_H
#define UNTITLED_SONG_H
#include <__fwd/string.h>
#include <string>
using namespace std;

class Song {
public:

    //int item;
    string title;
    string artist;
    int durationInSeconds;
    string genre;

 //   Song(int i, string t, string a, int d, string g);
    Song(string t, string a, int d, string g);


    Song* next;
    Song* prev;

};


#endif //UNTITLED_SONG_H
