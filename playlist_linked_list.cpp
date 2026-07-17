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

using json = nlohmann::json;
using namespace std;

size_t playlist_linked_list::WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void playlist_linked_list::addSong() {
    int item=0;
    string song;
    string artist;
    int songLength;
    string genre;
    cin.ignore();
    cout << "What song would you like to add to your playlist?" << endl;
    getline(cin, song);

    cout << "Enter the name of the artist" << endl;
    getline(cin, artist);

    cout << "Enter the length of the song" << endl;
    cin >> songLength;

    cin.ignore();

    cout << "Enter the genre of the song" << endl;
    getline(cin, genre);

    Song* newSong = new Song(song, artist, songLength, genre);
    if (head == nullptr) {
        head = newSong;
        cout << "Song added" << endl;
        return;
    }
    Song* current = head;

    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newSong;
    newSong->prev = current;
    cout << "Song added to your playlist" << endl;

}

void playlist_linked_list::removeSong() {
    string song;


    cout << "What song would you like to remove?" << endl;

    getline(cin, song);

    if (head == nullptr) {
        cout << "Playlist is empty" << endl;
        return;
    }
    if (head->title == song) {
        Song* temp = head;
        head = head->next;
        delete temp;
        cout << "Song removed" << endl;
        return;
    }
    Song* current = head;
    while (current->next->title != song) {
        current = current->next;
    } if (current->next == nullptr) {
        cout << "Playlist is empty" << endl;
        return;
    }
    Song* temp = current->next;
    current->next = temp->next;
    if (temp->next != nullptr) {
        temp->next->prev = current;
    }
    delete temp;
    cout << "song has been removed" << endl;
}

void playlist_linked_list::shufflePlaylist() {
    cout << "Coming Soon" << endl;
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

void playlist_linked_list::moveSong() {
    string songName;
    string songNamePrev;
    Song* current = head;
    cin.ignore();
    cout << "What song would you like to move?" << endl;
    getline(cin, songName);
    cout << "What song would you like to move it after?" << endl;
    getline(cin, songNamePrev);

    if (head == nullptr) {
        cout << "Playlist is empty" << endl;
        return;
    }
    while (current != nullptr && current->title != songName) {
        current = current->next;
        }

    if (current == nullptr) {
            cout << "Song not found" << endl;
            return;
    }
    Song* temp = current;

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

//void playlist_linked_list::playSong(const string songToPlay,  vector<Song> & library) {
void playlist_linked_list::playSong(vector<Song>& library) {

    string songToPlay;

    /*
    cin.ignore();
    cout << "What song would you like to play from your playlist below?" << endl;
    Song* current = head;
    while (current != nullptr) {
        cout << current->title << " " << current->artist << " " << current->durationInSeconds << endl;
        current = current->next;
    }
    */
    //getline(cin, songName);
   // songName = playList[25].title;

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
        //cout << "Opening CSV" << filename << endl;
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
        //cout << title;

        int duration = stoi(durationInSeconds);

        Songs.push_back(Song(title, artist, duration, genre));
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
         //<< setw(10) << "Index"
         << setw(30) << "Title"
         << setw(20) << "Artist"
         << setw(10) << "Duration"
         << setw(10) << "Genre"
         << endl;

    for (const auto& Song : Songs) {
        cout << left
            //<< setw(10) << Song.item
             << setw(30) << Song.title
             << setw(20) << Song.artist
             << setw(10) << Song.durationInSeconds
             << setw(10) << Song.genre
             << endl;
    }



}

void playlist_linked_list::saveData(string filename) {
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
