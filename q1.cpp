#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class GamePlayed 
{
public:
string gameID;
float hoursPlayed;
int achievementUnlocked;
GamePlayed* next;

GamePlayed() : gameID(""), hoursPlayed(0.0), achievementUnlocked(0), next(nullptr) 
{}
};

class Game 
{
public:
string gameID;
string name;
string developer;
string publisher;
float fileSizeInGBs;
int downloads;

Game() : gameID(""), name(""), developer(""), publisher(""), fileSizeInGBs(0.0), downloads(0) {}
};

class Player 
{
public:
string playerID;
string name;
string phoneNo;
string email;
string password;
GamePlayed* gamePlayedHead;

Player() : playerID(""), name(""), phoneNo(""), email(""), password(""), gamePlayedHead(nullptr) 
{}
};

class PlayerNode 
{
public:
Player player;
PlayerNode* left;
PlayerNode* right;

PlayerNode(Player p) : player(p), left(nullptr), right(nullptr) 
{}
};

class GameNode 
{
public:
Game game;
GameNode* left;
GameNode* right;

GameNode(Game g) : game(g), left(nullptr), right(nullptr) {}
};

class PlayerTree 
{
public:
PlayerNode* root;

PlayerTree() : root(nullptr) 
{}

bool insert(PlayerNode *newNode) 
{
return insertRec(root, newNode);
}

bool insertRec(PlayerNode *&node, PlayerNode *newNode) 
{
if (node == nullptr) 
{
node = newNode;
return true;
}
if (newNode->player.playerID == node->player.playerID) 
{
cout << "player id doesnt exist" << endl;
return false;
}
if (newNode->player.playerID < node->player.playerID) 
{
return insertRec(node->left, newNode);
} 
else 
{
return insertRec(node->right, newNode);
}
}



bool deleteNode(string playerID) 
{
root = deleteRec(root, playerID);
return root != nullptr;
}

PlayerNode* deleteRec(PlayerNode *&node, const string& playerID) 
{
if (node == nullptr) 
return nullptr;
if (playerID < node->player.playerID) 
{
node->left = deleteRec(node->left, playerID);
} 
else if (playerID > node->player.playerID) 
{
node->right = deleteRec(node->right, playerID);
} 
else 
{
if (node->left == nullptr) 
{
PlayerNode *temp = node;
node = node->right;
delete temp;
} 
else if (node->right == nullptr) 
{
PlayerNode *temp = node;
node = node->left;
delete temp;
} 
else 
{
PlayerNode *temp = minNode(node->right);
node->player = temp->player;
node->right = deleteRec(node->right, temp->player.playerID);
}
}
return node;
}

PlayerNode* minNode(PlayerNode *node) 
{
while (node->left != nullptr) node = node->left;
return node;
}

void preorderTraversal(PlayerNode *node) 
{
if (node == nullptr) 
return;
cout << node->player.playerID << "," << node->player.name << endl;
preorderTraversal(node->left);
preorderTraversal(node->right);
}

void saveToFile(const string& filename) 
{
ofstream file(filename);
if (!file) 
{
cout << "error opening file" << endl;
return;
}
preorderTraversalToFile(root, file);
file.close();
}

void preorderTraversalToFile(PlayerNode *node, ofstream &file) 
{
if (node == nullptr) 
return;
file << node->player.playerID << "," << node->player.name << endl;
preorderTraversalToFile(node->left, file);
preorderTraversalToFile(node->right, file);
}

void showLayers(int n) 
{
showLayersRec(root, 1, n);
}

void showLayersRec(PlayerNode *node, int currentLayer, int maxLayers) 
{
if (node == nullptr) 
return;
if (currentLayer <= maxLayers) 
{
cout << "Layer " << currentLayer << ": " << node->player.playerID << "," << node->player.name << endl;
showLayersRec(node->left, currentLayer + 1, maxLayers);
showLayersRec(node->right, currentLayer + 1, maxLayers);
} 
else 
{
cout << "Layer limit was reached, can’t go further." << endl;
}
}

int getLayer(const string& playerID) 
{
return getLayerRec(root, playerID, 1);
}

int getLayerRec(PlayerNode *node, const string& playerID, int currentLayer) 
{
if (node == nullptr) 
return -1;
if (node->player.playerID == playerID) 
return currentLayer;
int leftLayer = getLayerRec(node->left, playerID, currentLayer + 1);
if (leftLayer != -1) 
return leftLayer;
return getLayerRec(node->right, playerID, currentLayer + 1);
}

void showPath(const string& playerID) 
{
showPathRec(root, playerID);
}

void showPathRec(PlayerNode *node, const string& playerID) 
{
if (node == nullptr) 
return;
cout << node->player.playerID << " -> ";
if (node->player.playerID == playerID) 
{
cout << "Found!" << endl;
return;
}
if (playerID < node->player.playerID) 
{
showPathRec(node->left, playerID);
} 
else 
{
showPathRec(node->right, playerID);
}
}

void editEntry(const string& oldID, PlayerNode* newData) 
{
if (deleteNode(oldID)) 
{
if (insert(newData)) 
{
cout << "Entry edited and repositioned in the tree." << endl;
} 
else 
{
cout << "Failed to insert the new player data." << endl;
}
} else 
{
cout << "Player not found, cannot edit entry!" << endl;
}
}
};

