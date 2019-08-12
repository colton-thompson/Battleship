// Colton Thompson

#include <iostream>
#include <vector>
#include "battleshipHelper.h"
#include "gameModes.h"
//#include "gameModesHelper.h"
#include "computerAI.h"
#include "constGlobalVars.h"

using namespace std;


void battleshipSinglePlayer(player player1, player cpu)
{
    //cout << "Single player mode in testing currently\n\n";
    srand(time(0)); //seed random
    int starter;
    
    player1.name = getName(SINGLEPLAYER);
    cpu.name = "CPU";

    //initialize the gameboards
    createGameboard(player1.gameboard); 
    createGameboard(cpu.gameboard);

    //create and set ship coordinates 
    setShipsInput(player1.name, player1.gameboard, player1.coordinates, player1.inputCoords);
    waitClear();
    setShips(cpu.gameboard, cpu.coordinates, SHIPS);

    //CHEAT system
    //cheat(player1.name, player1.coordinates);
    //cheat(cpu.name, cpu.coordinates);

    //randomize start value to either 0 or 1
    //this will ensure that the starting player is random each time
    starter = getStartVal(starter, player1.name, cpu.name);
    
    
    while(player1.correct < SHIPPARTS && cpu.correct < SHIPPARTS)
    //while(player1.correct < 5 && player2.correct < 5)
    {   
        //cout << "-------------------------------------------------" << endl;

        if(!(starter%2)) //starter = 0, !starter = 1
        //if(0)
        {
            //cheat system for coordinate
            //cheat(cpu.name, cpu.coordinates);

            cout << player1.name << "'s turn, move: " << player1.moveNum << endl;

            dispGameboard(player1.gameboard); 

            //get user input 
            //prompt verifies the input
            player1.coord = prompt(player1.gameboard, player1.coordinates, player1.usedCoords);


            if(isHit(player1.gameboard, SHIPS, cpu.coordinates, player1.coord))
            {
                player1.correct++;
                cout << "You hit " << cpu.name << "'s ship at coordinate " << player1.coord << "!" << endl;
            }
            else
                cout << "Splash! " << player1.coord << " missed!" << endl;
            
            player1.moveNum++; //increase move number
            cout << endl; //spacer

            //show updated gameboard
            dispGameboard(player1.gameboard);
            waitClear();
        }
        else
        {
            bool targetSouth = true;
            size_t sz = 0;
            //cheat system for coordinate
            //cheat(player1.name, player1.coordinates);
            //extra variables for the CPU cases

            cout << cpu.name << "'s turn, move: " << cpu.moveNum << endl;
            
            dispGameboard(cpu.gameboard);

            if(cpu.moveNum > 1)
            {
                cout << "Used coordinates: ";
                for(int i = 0; i < cpu.usedCoords.size(); i++)
                    cout << cpu.usedCoords[i] << " ";
                cout << endl;
            }

            

            //if(cpu.moveNum > 1)
            //    cout << "back test: " << cpu.usedCoords.back() << endl;

            //basecase 
            //HUNT MODE
            if(cpu.nextGuess.size() == 0)
            {
                cpu.coord = computerGuess(cpu.usedCoords);
                //cout << "cpu coord: " << cpu.coord << endl;
                if(isHit(cpu.gameboard, SHIPS, player1.coordinates, cpu.coord))
                {
                    cpu.correct++;
                    cout << "You hit " << player1.name << "'s ship at coordinate " << cpu.coord << "!" << endl;
                    string colNS = cpu.coord.substr(1,cpu.coord.size()); //tmp value for string extraction
                    //string north = northAdjacent(coord, colNS); //northRow + colNS;
                    string south = southAdjacent(cpu.coord, colNS);
                    cpu.nextGuess = south;
                    cpu.initialHit = cpu.coord;
                    cpu.indexGuess = 1;
                    //targetSouth = true;
                }
                else
                    cout << "Splash! " << cpu.coord << " missed!" << endl;
            }
            //target mode
            else if (cpu.indexGuess == 1 && cpu.nextGuess.size() != 0)
            {
                //cout << "executing SOUTH\n";
                cpu.coord = cpu.nextGuess;
                //cpu.coord = cpu.initialHit;
                //cout << "coord: " << cpu.coord << endl;
                int row = cpu.initialHit[0];
                int col = stoi (cpu.initialHit.substr(1, cpu.initialHit.size()), &sz, 0);
                //cout << "recieved coord: " << row-65 << " " << col-1 << "\tgameboard: " << char(cpu.gameboard[row-65][col-1]) << endl;

                if(inBounds(cpu.coord) && cpu.gameboard[row-65][col-1] == 'X' && !doesExist(cpu.coord, cpu.usedCoords))
                {
                    cpu.usedCoords.push_back(cpu.coord);
                    string colNS = cpu.coord.substr(1,cpu.coord.size()); //tmp value for string extraction
                    if(isHit(cpu.gameboard, SHIPS, player1.coordinates, cpu.coord))
                    {
                        cpu.correct++;
                        cout << "You hit " << player1.name << "'s ship at coordinate " << cpu.coord << "!" << endl;
                        //cpu.initialHit = cpu.coord;
                        //string north = northAdjacent(coord, colNS); //northRow + colNS;
                        string south = southAdjacent(cpu.coord, colNS);
                        //string north = northAdjacent(cpu.coord, colNS);
                        cpu.nextGuess = south;
                        cpu.indexGuess = 1;  
                        //cout << "intial hit: " << cpu.initialHit << endl;                  
                    }
                    else
                    {
                        cout << "Splash! " << cpu.coord << " missed!" << endl;
                        string north = northAdjacent(cpu.initialHit, colNS);
                        cpu.nextGuess = north;
                        cpu.indexGuess = 2;
                    }
                }
                else
                {
                    //cout << "out of bounds, next direction\n";
                    cpu.indexGuess = 2;             
                }
            } //end of south
            
            //NORTH TARGET
            else if (cpu.indexGuess == 2 && cpu.nextGuess.size() != 0)
            {
                //cout << "executing NORTH\n";
                cpu.coord = cpu.nextGuess;
                //cout << "intial hit: " << cpu.initialHit << endl; 
                //cpu.coord = cpu.initialHit;
                //cout << "coord: " << cpu.coord << endl;
                int row = cpu.initialHit[0];
                int col = stoi (cpu.initialHit.substr(1, cpu.initialHit.size()), &sz, 0);
                //cout << "recieved coord: " << row-65 << " " << col-1 << "\tgameboard: " << char(cpu.gameboard[row-65][col-1]) << endl;

                if(inBounds(cpu.coord) && cpu.gameboard[row-65][col-1] == 'X' && !doesExist(cpu.coord, cpu.usedCoords))
                {
                    cpu.usedCoords.push_back(cpu.coord);
                    string colNS = cpu.coord.substr(1,cpu.coord.size()); //tmp value for string extraction
                    if(isHit(cpu.gameboard, SHIPS, player1.coordinates, cpu.coord))
                    {
                        cpu.correct++;
                        cout << "You hit " << player1.name << "'s ship at coordinate " << cpu.coord << "!" << endl;
                        //cpu.initialHit = cpu.coord;
                        //string north = northAdjacent(coord, colNS); //northRow + colNS;
                        string north = northAdjacent(cpu.coord, colNS);
                        //string north = northAdjacent(cpu.coord, colNS);
                        cpu.nextGuess = north;
                        cpu.indexGuess = 2;  
                        //cout << "intial hit: " << cpu.initialHit << endl;                  
                    }
                    else
                    {
                        cout << "Splash! " << cpu.coord << " missed!" << endl;
                        int col = stoi (cpu.initialHit.substr(1,cpu.initialHit.size()), &sz, 0);
                        string east = eastAdjacent(cpu.initialHit, col);
                        cpu.nextGuess = east;
                        cpu.indexGuess = 3;
                    }
                }
                else
                {
                    //cout << "out of bounds, next direction\n";
                    cpu.indexGuess = 3;             
                }
            } 

            else if (cpu.indexGuess == 3 && cpu.nextGuess.size() != 0)
            {
                //cout << "executing EAST\n";
                cpu.coord = cpu.nextGuess;
                //cout << "intial hit: " << cpu.initialHit << endl; 
                //cpu.coord = cpu.initialHit;
                //cout << "coord: " << cpu.coord << endl;
                int row = cpu.initialHit[0];
                int col = stoi (cpu.initialHit.substr(1, cpu.initialHit.size()), &sz, 0);
                //cout << "recieved coord: " << row-65 << " " << col << "\tgameboard: " << char(cpu.gameboard[row-65][col-1]) << endl;

                if(inBounds(cpu.coord) && cpu.gameboard[row-65][col-1] == 'X' && !doesExist(cpu.coord, cpu.usedCoords))
                {
                    cpu.usedCoords.push_back(cpu.coord);
                    int colEW = stoi (cpu.coord.substr(1,cpu.coord.size()), &sz, 0);
                    if(isHit(cpu.gameboard, SHIPS, player1.coordinates, cpu.coord))
                    {
                        cpu.correct++;
                        cout << "You hit " << player1.name << "'s ship at coordinate " << cpu.coord << "!" << endl;
                        //cpu.initialHit = cpu.coord;
                        //string north = northAdjacent(coord, colNS); //northRow + colNS;
                        string east = eastAdjacent(cpu.coord, colEW);
                        //string north = northAdjacent(cpu.coord, colNS);
                        cpu.nextGuess = east;
                        cpu.indexGuess = 3;  
                        //cout << "intial hit: " << cpu.initialHit << endl;                  
                    }
                    else
                    {
                        cout << "Splash! " << cpu.coord << " missed!" << endl;
                        int colW = stoi (cpu.initialHit.substr(1,cpu.initialHit.size()), &sz, 0);
                        string west = westAdjacent(cpu.initialHit, colW);
                        cpu.nextGuess = west;
                        cpu.indexGuess = 4;
                    }
                }
                else
                {
                    //cout << "out of bounds, next direction\n";
                    cpu.indexGuess = 4;             
                }
            } 

            else if (cpu.indexGuess == 4 && cpu.nextGuess.size() != 0)
            {
                //cout << "executing WEST\n";
                cpu.coord = cpu.nextGuess;
                //cout << "intial hit: " << cpu.initialHit << endl; 
                //cpu.coord = cpu.initialHit;
                //cout << "coord: " << cpu.coord << endl;
                int row = cpu.initialHit[0];
                int col = stoi (cpu.initialHit.substr(1, cpu.initialHit.size()), &sz, 0);
                //cout << "recieved coord: " << row-65 << " " << col-1 << "\tgameboard: " << char(cpu.gameboard[row-65][col-1]) << endl;

                if(inBounds(cpu.coord) && cpu.gameboard[row-65][col-1] == 'X' && !doesExist(cpu.coord, cpu.usedCoords))
                {
                    cpu.usedCoords.push_back(cpu.coord);
                    int colEW = stoi (cpu.coord.substr(1,cpu.coord.size()), &sz, 0);
                    if(isHit(cpu.gameboard, SHIPS, player1.coordinates, cpu.coord))
                    {
                        cpu.correct++;
                        cout << "You hit " << player1.name << "'s ship at coordinate " << cpu.coord << "!" << endl;
                        //cpu.initialHit = cpu.coord;
                        //string north = northAdjacent(coord, colNS); //northRow + colNS;
                        string west = westAdjacent(cpu.coord, colEW);
                        //string north = northAdjacent(cpu.coord, colNS);
                        cpu.nextGuess = west;
                        cpu.indexGuess = 4;  
                        //cout << "intial hit: " << cpu.initialHit << endl;                  
                    }
                    else
                    {
                        cout << "Splash! " << cpu.coord << " missed!" << endl;
                        //int colEW = stoi (coord.substr(1,cpu.coord.size()), &sz, 0);
                        //string east = eastAdjacent(cpu.coord, colEW);
                        cpu.nextGuess = "";
                        cpu.indexGuess = 0;
                    }
                }
                else
                {
                    //cout << "out of bounds, next direction\n";
                    cpu.indexGuess = 1;      
                    cpu.nextGuess = "";       
                }
            } 
            
            
            
            
            
            cpu.moveNum++;//increase move number
            cout << endl; //spacer

            //show updated gameboard
            dispGameboard(cpu.gameboard);
            //pause
            waitClear();
        }
        //system("clear"); //clear screen
        starter++;
    }
    //display winner information
    if(player1.correct == 17)
        cout << player1.name << " sunk all of " << cpu.name << "'s ships in " << player1.moveNum-1 << " moves!\n" << player1.name << " won! Game Over" << endl; 
    else      
        cout << cpu.name << " sunk all of " << player1.name << "'s ships in " << cpu.moveNum-1 << " moves!\n" << cpu.name << " won! Game Over" << endl; 
    //}
   
}

