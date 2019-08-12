#include <iostream>

#include "constGlobalVars.h"
#include "battleshipHelper.h"
//#include "constGlobalVars.h"

void waitClear()
{
    cout << "Press enter to continue...";
    cin.ignore();
    system("clear");
}

void createGameboard(int (&gb)[DIMENSION][DIMENSION])
{
    //initialize gameboard spaces to ~
    for(int i = 0; i < DIMENSION; i++)
    {
        //cout << char(i+65) << "|  ";
        for(int j = 0; j < DIMENSION; j++)
        {
            gb[i][j] = 126; //126 = ~ in  ASCII
        }
    }
} // createGameboard()

void dispGameboard(int (&gb)[DIMENSION][DIMENSION])
{   
    cout << "   1  " << "2  " << "3  " << "4  " << "5  ";
    cout << "6  " << "7  " << "8  " << "9  " << "10  " << endl;
    for(int i = 0; i < DIMENSION; i++)
    {
        cout << char(i+65) << "| ";
        for(int j = 0; j < DIMENSION; j++)
            cout << char(gb[i][j]) << "  ";
        cout << endl;
    }
} // dispGameboard()

bool isHit(int (&gb)[DIMENSION][DIMENSION], int ships, vector<string> &coordinates, string &coord)
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
        gb[int(r)-65][c-1] = 'X'; //~ -> X to mark hit
        return true;
    }
    else
    {
        //cout << "MISS: " << coord << endl;
        gb[int(r)-65][c-1] = 'O'; //~ -> O to mark miss
        return false;
    }
} //isHit()

bool doesExist(string &coord, vector <string> &coordinates)
{
    vector <string>::iterator it; //initialize iterator

    //set iterator search value
    it = find (coordinates.begin(), coordinates.end(), coord);
        
    if (it != coordinates.end())
        return true; //it exists
    else
        return false; //new coordinate
} // doesExist()

string prompt(int (&gb)[DIMENSION][DIMENSION], vector<string> &coordinates, vector <string> &usedCoords)
{
    vector <string>::iterator it;
    bool repeatPrompt = true;
    string coords;
    int colVal;
    size_t sz = 0;
    
    while(repeatPrompt)
    {
        cout << "Enter coordinate: ";
        //cout << "row (char), col (int): ";
        getline(cin, coords); // get user input
        
            //verification of user input
            //check input size, row range, and col range
            if(coords.size() <= 1 || coords.size() > 3)
            {
                while(coords.size() <= 1 || coords.size() > 3)
                {
                    cout << "ERROR: input size of " << coords.size() << " is invalid" << endl;
                    cout << "row (A-J), col (1-10): ";
                    getline(cin, coords); // get user input
                }
            }
            if(coords[0] < 'A' || coords[0] > 'J')
            {
                while(coords[0] < 'A' || coords[0] > 'J')
                {
                    cout << "ERROR: row value " << coords[0] << " is out of bounds" << endl;
                    cout << "row (A-J), col (1-10): ";
                    getline(cin, coords); // get user input
                }
                
            }
            colVal = stoi (coords.substr(1,coords.size()) ,&sz, 0);
            if(colVal < 1 || colVal > 10)
            {
                while(colVal < 1 || colVal > 10)
                {
                    cout << "ERROR: column value: " << colVal << " is out of bounds" << endl;
                    cout << "row (A-J), col (1-10): ";
                    getline(cin, coords); // get user input
                    colVal = stoi (coords.substr(1,coords.size()) ,&sz, 0);
                }   
            }
        
        repeatPrompt = doesExist(coords, usedCoords); //change bool accordingly
        
    
        if(repeatPrompt)
        {
            //coordinates.pop_back();
            cout << "ERROR: coordinate " << coords << " has already been used" << endl; //print errir message
            //usedCoords.pop_back();
        }
        else
        {
            usedCoords.push_back(coords); //coords is now used in the program so push it into vector
            return coords;
        }
    }
} //prompt()

