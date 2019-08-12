#include <iostream>
#include <vector>

using namespace std;

//size of gameboard
#define DIMENSION 10

//cases for players
#define SINGLEPLAYER 1
#define TWOPLAYER 2

//number of ship
#define SHIPS 5

//each ships length
#define CARRIER 5
#define BATTLESHIP 4
#define CRUISER 3
#define SUBMARINE 3
#define DESTROYER 2

//sum of ship lengths
#define SHIPPARTS (CARRIER+BATTLESHIP+CRUISER+SUBMARINE+DESTROYER)

class player
{
    public:
        //player name
        string name;

        //gameboard
        int gameboard[DIMENSION][DIMENSION];

        //correct guesses
        int correct = 0;

        //turn number 
        int moveNum = 1;

        //ship coordinates
        vector <string> coordinates;

        //user input coordinate
        string coord;

        //guessed coordinates
        vector <string> usedCoords;

        //coords used in manual input
        vector <string> inputCoords;

        //used for cpu to see if the last coord was hit
        string nextGuess = "";

        string initialHit = "";

        int indexGuess;
}; 