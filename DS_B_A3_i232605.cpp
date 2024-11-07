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
