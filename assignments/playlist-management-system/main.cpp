#include <iostream>
#include <string>
using namespace std;

// Node structure to represent each song in the playlist
struct SongNode {
    int songID;
    string title;
    string artist;
    SongNode* next;
    SongNode* prev;

    // Constructor
    SongNode(int id, string t, string a) : songID(id), title(t), artist(a), next(nullptr), prev(nullptr) {}
};

// Playlist Class (Doubly Linked List)
class Playlist {
    SongNode* head;
    SongNode* tail;

public:
    // Constructor
    Playlist() : head(nullptr), tail(nullptr) {}

    // Destructor  when playlist is destroyed
    ~Playlist() {
        SongNode* current = head;
        while (current != nullptr) {
            SongNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr; // Ensure pointers are reset
    }

    // add a song to the end of the playlist
    void addSong(int id, string title, string artist) {
        SongNode* newSong = new SongNode(id, title, artist);

        if (tail == nullptr) { // the playlist is empty
            head = tail = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }

        cout << "Song added: " << title << " by " << artist << endl;
    }

    void removeSong(int id) {
        SongNode* current = head;

        while (current != nullptr) {
            if (current->songID != id) {
                continue;
            }
            // If the song is in the head
            if (current == head) {
                head = current->next;
                if (head != nullptr) head->prev = nullptr;
                else tail = nullptr;
            }
            // If the song is at the tail
            else if (current == tail) {
                tail = current->prev;
                if (tail != nullptr) tail->next = nullptr;
            }
            // If is in the middle
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            cout << "Song removed: " << current->title << " by " << current->artist << endl;
            delete current;
            return;
        } 
        current = current->next;
    
        cout << "Song with ID " << id << " not found!" << endl;
    }

    void displayPlaylist() const {
        if (head == nullptr) {
            cout << "The playlist is empty!" << endl;
            return;
        }
        SongNode* current = head;
        cout << "Playlist: " << endl;
        while (current != nullptr) {
            cout << current->songID << ": " << current->title << " by " << current->artist << endl;
            current = current->next;
        }
    }

    void displayReversePlaylist() const {
        if (tail == nullptr) {
            cout << "The playlist is empty!" << endl;
            return;
        }
        SongNode* current = tail;
        cout << "Playlist in reverse: " << endl;
        while (current != nullptr) {
            cout << current->songID << ": " << current->title << " by " << current->artist << endl;
            current = current->prev;
        }
    }

    SongNode* searchSong(int id) const {
        SongNode* current = head;

        while (current != nullptr) {
            if (current->songID == id) {
                cout << "Song found: " << current->title << " by " << current->artist << endl;
                return current;
            }
            current = current->next;
        }
        cout << "Song with ID " << id << " not found!" << endl;
        return nullptr;
    }
};

// Main function to simulate the playlist management system
int main() {
    Playlist playlist;
    int choice, id;
    string title, artist;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Song\n";
        cout << "2. Remove Song\n";
        cout << "3. Display Playlist\n";
        cout << "4. Display Reverse Playlist\n";
        cout << "5. Search Song\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        // if the string is not removed it will loop forever
        switch (choice) {
            case 1:
                cout << "Enter song ID: ";
                cin >> id;
                if (cin.fail() || id <= 0) {
                    cin.clear();
                    string invalid_input;
                    cin >> invalid_input;
                    cout << "Invalid ID. It should be a positive int.\n";
                    break;
                } // i added this checks cause it was crashing if not
                cout << "Enter song title: ";
                cin.ignore(); // To handle the newline character from previous input
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist);
                playlist.addSong(id, title, artist);
                break;
            case 2:
                cout << "Enter song ID to remove: ";
                cin >> id;
                if (id <= 0) {
                    cout << "Invalid ID. It should be a positive int.\n";
                    break;
                }
                playlist.removeSong(id);
                break;
            case 3:
                playlist.displayPlaylist();
                break;
            case 4:
                playlist.displayReversePlaylist();
                break;
            case 5:
                cout << "Enter song ID to search: ";
                cin >> id;
                if (id <= 0) {
                    cout << "Invalid ID. It should be a positive int.\n";
                    break;
                }
                playlist.searchSong(id);
                break;
            case 0:
                cout << "Exiting Playlist Management System.\n";
                break;
            default:
                cout << "Invalid choice! Please select a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}