void setShipsHelper(int (&gb)[DIMENSION][DIMENSION], int ship, vector <string> &coordinates)
{
    char r;
    int c, pos;
    bool check = true;
    string coords;
    string cCoordINT;
    size_t sz = 0; 
    
    //mod with 2 to produce 0 or 1
    pos = rand()%2;
    
    //determine position, r val, and c val
    //NOTE: +(65) is used to get to char value in ASCII
    if (pos)
    {
        //VERTICAL CASE
        r = (rand() % ((DIMENSION))+(65));//set row value
        c = (rand() % (DIMENSION)+1);//set col value 
        
        //verify that c is acceptable range
        //if not, repeat until it is
        while (c > (DIMENSION-ship)+1)
            c = (rand() % (DIMENSION)+1);//col 
    }
    else
    {
        //HORIZONTAL CASE
        r = (rand() % (DIMENSION-ship)+1+(65)); //set row value
        //verify that r is acceptable range
        //if not, repeat until it is
        while (r > char((DIMENSION-ship)+65))
            r = (rand() % (DIMENSION-ship)+1+ (65));//row FIX
        c = (rand() % (DIMENSION)+1);//set col value
    }


    for(int j = 0; j < ship; j++)
    {
        if(pos)
        {   
            //horizontal position
            string rCoord (1, r); //convert char r to string
            cCoordINT = to_string(c+j); //convert int c to a string
            coords = rCoord + cCoordINT; //concatenate r and c

                //check if this coordinate exists already
                //if it exists, delete all coords
                //this will restart function setShips
                //NOTE: do this instead of reworking for ease of use
                if (doesExist(coords, coordinates))
                {
                    coordinates.clear(); //removes all elements from coordinates
                    break;
                }
            coordinates.push_back(coords); //new coordinate, add to memory
        }

        else
        {
            //vertical position
            string rCoord (1, r+j); //convert char r to string
            cCoordINT = to_string(c); //convert int c to a string
            coords = rCoord + cCoordINT; //concatenate r and c
            
                //check if this coordinate exists already
                //if it exists, delete all coords
                //this will restart function setShips
                //NOTE: do this instead of reworking for ease of use
                if(doesExist(coords, coordinates))
                {
                    coordinates.clear();   
                    break;
                }          
            coordinates.push_back(coords);  //concatenate r and c
        }
    }
} // setShipsHelper()

void setShips(int (&gb)[DIMENSION][DIMENSION], vector <string> &coordinates, int numShips)//, int ships)
{
    //cout << "----CARRIER +5----" << endl;
    setShipsHelper(gb, CARRIER, coordinates);
    if(coordinates.size() != 0)
    {
       // cout << "----BATTLESHIP +4----" << endl;
       setShipsHelper(gb, BATTLESHIP, coordinates);
       if(coordinates.size() != 0)
        {
            //cout << "----CRUISER +3----" << endl;
            setShipsHelper(gb, CRUISER, coordinates);
            if(coordinates.size() != 0)
            {
                //cout << "----SUBMARINE +3----" << endl;
                setShipsHelper(gb, SUBMARINE, coordinates);
                if(coordinates.size() != 0)
                {
                    //cout << "----DESTROYER +2----" << endl;
                    setShipsHelper(gb, DESTROYER, coordinates);
                }
            }
        }
    }

    //if coordinates break and are cleared, they will return a 0
    //while it returns a 0, keep calling function until success    
    if(coordinates.size() == 0)
        setShips(gb, coordinates, numShips);
} // setShips()

string northAdjacent(string coord, string colNorth)
{
    char northRow = coord[0]-1;
    //string colNS = coord.substr(1,coord.size());
    string north = northRow + colNorth;// colNS;

    return north;
}

string southAdjacent(string coord, string colSouth)
{
    char southRow = coord[0]+1;
    //string colNS = coord.substr(1,coord.size());
    string south = southRow + colSouth;// colNS;

    return south;
}

string eastAdjacent(string coord, int colEast)
{
    string col = to_string(colEast+1);
    string east = coord[0] + col;
    
    return east;
}

string westAdjacent(string coord, int colWest)
{
    string col = to_string(colWest-1);
    string west = coord[0] + col;

    return west;
}

