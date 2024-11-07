# DS-Assg-3
# Player and Game Management System

It binary search trees (BST) to store and manage player and game data. It includes features like adding, searching, and deleting players and games. Additionally, reading and writing player and game data from/to files.

## Features

- **Player Management**:
  - Add, search, delete players.
  - Display all players.
  - Edit player data.
  - Track games played by players (with details like hours played, achievements unlocked).

- **Game Management**:
  - Add, search, delete games.
  - Display all games.
  - Track player information for each game.

- **Binary Search Tree Implementation**:
  - Player data is stored in a BST, allowing for fast search and insertion.
  - Game data is stored in a separate BST for efficient management.

- **File I/O**:
  - Players and games can be loaded from and saved to text files (`Players.txt` and `Games.txt`).

## Directory Structure

```
├── Players.txt    # Contains player data in CSV format
├── Games.txt      # Contains game data in CSV format
└── main.cpp       # Main program source file
```

## Classes

1. **Player**:
   - Stores player information such as ID, name, phone number, email, and password.
   - Keeps a linked list of games played, with details like hours played and achievements unlocked.

2. **Game**:
   - Stores game information such as ID, name, developer, publisher, file size, and download count.

3. **GamePlayed**:
   - Keeps track of individual game sessions, including the number of hours played and achievements unlocked.

4. **PlayerNode** and **GameNode**:
   - Nodes used in the binary search tree to store `Player` and `Game` objects respectively.

5. **PlayerTree** and **GameTree**:
   - Binary Search Tree implementations for managing players and games.

## How to Run

### Prerequisites
- C++ compiler (such as GCC or MSVC).

### Compilation
To compile the code, use the following command:

```bash
g++ main.cpp -o game_management
```

### Running the Program
After compiling, you can run the program by executing the following:

```bash
./game_management
```

The program will prompt you with a menu where you can:
1. Add a player or game.
2. Search for a player or game.
3. Delete a player or game.
4. Display all players or games.

## Additional Notes
- The system uses a binary search tree for efficient insertion, search, and deletion operations.
- Data from `Players.txt` and `Games.txt` is loaded automatically when the program starts.
- You can edit or delete players and games directly through the interactive menu.
