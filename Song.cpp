//
// Created by Corey Braswell on 7/13/26.
//

#include "Song.h"
using namespace std;

Song::Song(string t, string a, int d, string g) {
    title = t;
    artist = a;
    durationInSeconds = d;
    next = nullptr;
    prev = nullptr;
    genre = g;
}