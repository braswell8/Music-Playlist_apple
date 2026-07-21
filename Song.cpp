//
// Created by Corey Braswell on 7/13/26.
//

#include "Song.h"
using namespace std;


Song::Song(string t, string a) {

    title = t;
    artist = a;


    next = nullptr;
    prev = nullptr;

}