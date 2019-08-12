#include <iostream>
#include <string>
#include <vector>

using namespace std; 

#include "battleshipHelper.h"
//#include "constGlobalVars.h"

#define DIMENSION 10
class player;

//bool doesExist(int (&gb)[DIMENSION][DIMENSION], string &coord, vector <string> &coordinates);

string computerGuess(vector <string> &usedCoords);

bool inBounds(string coord);

void target(player& cpu, player& player1, string direction);

string hunt(player& cpu);//, player& player1);//vector <string> &p1Coords);

void computerAI(player& cpu, player& player1);