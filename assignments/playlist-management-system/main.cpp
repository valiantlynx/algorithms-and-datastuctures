#include <iostream>
#include <string>
using namespace std;

// Node structure for doubly linked list
struct Node {
    int id;
    string title;
    string artist;
    Node* next;
    Node* prev;
};

// Playlist class implementing a doubly linked list
class Playlist {
private:
    Node* head;
    Node* tail;

public:
    Playlist() {
        head = nullptr;
        tail = nullptr;
    }

    // Add a new song at the end of the playlist
    void addSong(int id, string title, string artist) {
        Node* newNode = new Node();
        newNode->id = id;
        newNode->title = title;
        newNode->artist = artist;
        newNode->next = nullptr;
        newNode->prev = tail;

        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        cout << "Song added: " << title << " by " << artist << endl;
    }

    // Remove a song from the playlist by ID
    void removeSong(int id) {
        Node* current = head;

        while (current != nullptr) {
            if (current->id == id) {
                if (current == head) {
                    head = current->next;
                    if (head != nullptr) {
                        head->prev = nullptr;
                    }
                } else if (current == tail) {
                    tail = current->prev;
                    if (tail != nullptr) {
                        tail->next = nullptr;
                    }
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                delete current;
                cout << "Song with ID " << id << " removed." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Song with ID " << id << " not found." << endl;
    }

    // Display the playlist in forward order
    void displayPlaylist() {
        Node* current = head;
        if (!current) {
            cout << "Playlist is empty." << endl;
            return;
        }

        cout << "Playlist: " << endl;
        while (current != nullptr) {
            cout << "ID: " << current->id << " | Title: " << current->title << " | Artist: " << current->artist << endl;
            current = current->next;
        }
    }

    // Display the playlist in reverse order
    void displayReversePlaylist() {
        Node* current = tail;
        if (!current) {
            cout << "Playlist is empty." << endl;
            return;
        }

        cout << "Playlist in reverse order: " << endl;
        while (current != nullptr) {
            cout << "ID: " << current->id << " | Title: " << current->title << " | Artist: " << current->artist << endl;
            current = current->prev;
        }
    }

    // Search for a song by ID
    void searchSong(int id) {
        Node* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                cout << "Song found: " << current->title << " by " << current->artist << endl;
                return;
            }
            current = current->next;
        }
        cout << "Song with ID " << id << " not found." << endl;
    }

    // Destructor to clean up the allocated memory
    ~Playlist() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        cout << "Playlist destroyed." << endl;
    }
};

// Main function with menu-driven interface
int main() {
    Playlist playlist;
    int choice, id;
    string title, artist;

    do {
        cout << "\nPlaylist Management System\n";
        cout << "1. Add a new song\n";
        cout << "2. Remove a song by ID\n";
        cout << "3. Display the playlist\n";
        cout << "4. Display the playlist in reverse order\n";
        cout << "5. Search for a song by ID\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Song ID: ";
                cin >> id;
                cout << "Enter Song Title: ";
                cin.ignore();  // Ignore the newline left in the input stream
                getline(cin, title);
                cout << "Enter Artist Name: ";
                getline(cin, artist);
                playlist.addSong(id, title, artist);
                break;

            case 2:
                cout << "Enter Song ID to remove: ";
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
                cout << "Enter Song ID to search: ";
                cin >> id;
                playlist.searchSong(id);
                break;

            case 6:
                cout << "Exiting Playlist Management System." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
