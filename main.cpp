#include <iostream>
#include "playlist_linked_list.h"
using namespace std;
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <iomanip> //MB added

int main() {
    cout << "Hello User, Welcome to CBeats, pick a number from the library below to select a command" << endl;
    int num = 0;
    playlist_linked_list myList;
    playlist_linked_list playlist;
    vector<Song> library = playlist.readInCSV("Library-Genre.csv");

    while(num != 6) {
        cout << "Select a number, if you want to erase your library/stop enter the number 8" << endl;
        cout << "1. addSong 2. removeSong 3. shufflePlaylist 4. playsong 5. moveSong 6. reversePlaylist 7. print automated CBeats library" << endl;
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
                {
                string yn;
                cout << "If you would like to access the CBeats automated playlist type 'yes', if you would like to access your own type 'no'" << endl;
                cin.ignore();
                getline(cin, yn);
                if (yn == "yes") {
                    playlist.printLibrary(library);
                } else if (yn == "no") {
                    myList.printPlaylist();
                }
                else {
                    cout << "statement not valid" << endl;
                    break;
                }
                cout << "Pick a song from above:" << endl;
                myList.playSong();
                break;
        }
            case 5:
                myList.moveSong();
                break;
            case 6:
                myList.reversePlaylist();
                break;
            case 7: {
                playlist.printLibrary(library);
                break;
            }
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
    return 0;
}
