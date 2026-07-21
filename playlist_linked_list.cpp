//
// Created by Corey Braswell on 7/13/26.
//

#include "playlist_linked_list.h"
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>

using json = nlohmann::json;
using namespace std;

size_t playlist_linked_list::WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}
// addSong function declaration: Adds a song to the users linked-list-playlist.

void playlist_linked_list::addSong() {

        int item=0;
        string song;
        string artist;
        int songLength;
        string genre;
        cin.ignore();
        string yesNo;

        // Reads in the users input for what song they would like to add to the playlist.
        do {
            bool songAdded = false;
            cout << "What song would you like to add to your playlist?, type no to stop adding songs" << endl;
            getline(cin, song);
            if (song == "no") {
                return;
            }
            cout << "Enter the name of the artist" << endl;
            getline(cin, artist);

            //Creates the song object and goes through the linked list to find the last node and add it after.
            Song* newSong = new Song(song, artist);
            if (head == nullptr) {
                head = newSong;
                cout << "Song added" << endl;
                songAdded = true;
            }
            if (songAdded == false) {
                Song* current = head;

                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newSong;
                newSong->prev = current;
                cout << "Song added to your playlist" << endl;
            }
        } while (song != "no");

}
//Remove Song function: Removes a song from the users playlist linked list.
void playlist_linked_list::removeSong(string SongToRemove) {
    string song = SongToRemove;

    //Test case 1: Playlist is empty
    if (head == nullptr) {
        cout << "Playlist is empty" << endl;
        return;
    }
    // Test case 2: Song = head node
    if (head->title == song) {
        Song* temp = head;
        head = head->next;
        delete temp;
        cout << "Song removed" << endl;
        return;
    }
    //Test Case 3: No Song found
    Song* current = head;
    while (current->next->title != song) {
        current = current->next;
    } if (current->next == nullptr) {
        cout << "Playlist is empty" << endl;
        return;
    }
    // Removes Song
    Song* temp = current->next;
    current->next = temp->next;
    if (temp->next != nullptr) {
        temp->next->prev = current;
    }
    delete temp;
    cout << "song has been removed" << endl;
}
// Shuffle Playlist Function: Shuffles the users linked list playlist by storing it in a vector and then fixing the pointers int eh linekd list.
void playlist_linked_list::shufflePlaylist() {

    // Creates vector and finds length of linked list.
    vector<string> shuffledSongs;
    Song* current = head;
    int count = 0;
    while (current != nullptr) {
        current = current->next;
        count++;
    }
    // pushes songs into vector
    Song* current2 = head;
    for (int i = 0; i < count; i++) {
        shuffledSongs.push_back(current2->title);
        current2 = current2->next;
    }
    //randomizes songs
    random_device rd;
    mt19937 gen(rd());
    shuffle(shuffledSongs.begin(), shuffledSongs.end(), gen);

    for (int i = 0; i < shuffledSongs.size(); i++) {
        cout << shuffledSongs[i] << endl;
    }
    //fixes the pointers in the original linked list.
    current = head;
    int i = 0;
    while (current != nullptr) {
        current->title = shuffledSongs[i];
        current = current->next;
        i++;
    }
}
    /*int count = 0;
    Song* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    for (int i = count; i > 0; i--) {
        int randomIndex = rand() % (i + 1);

        Song* songI
    }
}
*/
//Reverse Playlist function: Reverses the playlist and fixes pointers.
void playlist_linked_list::reversePlaylist() {
    string song;
    Song* current = head;
    Song* tail;
    string temp;
    if (head == nullptr) {
        cout << "Playlist is empty" << endl;
        return;
    }
  //  /*

    while (current != nullptr) {
        song = current->title;
        cout << song << " " << endl;
        tail = current;
        current = current->next;
    }
    cout<< "Reversing Playlist now:" << endl;
    current = tail;

    while (current != nullptr) {
        song = current->title;
        cout << song << " " << endl;
        current = current->prev;
    }

}
//Moves song after any song. If you try to move it behind itself, program will crash.
void playlist_linked_list::moveSong(string songToMove, string songToMovePrev) {
    string songName = songToMove;
    string songNamePrev = songToMovePrev;
    Song* current = head;
    //Retrieves the song from the user


    //Test case 1: Empty playlist
    if (head == nullptr) {
        cout << "Playlist is empty" << endl;
        return;
    }
    while (current != nullptr && current->title != songName) {
        current = current->next;
        }
    //Test Case 2: No song in playlist
    if (current == nullptr) {
            cout << "Song not found" << endl;
            return;
    }
    Song* temp = current;
    //Adjusts pointers to directly change the linked list.
    if (temp == head) {
        head = temp->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
    } else {
        temp->prev->next = temp->next;
        if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
        }
    }

    temp->next = nullptr;
    temp->prev = nullptr;




    current = head;
    while (current != nullptr && current->title != songNamePrev) {
        current = current->next;
    }
        if (current == nullptr) {
            cout << "Song  not found" << endl;
            return;
        }
    Song* afterInsertPoint = current->next; // save before overwriting

    temp->next = afterInsertPoint;
    temp->prev = current;

    if (afterInsertPoint != nullptr) {
        afterInsertPoint->prev = temp;
    }
    current->next = temp;
}

