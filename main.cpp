#include <iostream>
#include "playlist_linked_list.h"
using namespace std;
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <filesystem>

vector<Song> readInCSV(const string& filename) {
    cout << "Happy Boy" << endl;
    vector<Song> Songs;
    ifstream file(filename);
    cout << std::filesystem::current_path() << endl;

    if (!file.is_open()) {
        cout << "Could not open file" << endl;
        return Songs;
    }
    else
    {
        cout << "Reading file" << endl;
    }

    string line;
    getline(file, line);

    cout << line << endl;


    while (getline(file, line)) {
        if (line.empty()) continue;

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

int main() {
    cout << "Hello User, Welcome to CBeats, pick a number from the library below to select a command" << endl;
    int num = 0;
    playlist_linked_list myList;
    while(num != 6){
        cout << "Select a number, if you want to erase your library/stop enter the number 8" << endl;
        cout << "1. addSong 2. removeSong 3. shufflePlaylist 4. playsong 5. moveSong 6. reversePlaylist 7. print playlist" << endl;
        cin >> num;
        switch (num){
            case 1:
                myList.addSong();
                break;
            case 2:
                myList.removeSong();
                break;
            case 3:
                myList.shufflePlaylist();
                break;
            case 4:
                myList.playSong();
                break;
            case 5:
                myList.moveSong();
                break;
            case 6:
                myList.reversePlaylist();
                break;
            case 7: {
                vector<Song> library = readInCSV("Library-simple.csv");
                for (const auto& song : library) {
                    cout << " " << song.title << "-" << song.artist << " (" << song.durationInSeconds << "s)[" << song.genre << "[\n";
                }
                break;
            }
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
    return 0;
}