class GameTree {
public:
GameNode* root;

GameTree() : root(nullptr) 
{}

bool insert(GameNode *newNode) 
{
return insertRec(root, newNode);
}

bool insertRec(GameNode *&node, GameNode *newNode) 
{
if (node == nullptr) 
{
node = newNode;
return true;
}
if (newNode->game.gameID == node->game.gameID) 
{
cout << "game id already exists" << endl;
return false;
}
if (newNode->game.gameID < node->game.gameID) 
{
return insertRec(node->left, newNode);
} 
else 
{
return insertRec(node->right, newNode);
}
}

GameNode* search(const string& gameID) 
{
return searchRec(root, gameID);
}

GameNode* searchRec(GameNode *node, const string& gameID) 
{
if (node == nullptr || node->game.gameID == gameID) 
{
return node;
}
if (gameID < node->game.gameID) 
{
return searchRec(node->left, gameID);
} 
else 
{
return searchRec(node->right, gameID);
}
}

bool deleteNode(string gameID) 
{
root = deleteRec(root, gameID);
return root != nullptr;
}

GameNode* deleteRec(GameNode *&node, const string& gameID) 
{
if (node == nullptr) 
return nullptr;
if (gameID < node->game.gameID) 
{
node->left = deleteRec(node->left, gameID);
} 
else if (gameID > node->game.gameID) 
{
node->right = deleteRec(node->right, gameID);
} 
else 
{
if (node->left == nullptr) 
{
GameNode *temp = node;
node = node->right;
delete temp;
} 
else if (node->right == nullptr) 
{
GameNode *temp = node;
node = node->left;
delete temp;
} 
else 
{
GameNode *temp = minNode(node->right);
node->game = temp->game;
node->right = deleteRec(node->right, temp->game.gameID);
}
}
return node;
}

GameNode* minNode(GameNode *node) 
{
while (node->left != nullptr) node = node->left;
return node;
}

void preorderTraversal(GameNode *node) 
{
if (node == nullptr) 
return;
cout << node->game.gameID << "," << node->game.name << endl;
preorderTraversal(node->left);
preorderTraversal(node->right);
}
};

void readPlayersFromFile(PlayerTree& playerTree, const string& filename) 
{
ifstream file(filename);
if (!file) 
{
cout << "error opening file" << endl;
return;
}
string line;
while (getline(file, line)) 
{
stringstream ss(line);
string playerID, name, phone, email, password;
getline(ss, playerID, ',');
getline(ss, name, ',');
getline(ss, phone, ',');
getline(ss, email, ',');
getline(ss, password, ',');

Player player;
player.playerID = playerID;
player.name = name;
player.phoneNo = phone;
player.email = email;
player.password = password;

playerTree.insert(new PlayerNode(player));
}
file.close();
}

