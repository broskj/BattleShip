#ifndef COMPUTER_H_
#define COMPUTER_H_

#include "Definitions.h"

class Computer : public Player
{
public:
    int **ships;
    std::vector<int> rowPattern;
    std::vector<int> colPattern;
    std::queue<int> nextRows;
    std::queue<int> nextCols;
    std::vector<int> prevRows;
    std::vector<int> prevCols;
    std::string *names;
    bool *isSunk;
    int **rows;
    int **cols;
    int nextRowGuess;
    int nextColGuess;
    int difficulty;
    bool lastWasHit;
    int dcount;
    bool dflag;

void qempty(std::queue<int> &q)
{
    std::queue<int>().swap(q);
    this->dcount = 0;
    this->dflag = false;
    return;
}

	void qprint(std::queue<int> &q)
	{
    while (!q.empty()) {
        q.pop();
    }
    return;
}

    Computer(int mode)
    {
        lastWasHit = false;
        srand((time(NULL)));
        difficulty = mode;
        ships = new int *[MAX_SHIPS];
        rows = new int *[MAX_SHIPS];
        cols = new int *[MAX_SHIPS];
        names = new std::string[MAX_SHIPS];
        isSunk = new bool [MAX_SHIPS];
        dcount = 0;
        dflag = false;

        names[0] = std::string("Destroyer"); /* size 2 */
        names[1] = std::string("Submarine"); /* size 3 */
        names[2] = std::string("Frigate"); /* size 3 */
        names[3] = std::string("Battleship"); /* size 4*/
        names[4] = std::string("Carrier"); /* size 5*/

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
        if(difficulty == -1)
        {
            //do nothing, PvP
        }
        else if(difficulty == 0)
        {
            nextRowGuess = rand() % 10;
            nextColGuess = rand() % 10;
        }
        else if(difficulty == 1) // hard
        {
            for(int i = 9; i >= 0; i--)
            {
                rowPattern.push_back(i);
                colPattern.push_back(9-i);
            }
            for(int i = 9; i >= 0; i--)
            {
                rowPattern.push_back(i);
                colPattern.push_back(i);
            }

            nextRowGuess = rowPattern.back();
            nextColGuess = colPattern.back();
        }
        else if(difficulty == 2)
        {
			//do nothing, impossible mode
		}
        else
            std::cout << "Something happened Computer.h" << std::endl;
    }//end Computer

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
    }//end getShipSize

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
    }//end sunk

	void changeDirection(void)
	{
		int s = this->nextRows.front();
		while(s != -1) {
			this->nextRows.pop();
			this->nextCols.pop();
			s = this->nextRows.front();
		}
		this->nextRows.pop();
		this->nextCols.pop();
        this->dcount--;
        this->dflag=false;
	}

    void findNextCoordinates(void)
    {
        if(difficulty == 0)
        {
            nextRowGuess = rand() % 10;
            nextColGuess = rand() % 10;
        }
        else if(difficulty == 1)
        {
            if(rowPattern.size() > 0)
            {
                nextRowGuess = rowPattern.back();
                nextColGuess = colPattern.back();
            }
            else
            {
                nextRowGuess = rand() % 10;
                nextColGuess = rand() % 10;
            }
		}
        if (dcount == 0 && difficulty == 1) {
			// We're actually going to use the stored values, so pop them
			// so that we have fresh ones next time.
			if(rowPattern.size() > 0)
                rowPattern.pop_back();
            if(colPattern.size() > 0)
                colPattern.pop_back();
            return;
        }


        switch (dcount) {
        case 4:
            if (dflag) { // We got a hit going North, so let's switch to South.
                /* Remove (what's effectively East) */
                this->changeDirection();
            } // Now remove (effectively the remaining North coords)
            this->changeDirection();
            return;
        case 3:
            if (dflag) { // We got a hit going East, so let's switch to West.
                /* Remove (what's effectively South) */
                this->changeDirection();
            }// Now remove (effectively the remaining East coords)
            this->changeDirection();
            return;
        case 2: // Miss going South, so let's switch to West.
            // Now remove (effectively the remaining South coords)
            if (dflag) {
                this->qempty(this->nextRows);
                this->qempty(this->nextCols);
			} else {
                this->changeDirection();
                return;
			}
        default:
			this->qempty(this->nextRows);
			this->qempty(this->nextCols);
            return;
        }

        return;
    }//end findNextCoordinates

};//end class Computer

#endif
