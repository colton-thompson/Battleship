#include <iostream>
#include <string>

#include "battleshipHelper.h"
#include "constGlobalVars.h"
#include "gameModes.h"
//#include "constGlobalVars.h"

//#include "gameModesHelper.h"

using namespace std;

//prototypes
class player;
void battleshipSinglePlayer(player player1, player cpu);
void battleshipTwoPlayer(player player1, player player2);

int main()
{
    system("clear");
    bool repeat = true;
    string tmp;
    int userChoice;
    size_t sz = 0;

    while(repeat)
    {
        cout << "+-------------------+" << endl;
        cout << "| *** Battlehip *** |" << endl;
        cout << "|        Menu       |" << endl;
        cout << "|                   |" << endl;
        cout << "| 1 - single player |" << endl;
        cout << "| 2 - two plyer     |" << endl;
        cout << "| 3 - quit          |" << endl;
        cout << "+-------------------+" << endl;
        cout << "Selection: ";
        getline(cin, tmp); //NOTE: getline instead of cin for consistency and error avoidance
        userChoice = tmp[0]-48;//subtract 48 because of ascii value  

        switch (userChoice)
        {
            case 1:
            {
                player player1;
                //player player2;
                player cpu;

                //cout << "mode is currently being developed\n";
                //cout << "initalizing 2 player mode\n";
                //battleshipTwoPlayer(player1, player2);
                battleshipSinglePlayer(player1, cpu);
                break;
            }
            case 2:
            {
                player player1;
                player player2;

                battleshipTwoPlayer(player1, player2);
                break;
            }
            case 3: 
            {   
                cout << "quiting" << endl;
                repeat = false;
                break;
            }

            default: 
            {
                cout << "ERROR: input must be 1, 2, or 3" << endl;  
                break;
            }
        }
        cout << "Press enter to continue...";
        cin.ignore();
        system("clear");
    
    }

    return 0;
}