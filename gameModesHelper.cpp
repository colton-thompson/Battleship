#include <iostream>

#include "battleshipHelper.h"
#include "gameModesHelper.h"
#include "constGlobalVars.h"

string getName(int playerNum)
{
    string name;
    cout << "Enter player " << playerNum << "'s name: ";
    getline(cin, name);
    return name;
}

int getStartVal(int start, string name1, string name2)
{
    start = rand()%2; 
    
    if(!(start))
        cout << name1 << " starts first!\n";  //dispGameboard(player1.gameboard);
    else
        cout << name2 << " starts first!\n";  //dispGameboard(player2.gameboard);

    return start;
}

void setShipsInput(string name, int (&gb)[DIMENSION][DIMENSION], vector <string> &coordinates, vector <string> &usedCoords)
{
    string genShipInput;
    bool correctInput = true;
    do
    {
        cout << name << ": generate your coordinates randomly? (Y/N): ";
        getline(cin, genShipInput);

        if(genShipInput == "Y" || genShipInput == "y" || genShipInput == "yes" || genShipInput == "Yes" || genShipInput == "YES")
        {
            cout << name << ", your ships are set!\n";
            setShips(gb, coordinates, SHIPS);
            correctInput = false;
        }
        else if(genShipInput == "N" || genShipInput == "n" || genShipInput == "no" || genShipInput == "No" || genShipInput == "NO")
        {
            setShipsMan(gb, coordinates, usedCoords);
            //cout << "feature coming soon!\nShips set randomly...\n";
            //setShips(gb, coordinates, SHIPS);
            correctInput = false;
        }
        else
        {
            cout << "ERROR: input \"" << genShipInput << "\" is invalid!\n";
        }
    } while(correctInput);
}