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
    string song;
    string artist;
    int songLength;
    string genre;

    cin.ignore();

    cout << "What song would you like to add to your playlist?" << endl;
    getline(cin, song);


    cout << "Enter the name of the artist" << endl;
    getline(cin, artist);

    cout << "Enter the length in seconds of the song" << endl;
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

    cin.ignore();

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
    int count = 0;
    string song;
    Song* current = head;
    if (head == nullptr) {
        cout << "Playlist is empty" << endl;
        return;
    }
    while (current->next != nullptr) {
        count++;
        current = current->next;
    }
    song = current->title;
    cout << song << " " << count << endl;
    count--;

    while (current != head) {
        song = current->title;
        cout << song << " " << count << endl;
        count--;
        current = current->prev;
    }
    song = head->title;
    cout << song << endl;
}

void playlist_linked_list::moveSong() {

}
void playlist_linked_list::playSong() {
    string songName; /*
    cin.ignore();
    cout << "What song would you like to play from your playlist below?" << endl;
    Song* current = head;
    while (current != nullptr) {
        cout << current->title << " " << current->artist << " " << current->durationInSeconds << endl;
        current = current->next;
    }
    */
    getline(cin, songName);

    // Build the search URL, replacing spaces with '+' for a valid URL
    string query = songName;
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
            cout << "No results found for \"" << songName << "\"." << endl;
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
            cout << setw(30) << current->title << setw(20) << current->artist << endl;
            current = current->next;
        }
    }



playlist_linked_list::playlist_linked_list() {
    head = nullptr;

}



vector<Song> playlist_linked_list::readInCSV(const string& filename) {
    cout << "Opening CSV" << filename << endl;
    vector<Song> Songs;
    ifstream file(filename);
    cout << filesystem::current_path() << endl;

    if (!file.is_open()) {
        cout << "Could not open file" << endl;
        return Songs;
    }
    else
    {
        cout << "Working Directory: " << filesystem::current_path() << endl;
        cout << "Opening file" << endl;
    }



    string line;
    getline(file, line);

    cout << line << endl;

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
        cout << title;

        int duration = stoi(durationInSeconds);

        Songs.push_back(Song(title, artist, duration, genre));
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
             << setw(10) << Song.durationInSeconds
             << setw(10) << Song.genre
             << endl;
    }



}
