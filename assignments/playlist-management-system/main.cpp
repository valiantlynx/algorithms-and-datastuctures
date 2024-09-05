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

    // Constructor to initialize a song node
    SongNode(int id, string t, string a) : songID(id), title(t), artist(a), next(nullptr), prev(nullptr) {}
};

// Class to represent the Playlist (Doubly Linked List)
class Playlist {
    SongNode* head;
    SongNode* tail;

public:
    // Constructor to initialize the playlist
    Playlist() : head(nullptr), tail(nullptr) {}

    // Destructor to free memory when the playlist is destroyed
    ~Playlist() {
        SongNode* current = head;
        while (current != nullptr) {
            SongNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Function to add a song to the end of the playlist
    void addSong(int id, string title, string artist) {
        SongNode* newSong = new SongNode(id, title, artist);

        if (tail == nullptr) { // If the playlist is empty
            head = tail = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }

        cout << "Song added: " << title << " by " << artist << endl;
    }

    // Function to remove a song by its ID
    void removeSong(int id) {
        SongNode* current = head;

        while (current != nullptr) {
            if (current->songID == id) {
                // If the song is found at the head
                if (current == head) {
                    head = current->next;
                    if (head != nullptr) head->prev = nullptr;
                    else tail = nullptr; // If list becomes empty
                }
                // If the song is found at the tail
                else if (current == tail) {
                    tail = current->prev;
                    if (tail != nullptr) tail->next = nullptr;
                }
                // If the song is in the middle
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                cout << "Song removed: " << current->title << " by " << current->artist << endl;
                delete current;
                return;
            }
            current = current->next;
        }
        cout << "Song with ID " << id << " not found!" << endl;
    }

    // Function to display the playlist from start to end
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

    // Function to display the playlist in reverse order
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

    // Function to search for a song by its ID
    void searchSong(int id) const {
        SongNode* current = head;

        while (current != nullptr) {
            if (current->songID == id) {
                cout << "Song found: " << current->title << " by " << current->artist << endl;
                return;
            }
            current = current->next;
        }
        cout << "Song with ID " << id << " not found!" << endl;
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

        switch (choice) {
            case 1:
                cout << "Enter song ID: ";
                cin >> id;
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
