#include <iostream>
#include "Definitions.h"
#include "Methods.h"
#include "Computer.h"
using namespace std;

void switchingBoards()
{
    pause();
    cls();
    cout << endl << "Switching boards in ";
    for(int i = 3; i > 0; i--)
    {
        cout << i << "...";
        sleep(1000);
        cout << "\b\b\b\b";
    }
}//end switchingBoards

void quickPlacement(Board *&playerBoard, Player *&playerShip)
{
    /*
     * method used for testing.  much less time intensive compared to
     *  placing ships for two players individually.
     */
    playerBoard->placeShip(7, 8, 'B', 'B', playerShip, 0);
    playerBoard->placeShip(2, 2, 'D', 'F', playerShip, 1);
    playerBoard->placeShip(0, 2, 'I', 'I', playerShip, 2);
    playerBoard->placeShip(5, 5, 'B', 'E', playerShip, 3);
    playerBoard->placeShip(8, 4, 'H', 'H', playerShip, 4);
}//end quickPlacement

void randomPlacement(Board *&playerBoard, Player *&playerShip)
{
    /*
     * method used for AI, as well as for the player should they choose
     *  to use it.  uses random number generator to pick a starting point
     *  and an orientation, and places a ship should the location be valid.
     */
    int row = 0, size = 0, orientation = 0 /*Use 0 for vertical, 1 for horizontal*/;
    char col = 'A';


    srand(time(NULL));
    for(int i = 0; i < MAX_SHIPS; i++)
    {
        size = playerShip->getShipSize(i);
        while(true)
        {
A:
            orientation = rand() % 2; // random number between 0 and 1
            row = rand() % 10; // random number between 0 and 9
            if((row+size) > 9)
                row -= size;
            col = rand() % 10 + 'A'; // random number between 65 and 74 (A through J)
            if((col+size) > 'J')
                col -= size;

            if(playerBoard->getIndex(row, col) != 0)
                goto A;

            /*
             * row and col are starting coordinates.
             * if orientation is vertical, then add ship size to row.
             *  check that it's valid, then playerBoard->placeShip(row, row+-shipSize, col, col, playerShip, shipSize)
             * else if orientation is horizontal, then add ship size to col.
             *  check that it's valid, then playerBoard->placeShip(row, row, col, col+-shipSize, playerShip, shipSize)
             */

            if(orientation == 0)
            {
                if(isValid(row, row+size-1, col, col, playerShip, playerBoard, size) && rowWithinBounds(row+size-1))
                {
                    playerBoard->placeShip(row, row+size-1, col, col, playerShip, i);
                    break;
                }
                else
                    goto A;
            }
            else if(orientation == 1)
            {
                if(isValid(row, row, col, col+size-1, playerShip, playerBoard, size) && colWithinBounds(col+size-1))
                {
                    playerBoard->placeShip(row, row, col, col+size-1, playerShip, i);
                    break;
                }
                else
                    goto A;
            }
            else
                pause();
        }
    }
}//end randomPlacement

void qempty(std::queue<int> &q)
{
    std::queue<int> empty;
    std::swap(q, empty );
    return;
}

void qprint(std::queue<int> &q)
{
    while (!q.empty()) {
        int _t = q.front();
        std::cout << _t << std::endl;
        q.pop();
    }
    return;
}

bool playerTurn(Board *playerOne, Board *playerTwo, Player *playerShip, int player)
{
    cls();

    //Signals that it is player 1's turn
    cout << "Player " << player << "'s Turn!" << endl << endl;

    //prints both boards relating to player 1
    cout << endl << "Enemy Board (Player 2)" << endl;
    //2 prints player 2's board with player 1's guesses about it.
    playerTwo->printBoard(2);

    cout << "Your Board" << endl;
    //1 prints player 1's own board
    playerOne->printBoard(1);

    //takes in player 1's guess about player 2's board.
    playerTwo->takeInGuess(playerShip);

    //checks for win (all ships sunk)
    if(playerTwo->checkGameOver() == 1)
    {
        cout << "Player " << player << " wins!" << endl;
        pause();
        return true;
        //if all ships have been sunk, the value of true is returned.
    }
    return false;
}//end playerTurn

