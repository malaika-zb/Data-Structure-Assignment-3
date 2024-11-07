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