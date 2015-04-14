#ifndef PLAYER_H_
#define PLAYER_H_

const int MAX_SHIPS = 5;
//The number of ships is set to 5

class Player
{

public:
    //a 2 dimensional array of ships will be created
    int **ships;
    std::string *names;
    bool *isSunk;
    int **rows;
    int ** cols;

    Player()
    {

        //the constructor for a player object creates a 2-dimensional array for ships,
        // and a one dimensional parallel aray for ship names

        ships = new int *[MAX_SHIPS];
        rows = new int *[MAX_SHIPS];
        cols = new int *[MAX_SHIPS];

        //names = new std::string[MAX_SHIPS] {"Destroyer" /* size 2 */,
        //                                    "Submarine" /* size 3 */,
        //                                    "Frigate"   /* size 3 */,
        //                                    "Battleship"/* size 4*/,
        //                                    "Carrier"   /* size 5*/
        //                                   };

        names = new std::string[MAX_SHIPS];
        names[0] = std::string("Destroyer");
        names[1] = std::string("Submarine");
        names[2] = std::string("Frigate");
        names[3] = std::string("Battleship");
        names[4] = std::string("Carrier");
        isSunk = new bool [MAX_SHIPS];

        //each row of the array holds the length of a ship: 2, 3, 3, 4, 5

        ships[0] = new int[2]; /* destroyer */
        ships[1] = new int[3]; /* submarine */
        ships[2] = new int[3]; /* frigate */
        ships[3] = new int[4]; /* battleship */
        ships[4] = new int[5]; /* carrier */

        rows[0] = new int[2]; /* destroyer */
        rows[1] = new int[3]; /* submarine */
        rows[2] = new int[3]; /* frigate */
        rows[3] = new int[4]; /* battleship */
        rows[4] = new int[5]; /* carrier */

        cols[0] = new int[2]; /* destroyer */
        cols[1] = new int[3]; /* submarine */
        cols[2] = new int[3]; /* frigate */
        cols[3] = new int[4]; /* battleship */
        cols[4] = new int[5]; /* carrier */

        for(int i = 0; i < MAX_SHIPS; i++)
            isSunk[i] = false;
    }

    int getShipSize(int index)
    {
        switch(index)
        {
        case 0:
            return 2;
        case 1:
            return 3;
        case 2:
            return 3;
        case 3:
            return 4;
        case 4:
            return 5;
        default:
            return -1;
        }
    }

    std::string getShipName(int index)
    {
        //returns name of ship at ships[index]
        return names[index];
    }

    bool sunk(int index, int row, int col)
    {
        /*
         * the sunk method is only called when a ship is hit.  therefore,
         *  we need to change the value of ships to indicate it was hit.
         */

        for(int i = 0; i < MAX_SHIPS; i++)
        {
            if(row == rows[index][i] && col == cols[index][i])
            {
                /* indicates recent hit was on the [index]th ship */
                ships[index][i] = 3; /* declare the hit at that spot*/
                if(!isSunk[index])
                {
                    for(int i = 0; i < getShipSize(index); i++)
                    {
                        if(ships[index][i] != 3)
                            return false;
                    }
                    isSunk[index] = true;
                    return true;
                }
            }
        }
        return false;
    }
};//end class Player
#endif