bool playerTurn(Board *playerOne, Board *playerTwo, Computer *computerShip, int player)
{
    cls();

    //Signals that it is player 1's turn
    cout << "Player " << player << "'s Turn!" << endl << endl;

    //prints both boards relating to player 1
    cout << endl << "Enemy Board (Player 2)" << endl;
    //2 prints player 2's board with player 1's guesses about it.
    playerTwo->printBoard(2);

    cout << "Your Board" << endl;
    //1 prints player 1's own board
    playerOne->printBoard(1);

    //takes in player 1's guess about player 2's board.
    playerTwo->takeInCGuess(computerShip);

    //checks for win (all ships sunk)
    if(playerTwo->checkGameOver() == 1)
    {
        cout << "Player " << player << " wins!" << endl;
        pause();
        return true;
        //if all ships have been sunk, the value of true is returned.
    }
    return false;
}//end playerTurn

bool computerTurn(Board *playerBoard, Computer *compShip)
{
    bool flag = false;
    int row, col;
    //for all hits, change to
    //while(playerBoard->getIndex(row, convertColumn(col)) != 1) ...
    if (compShip->nextRows.size() == 0)
    {
        row = compShip->nextRowGuess;
        col = compShip->nextColGuess;
        while(playerBoard->getIndex(row, col) == 2 ||
                playerBoard->getIndex(row, col) == 3)
        {
            compShip->findNextCoordinates();
            row = compShip->nextRowGuess;
            col = compShip->nextColGuess;
        }
    }
    else
    {
        flag = true;
        row = compShip->nextRows.front();
        compShip->nextRows.pop();
        col = compShip->nextCols.front();
        compShip->nextCols.pop();
    }
    pause();
    cout << "The computer is firing at " << row << (char)(col+'A') << endl;
    pause();
    int shipfound = playerBoard->checkGuess(row, col, compShip);
    if(shipfound >= 0)
    {
        qempty(compShip->nextRows);
        qempty(compShip->nextCols);
        //cout << "Found " << compShip->getShipName(shipfound) << endl;
        flag = false;
    }
    else if (shipfound == -1)
    {
        if(flag)
        {
        }
        else
        {
            /* Debug */
            std::queue<int> deb;
            /* North */
            for (int i = 1; i < 5; ++i)
            {
                if ((row - i) < 0)
                {
                    break;
                }
                compShip->nextRows.push(row - i);
                deb.push(row - i);
                compShip->nextCols.push(col);
            }
            compShip->nextRows.push(-1);
            deb.push(-1);
            compShip->nextCols.push(-1);
            /* East */
            for (int i = 1; i < 5; ++i)
            {
                if ((col + i) > 9)
                {
                    break;
                }
                compShip->nextRows.push(row);
                deb.push(row);
                compShip->nextCols.push(col + i);
            }
            compShip->nextRows.push(-1);
            deb.push(-1);
            compShip->nextCols.push(-1);
            /* South */
            for (int i = 1; i < 5; ++i)
            {
                if ((row + i) > 9)
                {
                    break;
                }
                compShip->nextRows.push(row + i);
                deb.push(row + i);
                compShip->nextCols.push(col);
            }
            compShip->nextRows.push(-1);
            deb.push(-1);
            compShip->nextCols.push(-1);
            /* West */
            for (int i = 1; i < 5; ++i)
            {
                if ((col - i) < 0)
                {
                    break;
                }
                compShip->nextRows.push(row);
                deb.push(row);
                compShip->nextCols.push(col - i);
            }

            //qprint(deb);
        }
    }
    else
    {
        compShip->findNextCoordinates();
    }
    pause();
    if(playerBoard->checkGameOver() == 1)
    {
        cout << "You lost!" << endl;
        pause();
        return true;
    }
    return false;
}//end computerTurn