void readGamesFromFile(GameTree& gameTree, const string& filename) 
{
ifstream file(filename);
if (!file) 
{
cout << "error opening file" << endl;
return;
}
string line;
while (getline(file, line)) 
{
stringstream ss(line);
string gameID, name, developer, publisher;
float fileSize;
int downloads;
getline(ss, gameID, ',');
getline(ss, name, ',');
getline(ss, developer, ',');
getline(ss, publisher, ',');
ss >> fileSize;
ss.ignore();  
ss >> downloads;

Game game;
game.gameID = gameID;
game.name = name;
game.developer = developer;
game.publisher = publisher;
game.fileSizeInGBs = fileSize;
game.downloads = downloads;

gameTree.insert(new GameNode(game));
}
file.close();
}

int main() 
{
PlayerTree playerTree;
GameTree gameTree;

int choice;
string id, name, phone, email, password, developer, publisher, gameName;
double fileSize;
int downloads;

while (true) 
{

readPlayersFromFile(playerTree, "Players.txt");

readGamesFromFile(gameTree, "Games.txt");


cout << "\n--- Main Menu ---\n";
cout << "1. Add Player\n";
cout << "2. Add Game\n";
cout << "3. Search Player\n";
cout << "4. Search Game\n";
cout << "5. Delete Player\n";
cout << "6. Delete Game\n";
cout << "7. Display All Players\n";
cout << "8. Display All Games\n";
cout << "9. Exit\n";
cout << "Enter your choice: ";
cin >> choice;

cin.ignore(); 

switch (choice) 
{
case 1: 
{
cout << "Enter Player ID: ";
getline(cin, id);
cout << "Enter Player Name: ";
getline(cin, name);
cout << "Enter Phone Number: ";
getline(cin, phone);
cout << "Enter Email: ";
getline(cin, email);
cout << "Enter Password: ";
getline(cin, password);

Player player;
player.playerID = id;
player.name = name;
player.phoneNo = phone;
player.email = email;
player.password = password;

playerTree.insert(new PlayerNode(player));
cout << "Player added successfully.\n";
break;
}
case 2: 
{
cout << "Enter Game ID: ";
getline(cin, id);
cout << "Enter Game Name: ";
getline(cin, gameName);
cout << "Enter Developer: ";
getline(cin, developer);
cout << "Enter Publisher: ";
getline(cin, publisher);
cout << "Enter File Size (GB): ";
cin >> fileSize;
cout << "Enter Downloads: ";
cin >> downloads;
cin.ignore();

Game game;
game.gameID = id;
game.name = gameName;
game.developer = developer;
game.publisher = publisher;
game.fileSizeInGBs = fileSize;
game.downloads = downloads;

gameTree.insert(new GameNode(game));
cout << "Game added successfully.\n";
break;
}
case 3: 
{
cout << "Enter Player ID to search: ";
getline(cin, id);
PlayerNode* foundPlayer = playerTree.search(id);
if (foundPlayer) 
{
cout << "Player Found: " << foundPlayer->player.name << endl;
} 
else 
{
cout << "Player not found with ID: " << id << endl;
}
break;
}
case 4: 
{
cout << "Enter Game ID to search: ";
getline(cin, id);
GameNode* foundGame = gameTree.search(id);
if (foundGame) 
{
cout << "Game Found: " << foundGame->game.name << endl;
} 
else 
{
cout << "Game not found with ID: " << id << endl;
}
break;
}
case 5: 
{
cout << "Enter Player ID to delete: ";
getline(cin, id);
playerTree.deleteNode(id);
cout << "Player deleted successfully.\n";
break;
}
case 6: 
{
cout << "Enter Game ID to delete: ";
getline(cin, id);
gameTree.deleteNode(id);
cout << "Game deleted successfully.\n";
break;
}
case 7: 
{
cout << "Displaying all players:\n";
playerTree.preorderTraversal(playerTree.root);
break;
}
case 8: 
{
cout << "Displaying all games:\n";
gameTree.preorderTraversal(gameTree.root);
break;
}
case 9:
cout << "Exiting...\n";
return 0;
default:
cout << "Invalid choice! Please try again.\n";
break;
}
}
return 0;
}
