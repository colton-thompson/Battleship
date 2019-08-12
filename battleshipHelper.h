//helper functions for battleship

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>


#define DIMENSION 10

using namespace std;

void waitClear();

void createGameboard(int (&gb)[DIMENSION][DIMENSION]);

void dispGameboard(int (&gb)[DIMENSION][DIMENSION]);

bool isHit(int (&gb)[DIMENSION][DIMENSION], int ships, vector <string> &coordinates, string &coord);

bool doesExist(string &coord, vector <string> &coordinates);

string prompt(int (&gb)[DIMENSION][DIMENSION], vector<string> &coordinates, vector <string> &usedCoords);

void setShipsHelper(int (&gb)[DIMENSION][DIMENSION], int ship, vector <string> &coordinates);

void setShips(int (&gb)[DIMENSION][DIMENSION], vector <string> &coordinates, int numShips);

string northAdjacent(string coord, string colNorth);

string southAdjacent(string coord, string colSouth);

string eastAdjacent(string coord, int colEast);

string westAdjacent(string coord, int colWest);

bool isAdjacent(string coord, int index, vector<string> &coordinates, vector <string> &usedCoords);

void setShipType(int shipType, int (&gb)[DIMENSION][DIMENSION], vector<string> &coordinates, vector <string> &inputCoords, char &direction);

char findDirection(string shipName);

void setShipsMan(int (&gb)[DIMENSION][DIMENSION], vector<string> &coordinates, vector <string> &usedCoords);

void cheat(string name, vector <string> &coordinates);