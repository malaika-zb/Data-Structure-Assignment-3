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

PlayerNode* search(const string& playerID) 
{
return searchRec(root, playerID);
}

PlayerNode* searchRec(PlayerNode *node, const string& playerID) 
{
if (node == nullptr || node->player.playerID == playerID) 
{
return node;
}
if (playerID < node->player.playerID) 
{
return searchRec(node->left, playerID);
} 
else 
{
return searchRec(node->right, playerID);
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