bool isAdjacent(string coord, int index, vector<string> &coordinates, vector <string> &usedCoords, char &direction)
{
    size_t sz = 0;
    char row = coord[0];
    string col = coord.substr(1,coord.size());
    //north south adjacency
    string colNS = coord.substr(1,coord.size()); //tmp value for string extraction
    string north = northAdjacent(coord, colNS); //northRow + colNS;
    string south = southAdjacent(coord, colNS); //southRow + colNS;
    
    //east west adjacency
    int colEW = stoi (col ,&sz, 0); //ger col int
    string east = eastAdjacent(coord, colEW);//row + eastCol;
    string west = westAdjacent(coord, colEW);//row + westCol;

    if(index > 0)
    {
        for(int i = 0; i < usedCoords.size(); i++)
        {
            if(direction == 'v' )//|| direction == 'V')
            {
                if (usedCoords[i] == north)
                {
                    //cout << "NORTH is adjacent\n";
                    return true;
                }
                else if (usedCoords[i] == south)
                {
                    //cout << "SOUTH is adjacent\n";
                    return true;
                }
            }

            if(direction == 'h')// || direction == 'H')
            {
                if (usedCoords[i] == east)
                {
                    //cout << "EAST is adjacent\n";
                    return true;
                }
                else if (usedCoords[i] == west)
                {
                    //cout << "WEST is adjacent\n";
                    return true;
                }
            }
            
        } 
        cout << "ERROR: " << coord << " is not alligned with previous coordinate(s)\n";
        return false;
    }
}

void setShipType(int shipType, int (&gb)[DIMENSION][DIMENSION], vector<string> &coordinates, vector <string> &inputCoords, char &direction)
{
    bool adjacent = true;
    //bool exist = false;
    int count = 0, size = inputCoords.size();

    //display the used coordinates for all cases besides the CARRIER
    if (size != 0)
    {
        cout << "Used coordinates: ";
        for(int i = 0; i < inputCoords.size(); i++)
            cout << inputCoords[i] << " ";
        cout << endl; 
    }   

    while (count < shipType)
    {

        string inputCoord = prompt(gb, coordinates, coordinates);
        
        inputCoords.push_back(inputCoord);
       
        //only check if coordinates are adjacent after the first coordinate
        if(count > 0)
            adjacent = isAdjacent(inputCoord, count, coordinates, inputCoords, direction);
        
        if(adjacent)
            count++;
        else
        {
            coordinates.pop_back();   //coordinates did not match therefore
            inputCoords.pop_back();   //pop them off from vector      
        }
    }
}

char findDirection(string shipName)
{
    string direction;
    bool correct = true;
    
    
    do
    {
        cout << "set " << shipName << ":\n";
        cout << "place horizontal or vertical (H/V): ";
        getline(cin, direction);
        //cin >> direction;
        switch (direction[0])
        {
            case 'h':
            case 'H':
                {
                    //cout << "HORIZONTAL \n";
                    return 'h';
                    break;
                }
            case 'v':
            case 'V':
                {
                    //cout << "direction is vertical\n";
                    return 'v';
                    break;
                }
            default: 
                {
                    cout << "Error: input \"" << direction << "\" is invalid\n";
                    cout << "Valid options are h, H, v, V\n";
                    waitClear();
                    break;
                }

        }
    } while (correct);
}

void setShipsMan(int (&gb)[DIMENSION][DIMENSION], vector<string> &coordinates, vector <string> &inputCoords)
{
    string inputCoord;
    char direction;
    bool repeat = true;
    bool exist = false;
    bool adjacent = true;
    int count = 0;

    //cout << "ships will be set manually\n\n";
    //set ship coordinates
    waitClear();
    //cout << "set CARRIER: \n";
    direction = findDirection("CARRIER");
    setShipType(CARRIER, gb, coordinates, inputCoords, direction);
    waitClear();
    //cout << "set BATTLESHIP: \n";
    direction = findDirection("BATTLESHIP");
    setShipType(BATTLESHIP, gb, coordinates, inputCoords, direction);
    waitClear();
    //cout << "set CRUISER: \n";
    direction = findDirection("CRUISER");
    setShipType(CRUISER, gb, coordinates, inputCoords, direction);
    waitClear();
    //cout << "set SUBMARINE: \n";
    direction = findDirection("SUBMARINE");
    setShipType(SUBMARINE, gb, coordinates, inputCoords, direction);
    waitClear();
    //cout << "set DESTROYER: \n";
    direction = findDirection("DESTROYER");
    setShipType(DESTROYER, gb, coordinates, inputCoords, direction);
}



void cheat(string name, vector <string> &coordinates)
{
    cout << name << "'s coordinates" << endl;
    for(int x = 0; x < coordinates.size(); x++)
        cout << coordinates[x] << " ";
    cout << " elements: " << coordinates.size() << endl;
}