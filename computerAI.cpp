#include <iostream>
#include <string>

#include "computerAI.h"
#include "battleshipHelper.h"
#include "constGlobalVars.h"


using namespace std;

//bool doesExist(int (&gb)[DIMENSION][DIMENSION], string &coord, vector <string> &coordinates);

bool inBounds(string coord)
{
    size_t sz =0;
    if(coord[0] < 'A' || coord[0] > 'J')
        return false;
            
    int colVal = stoi (coord.substr(1,coord.size()) ,&sz, 0);
    if(colVal < 1 || colVal > 10)
        return false;

    return true;
}

void target(player& cpu, player& player1, string direction)
{
    //cout << "Begin targetting around coord: " << coord << endl;
    
    if(isHit(cpu.gameboard, SHIPS, player1.coordinates, direction))
    {
        cpu.correct++;
        cout << cpu.name << " hit " << player1.name << "'s ship at coordinate " << direction << "!" << endl;
        //cpu.lastHit = true;
        //targeting = false;
    }
    else
    {
        cout << "Splash! " << direction << " missed!" << endl;
        //cpu.lastHit = false;                        //cpu.coordinates.pop_back();
    }
    
    //return coord; 
}


string computerGuess(vector <string> &usedCoords)
{
    //char BEGIN = 'A';
    char startChar = 'A';
    char startChar2 = 'A';

    int startInt = 1, startInt2 = 2, counter = 0;
    string CPUguess;
    CPUguess = startChar + to_string(startInt);

    //usedCoords.push_back(CPUguess);

    //cout << "test A\n";
    while(doesExist(CPUguess, usedCoords)) 
    {
        //random guess - easy mode 
        /*
        startChar = (rand() % ((DIMENSION))+(65));//set row value
        startInt = (rand() % (DIMENSION)+1);//set col value    
        CPUguess = startChar + to_string(startInt);
        return CPUguess; */
        //THIS WORKS
        
        
        if(counter < 50)
        {
            //change col value by 2 to create parity guessing
            // for A,C,E,G,I produce values 1,3,5,7,9
            // for B,D,F,H,J produces values 2,4,6,8.10
            for (int i = startInt; i <= DIMENSION; i+=2)
            {
                counter++;
                //cout << "counter: " << counter << endl;
                //create guess string
                CPUguess = startChar + to_string(i);
                //check if guess string already exists
                if ((!doesExist(CPUguess, usedCoords)))
                {
                    //guess was not already used, push onto vector   
                    
                    usedCoords.push_back(CPUguess);
                    return CPUguess;
                    break; //break out of loop
                }
            }
            //all five row vals existed so increment row
            startChar = int(startChar) + 1;
            //increment startInt by one
            //then take mod 2 of that
            //if it returns a 0, startInt = 2 because col 0 DNE
            //NOTE: DNE = does not exist
            startInt++;
            startInt = startInt%2;
            if(!startInt)
                startInt = 2;
        }
        
        //reverse the parity to find ships
        if (counter >= 50)
        //if (counter < 50)
        {
            //change col value by 2 to create parity guessing
            // for A,C,E,G,I produce values 2,4,6,8.10 
            // for B,D,F,H,J produces values 1,3,5,7,9
            for (int i = startInt2; i <= DIMENSION; i+=2)
            {
                counter++;
                //create guess string
                CPUguess = startChar2 + to_string(i);
                //check if guess string already exists
                if ((!doesExist(CPUguess, usedCoords)))
                {
                    //guess was not already used, push onto vector   
                    usedCoords.push_back(CPUguess);
                    return CPUguess;
                    break; //break out of loop
                }
            }
            //all five row vals existed so increment row
            startChar2 = int(startChar2) + 1;
            //increment startInt by one
            //then take mod 2 of that
            //if it returns a 0, startInt = 2 because col 0 DNE
            //NOTE: DNE = does not exist
            startInt2++;
            startInt2 = startInt2%2;
            if(!startInt2)
                startInt2 = 2;
            
        } 

    }
    usedCoords.push_back(CPUguess);

    return CPUguess;
}

string hunt(player& cpu)//, player& player1)//vector <string> &p1Coords)//, bool targetting)
{
    string prevTarg;


    cpu.coord = computerGuess(cpu.usedCoords);
    return cpu.coord;        

}

void computerAI(player& cpu, player& player1)
{
    string prevCoord = hunt(cpu);//, player1);// player1.coordinates);//, targeting);
                
    if(isHit(cpu.gameboard, SHIPS, player1.coordinates, prevCoord))
    {
        cpu.correct++;
        //targeting = true;
        //cout << "target: " << prevTarg << endl;
        cout << cpu.name << " hit " << player1.name << "'s ship at coordinate " << cpu.coord << "!" << endl;
        //return cpu.coord;
        //cpu.lastHit = true;
    }
    else
    {
        cout << "Splash! " << cpu.coord << " missed!" << endl;
        //cpu.lastHit = false;
    }           //return true;

                
}


bool CPUisHit(int (&gb)[DIMENSION][DIMENSION], int ships, vector<string> &coordinates, string &coord)
{
    vector <string>::iterator it;
    size_t sz = 0;
    char r = coord[0]; //get row char
    string tmp = coord.substr(1,coord.size()); //tmp value for string extraction
    int c = stoi (tmp ,&sz, 0); //ger col int
    
    //set search value
    it = find (coordinates.begin(), coordinates.end(), coord);
    
    //if it does not equal the end of coordinates then it has 
    //hit a ship
    if (it != coordinates.end()) // j != bCol.end())
    {   
        //cout << "HIT: " << coord << endl;
        coordinates.erase(it);
        //gb[int(r)-65][c-1] = 'X'; //~ -> X to mark hit
        return true;
    }
    else
    {
        //cout << "MISS: " << coord << endl;
        //gb[int(r)-65][c-1] = 'O'; //~ -> O to mark miss
        return false;
    }
} //isHit()