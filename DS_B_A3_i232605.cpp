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
