/*#include <iostream>
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
        cout << "1. addSong " << endl;
        cout << "2. removeSong " << endl;
        cout << "3. shufflePlaylist " << endl;
        cout << "4. playSong " << endl;
        cout << "5. moveSong " << endl;
        cout << "6. reversePlaylist " << endl;
        cout << "7. print automated CBEATS library " << endl;
        cout << "8. printPlaylist " << endl;
        cout << "9. exit" << endl;

        cin >> num;
        if (num >= 1 && num <= 9) {
            switch (num){
                case 1: {
                    myList.addSong();
                    break;
                }
                case 2: {
                    myList.removeSong();
                    break;
                }
                case 3: {
                    myList.shufflePlaylist();
                    break;
                }
                case 4:
                {
                    myList.playSong(library);
                    break;
                }
                case 5: {
                    myList.printPlaylist();
                    myList.moveSong();
                    break;
                }
                case 6: {
                    myList.reversePlaylist();
                    break;
                }
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
*/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}