void randomPlacement(Board *&computerBoard, Computer *&computerShip)
{
    /*
     * method used for AI, as well as for the player should they choose
     *  to use it.  uses random number generator to pick a starting point
     *  and an orientation, and places a ship should the location be valid.
     */
    int row = 0, size = 0, orientation = 0 /*Use 0 for vertical, 1 for horizontal*/;
    char col = 'A';


    srand(time(NULL));
    for(int i = 0; i < MAX_SHIPS; i++)
    {
        size = computerShip->getShipSize(i);
        while(true)
        {
A:
            orientation = rand() % 2; // random number between 0 and 1
            row = rand() % 10; // random number between 0 and 9
            if((row+size) > 9)
                row -= size;
            col = rand() % 10 + 'A'; // random number between 65 and 74 (A through J)
            if((col+size) > 'J')
                col -= size;

            if(computerBoard->getIndex(row, col) != 0)
                goto A;

            /*
             * row and col are starting coordinates.
             * if orientation is vertical, then add ship size to row.
             *  check that it's valid, then playerBoard->placeShip(row, row+-shipSize, col, col, playerShip, shipSize)
             * else if orientation is horizontal, then add ship size to col.
             *  check that it's valid, then playerBoard->placeShip(row, row, col, col+-shipSize, playerShip, shipSize)
             */

            if(orientation == 0)
            {
                if(isValid(row, row+size-1, col, col, computerShip, computerBoard, size) && rowWithinBounds(row+size-1))
                {
                    computerBoard->placeCShip(row, row+size-1, col, col, computerShip, i);
                    break;
                }
                else
                    goto A;
            }
            else if(orientation == 1)
            {
                if(isValid(row, row, col, col+size-1, computerShip, computerBoard, size) && colWithinBounds(col+size-1))
                {
                    computerBoard->placeCShip(row, row, col, col+size-1, computerShip, i);
                    break;
                }
                else
                    goto A;
            }
            else
                pause();
        }
    }
}//end randomPlacement

bool playGame(int mode, int difficulty)
{
    //This is where the bulk of the game is played, calling methods and classes from other files.

    //A board object is created for both player 1 and player 2.
    Board *playerOne = new Board;
    Board *playerTwo = new Board;

    //A player object is created for both player 1 and player 2.
    Player *player1 = new Player;
    Player *player2 = new Player;

    Computer *computer1 = new Computer(difficulty);

    /*
     * The following code is executed for both PVP and PVC games
     */

    //Signals for player 1 to place his/her ships
    cout << "Player 1, it is time to place your ships!" << endl;
    //calls the initialShipPlacement method, to properly place the ships
    //initialShipPlacement(playerOne, player1);
    quickPlacement(playerOne, player1);
    //clears the screen between each player's turn, so that neither have an unfair advantage over the other.
    cls();

    /*
     * Here is where code differs based on game style:
     * For PVP,
     *  After ships are placed, players take turns firing at the other's
     *  board.  The game exits when all of one player's ships are sunk.
     * For PVC,
     *  There is no player 2, so the ships are placed randomly.  The player
     *  fires at the computer, and the computer uses programmed AI to fire at
     *  the player.  The game exits when either the user or the player has no
     *  ships left.
     */
    cout << mode << endl;
    switch(mode)
    {
    case 0:  //PVP
        //Signals for player 2 to place his/her ships
        cout << "Player 2, it is time to place your ships!" << endl;
        //calls the initialShipPlacement method, to properly place the ships
        //initialShipPlacement(playerTwo, player2);
        quickPlacement(playerTwo, player2);

        /*
         * this while loop checks to see if all ships are sunk, meaning that the
         *  game is over and a winner has been determined.
         */
        while(true)
        {
            if(playerTurn(playerOne, playerTwo, player2, 1))
                return true;
            switchingBoards();
            if(playerTurn(playerTwo, playerOne, player1, 2))
                return true;
            switchingBoards();
        }
        break;
    case 1:  //PVC
        //Signals for player 2 to place his/her ships
        cout << "The computer is now placing its ships." << endl;
        //calls the randomPlacement method to randomly place ships
        //randomPlacement(playerTwo, player2);
        //quickPlacement(playerTwo, player2);
        randomPlacement(playerTwo, computer1);

        /*
         * this while loop checks to see if all ships are sunk, meaning that the
         *  game is over and a winner has been determined.
         */
        while(true)
        {
            if(playerTurn(playerOne, playerTwo, computer1, 1))
                return true;
            if(computerTurn(playerOne, computer1))
                return true;
        }
        break;
    }

    pause();

    return false;

}//end playGame