void playlist_linked_list::playSong(string songToPlay) {



    // Build the search URL, replacing spaces with '+' for a valid URL
    string query = songToPlay;
    for (auto& c : query) if (c == ' ') c = '+';
    string url = "https://itunes.apple.com/search?term=" + query + "&entity=song&limit=1";

    // Set up curl to fetch the search results
    CURL* curl = curl_easy_init();
    string readBuffer;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            cout << "Failed to reach iTunes: " << curl_easy_strerror(res) << endl;
            return;
        }

        // Parse the JSON response
        json data = json::parse(readBuffer, nullptr, false);  // false = don't throw on bad JSON

        if (data.is_discarded()) {
            cout << "Failed to parse response." << endl;
            return;
        }

        if (data["results"].empty()) {
            cout << "No results found for \"" << songToPlay << "\"." << endl;
            return;
        }

        string previewUrl = data["results"][0]["previewUrl"];
        string trackName = data["results"][0]["trackName"];
        string artistName = data["results"][0]["artistName"];

        cout << "Playing preview: " << trackName << " by " << artistName << endl;

        string command = "open \"" + previewUrl + "\"";
        system(command.c_str());
    } else {
        cout << "Failed to initialize curl." << endl;
    }
    /*string query = songName;
    for (auto& c : query) if (c == ' ') c = '+';

    string command = "open \"https://www.youtube.com/results?search_query=" + query + "\"";
    system(command.c_str());*/
}
    void playlist_linked_list::printPlaylist() {
        Song* current = head;
        while (current != nullptr) {
            cout << left << setw(30) << current->title << left << setw(20) << current->artist << endl;
            current = current->next;
        }
    }



playlist_linked_list::playlist_linked_list() {
    head = nullptr;

}



vector<Song> playlist_linked_list::readInCSV(const string& filename) {

    int item =1; // index counter for each song in library

    vector<Song> Songs;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open file" << endl;
        return Songs;
    }
    else
    {
        cout << "Working Directory: " << filesystem::current_path() << endl;
        cout << "Opening file" << endl;
        cout << "Opening CSV" << filename << endl;
        cout << filesystem::current_path() << endl;

    }


    string line;
    getline(file, line);

    //cout << line << endl; // debug line, display file contents; unparsed

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        stringstream ss(line);
        string title, artist, durationInSeconds, genre;

        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, durationInSeconds, ',');
        getline(ss, genre, ',');

        int duration = stoi(durationInSeconds);

        Songs.push_back(Song(title, artist));
        item++;
    }
    file.close();
    return Songs;
}

void playlist_linked_list::printLibrary(const vector<Song>& Songs) {

    if (Songs.empty()) {
        cout << "No songs to display." << endl;
        return;
    }
    cout << left
         << setw(30) << "Title"
         << setw(20) << "Artist"
         << setw(10) << "Duration"
         << setw(10) << "Genre"
         << endl;

    for (const auto& Song : Songs) {
        cout << left
             << setw(30) << Song.title
             << setw(20) << Song.artist
             << endl;
    }



}

/*void playlist_linked_list::saveData(string filename) {
    ofstream file(filename);
    Song* current = head;
    while (current != nullptr) {
        file << left << setw(20) << current->title << "," << left << setw(15) << current->artist << endl;
        current = current->next;
    }
    file.close();
}

void playlist_linked_list::loadData(string filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string title, artist;
        getline(ss, title, ',');
        getline(ss, artist, ',');

        addSong();

    }
}
*/

/*void playlist_linked_list::playSong(vector<Song>& library) {

    string songToPlay;
    string yn;
    cout << "If you would like to access the CBeats automated playlist type 'yes', if you would like to access your own type 'no'" << endl;
    cin.ignore();
    getline(cin, yn);

    if (yn == "yes") {
        //CBeatslist.printLibrary(library);
        printLibrary(library);
    } else if (yn == "no") {
        //myList.printPlaylist();
        printPlaylist();
    }
    else {
        cout << "statement not valid" << endl;
        return;
    }
    cout << "Pick a song from above:" << endl;
    getline(cin, songToPlay);
    //songToPlay = playSong[25].title;



    // Build the search URL, replacing spaces with '+' for a valid URL
    string query = songToPlay;
    for (auto& c : query) if (c == ' ') c = '+';
    string url = "https://itunes.apple.com/search?term=" + query + "&entity=song&limit=1";

    // Set up curl to fetch the search results
    CURL* curl = curl_easy_init();
    string readBuffer;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            cout << "Failed to reach iTunes: " << curl_easy_strerror(res) << endl;
            return;
        }

        // Parse the JSON response
        json data = json::parse(readBuffer, nullptr, false);  // false = don't throw on bad JSON

        if (data.is_discarded()) {
            cout << "Failed to parse response." << endl;
            return;
        }

        if (data["results"].empty()) {
            cout << "No results found for \"" << songToPlay << "\"." << endl;
            return;
        }

        string previewUrl = data["results"][0]["previewUrl"];
        string trackName = data["results"][0]["trackName"];
        string artistName = data["results"][0]["artistName"];

        cout << "Playing preview: " << trackName << " by " << artistName << endl;

        string command = "open \"" + previewUrl + "\"";
        system(command.c_str());
    } else {
        cout << "Failed to initialize curl." << endl;
    }
    string query = songName;
    for (auto& c : query) if (c == ' ') c = '+';

    string command = "open \"https://www.youtube.com/results?search_query=" + query + "\"";
    system(command.c_str());
    }*/
