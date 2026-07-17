#include <iostream>
#include "playlist_linked_list.h"
using namespace std;
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <iomanip> //MB added to allow screen formatting

int main() {
    int num = 0;
    string songToPlay;
    playlist_linked_list myList;
    playlist_linked_list CBeatslist;
    vector<Song> library = CBeatslist.readInCSV("Library-Genre.csv");


    cout << endl << endl;
    cout << "Hello User, Welcome to CBeats, pick a number from the options below to select a command" << endl;
    cout << endl << endl;


    while(num != 6) {
        cout << "Select a number, if you want to erase your library/stop enter the number 9" << endl;
        cout << "1. addSong 2. removeSong 3. shufflePlaylist 4. playsong 5. moveSong 6. reversePlaylist 7. print automated CBeats library, 8. printYourPlaylist, 9. exit program" << endl;
        cin >> num;
        if (num >= 1 && num <= 9) {
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
                    myList.playSong(library);
                    break;
                }
                case 5:
                    myList.printPlaylist();
                    myList.moveSong();
                    break;
                case 6:
                    myList.reversePlaylist();
                    break;
                case 7: {
                    CBeatslist.printLibrary(library);
                    break;
                }
                case 8: {
                    myList.printPlaylist();
                    break;
                }
                case 9: {
                    cout << "Exiting Program" << endl;
                    return 0;
                }
                default:
                    cout << "Invalid option. Please try again." << endl;
                    break;
            }
        }
        else {
            cout << "Invalid option. Please try again." << endl;
        }
    }
    return 0;
}
