#### Playlist Management System

**Description:**
This is a simple playlist management system implemented in C++ using a Doubly Linked List (DLL). Each song in the playlist is represented by a node containing the song ID, title, and artist. The system allows users to perform the following operations:

- **Add a Song:** Insert a new song at the end of the playlist.
- **Remove a Song:** Delete a song by providing its unique ID.
- **Display Playlist:** Show all songs in the playlist in forward order.
- **Display Reverse Playlist:** Show all songs in reverse order.
- **Search Song:** Find a song by its unique ID.

**Features:**

- **Doubly Linked List:** Allows efficient traversal in both directions.
- **Memory Management:** Ensures proper allocation and deallocation of memory when adding or removing songs.
- **Menu-Driven Interface:** The user is prompted with options to interact with the playlist.

**How It Works:**
1. **Add Song:** When a new song is added, it's inserted at the end of the doubly linked list.
2. **Remove Song:** The system searches for the song by its ID, and removes it from the appropriate position (beginning, middle, or end) in the list.
3. **Display Playlist:** Traverses the playlist from the head to the tail, showing song details.
4. **Reverse Display:** Traverses the playlist from the tail to the head, showing song details in reverse.
5. **Search Song:** Searches through the playlist to find a song by its ID.

**Usage:**
Compile and run the program using any C++ compiler. The user will be presented with a menu to add, remove, display, and search for songs in the playlist.

#### Files:
- `playlist.cpp`: The main source file containing the Playlist Management System implementation.
- `README.md`: This file, describing the system, its features, and usage instructions.

