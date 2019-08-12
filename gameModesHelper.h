#include <iostream>
#include <vector>

//#include "battleshipHelper.h"
//#include "constGlobalVars.h"
using namespace std;

#define DIMENSION 10

string getName(int playerNum);

int getStartVal(int start, string name1, string name2);

void setShipsInput(string name, int (&gb)[DIMENSION][DIMENSION], vector <string> &coordinates, vector <string> &usedCoords);