void battleshipTwoPlayer(player player1, player player2)
{
    srand(time(0)); //seed random
    int starter;
    
    //get player names
    player1.name = getName((TWOPLAYER-1));
    //playerNum++;
    player2.name = getName(TWOPLAYER);
    //playerNum == 1; //revert back to previous state for reuse
    
    //initialize the gameboards
    createGameboard(player1.gameboard); 
    createGameboard(player2.gameboard);
    
    //create and set ship coordinates
    waitClear();
    setShipsInput(player1.name, player1.gameboard, player1.coordinates, player1.inputCoords);
    system("clear");//waitClear();
    setShipsInput(player2.name, player2.gameboard, player2.coordinates, player2.inputCoords);
    waitClear();

    //randomize start value to either 0 or 1
    //this will ensure that the starting player is random each time
    starter = getStartVal(starter, player1.name, player2.name);


    while(player1.correct < SHIPPARTS && player2.correct < SHIPPARTS)
    //while(player1.correct < 5 && player2.correct < 5)
    {   
        //cout << "-------------------------------------------------" << endl;

        if(!(starter%2)) //starter = 0, !starter = 1
        //if(1)
        {
            //cheat system for coordinate
            //cheat(player2.name, player2.coordinates);

            cout << player1.name << "'s turn, move: " << player1.moveNum << endl;

            dispGameboard(player1.gameboard); 

            //get user input 
            //prompt verifies the input
            player1.coord = prompt(player1.gameboard, player1.coordinates, player1.usedCoords);


            if(isHit(player1.gameboard, SHIPS, player2.coordinates, player1.coord))
            {
                player1.correct++;
                cout << "You hit " << player2.name << "'s ship at coordinate " << player1.coord << "!" << endl;
            }
            else
                cout << "Splash! " << player1.coord << " missed!" << endl;
            
            player1.moveNum++; //increase move number
            cout << endl; //spacer

            //show updated gameboard
            dispGameboard(player1.gameboard);
            waitClear();
            //cout << "Press any key to continue...";
            //cin.ignore();
        }
        else
        {
            //cheat system for coordinate
            //cheat(player1.name, player1.coordinates);

            cout << player2.name << "'s turn, move: " << player2.moveNum << endl;

            dispGameboard(player2.gameboard);

            //get user input 
            //prompt verifies the input
            player2.coord = prompt(player2.gameboard, player2.coordinates, player2.usedCoords);

            //check to see if the coordinate hits a ship
            if(isHit(player2.gameboard, SHIPS, player1.coordinates, player2.coord))
            {
                player2.correct++;
                cout << "You hit " << player1.name << "'s ship at coordinate " << player2.coord << "!" << endl;
            }
            else
                cout << "Splash! " << player2.coord << " missed!" << endl;

            player2.moveNum++;//increase move number
            cout << endl; //spacer

            //show updated gameboard
            dispGameboard(player2.gameboard);
            //pause
            waitClear();
            //cout << "Press enter to continue...";
            //cin.ignore();
        }
        //system("clear"); //clear screen
        starter++;
    }
    //display winner information
    if(player1.correct == 17)
        cout << player1.name << " sunk all of " << player2.name << "'s ships in " << player1.moveNum-1 << " moves!\n" << player1.name << " won! Game Over" << endl; 
    else      
        cout << player2.name << " sunk all of " << player1.name << "'s ships in " << player2.moveNum-1 << " moves!\n" << player2.name << " won! Game Over" << endl; 

    //player1.coordinates.clear();
    //player2.coordinates.clear();
}