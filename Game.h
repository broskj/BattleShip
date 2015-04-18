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
    playerBoard->placeShip(1, 1, 'A', 'B', playerShip, 0);
    playerBoard->placeShip(2, 2, 'B', 'D', playerShip, 1);
    playerBoard->placeShip(0, 2, 'I', 'I', playerShip, 2);
    playerBoard->placeShip(5, 5, 'B', 'E', playerShip, 3);
    playerBoard->placeShip(8, 4, 'H', 'H', playerShip, 4);
}//end quickPlacement

// playerTurn for Player vs. Player
bool playerTurn(Board *playerOne, Board *playerTwo, Player *playerShip, int player)
{
    cin.clear();
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

    cin.clear();
    //checks for win (all ships sunk)
    if(playerTwo->checkGameOver() == 1)
    {
        pause();
        shipAnimation(player);
        pause();
        cls();
        return true;
        //if all ships have been sunk, the value of true is returned.
    }
    return false;
}//end playerTurn

// Player turn for Player vs. Computer
bool playerTurn(Board *playerOne, Board *playerTwo, Computer *computerShip, int player)
{
    cin.clear();
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

    cin.clear();
    //checks for win (all ships sunk)
    if(playerTwo->checkGameOver() == 1)
    {
        pause();
        shipAnimation(player);
        pause();
        cls();
        return true;
        //if all ships have been sunk, the value of true is returned.
    }
    return false;
}//end playerTurn

bool computerTurn(Board *playerBoard, Computer *compShip, Player *playerShip)
{
    cin.clear();
    int row, col;
    //for all hits, change to
    //while(playerBoard->getIndex(row, convertColumn(col)) != 1) ...
    if(compShip->difficulty == 2)
    {
        row = rand() % 10;
        col = rand() % 10;
        while(playerBoard->getIndex(row, col) != 1)
        {
            row = rand() % 10;
            col = rand() % 10;
        }
        pause();
    	cout << "The computer is firing at " << row << (char)(col+'A') << endl;
		pause();
        playerBoard->checkGuess(row, col, playerShip);
        pause();

        if(playerBoard->checkGameOver() == 1)
		{
            pause();
			shipAnimation(0);
			pause();
			cls();
			return true;
		}
		return false;
    }

	if (compShip->dcount == 0) /* Not currently firing at a ship */
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
	} else { /* Continue to fire at the ship we're firing at */
		row = compShip->nextRows.front();
		if (row == -1) {
			compShip->nextRows.pop();
			compShip->nextCols.pop();
			row = compShip->nextRows.front();
            compShip->dcount --;
            compShip->dflag = false;
		}

		compShip->nextRows.pop();
		col = compShip->nextCols.front();
		compShip->nextCols.pop();

	}
	while(playerBoard->getIndex(row, col) == 2 ||
            playerBoard->getIndex(row, col) == 3)
    {
        compShip->findNextCoordinates();
         if (compShip->dcount == 0) {
             row = compShip->nextRowGuess;
             col = compShip->nextColGuess;
         } else {
             if (compShip->nextRows.front() == -1) {
                 compShip->nextRows.pop();
                 compShip->nextCols.pop();
             }
             row = compShip->nextRows.front();
             col = compShip->nextCols.front();
             compShip->nextRows.pop();
             compShip->nextCols.pop();
         }
    }
A:
    pause();
    cout << "The computer is firing at " << row << (char)(col+'A') << endl;
    pause();

    int shipfound = playerBoard->checkGuess(row, col, playerShip);
    if (shipfound >= 0) /* Sink */
    {
        compShip->qempty(compShip->nextRows);
        compShip->qempty(compShip->nextCols);
        compShip->dflag = false;
        compShip->dcount = 0;
        //cout << "Found " << compShip->getShipName(shipfound) << endl;
    }
    else if (shipfound == -1) // Hit
    {
        if(compShip->dcount != 0) /* We're already targeting a ship. */
        {
            compShip->dflag = true;
        }
        else /* Set up for targeting a ship */
        {
			compShip->dcount = 4;
            /* North */
            for (int i = 1; i < 5; ++i)
            {
                if ((row - i) < 0) { break; }
                compShip->nextRows.push(row - i);
                compShip->nextCols.push(col);
            }
            compShip->nextRows.push(-1);
            compShip->nextCols.push(-1);
            /* East */
            for (int i = 1; i < 5; ++i)
            {
                if ((col + i) > 9) { break; }
                compShip->nextRows.push(row);
                compShip->nextCols.push(col + i);
            }
            compShip->nextRows.push(-1);
            compShip->nextCols.push(-1);
            /* South */
            for (int i = 1; i < 5; ++i)
            {
                if ((row + i) > 9) { break; }
                compShip->nextRows.push(row + i);
                compShip->nextCols.push(col);
            }
            compShip->nextRows.push(-1);
            compShip->nextCols.push(-1);
            /* West */
            for (int i = 1; i < 5; ++i)
            {
                if ((col - i) < 0) { break; }
                compShip->nextRows.push(row);
                compShip->nextCols.push(col - i);
            }


        }
    }
    else if(shipfound == -2)
    {
        compShip->changeDirection();
        row = compShip->nextRowGuess;
		col = compShip->nextColGuess;
		while(playerBoard->getIndex(row, col) == 2 ||
				playerBoard->getIndex(row, col) == 3)
		{
			compShip->findNextCoordinates();
			if (compShip->dcount == 0) {
                 row = compShip->nextRowGuess;
                 col = compShip->nextColGuess;
             } else {
                 if (compShip->nextRows.front() == -1) {
                     compShip->nextRows.pop();
                     compShip->nextCols.pop();
                 }
                 row = compShip->nextRows.front();
                 col = compShip->nextCols.front();
                 compShip->nextRows.pop();
                 compShip->nextCols.pop();
             }
		}
        goto A;
    }
    else /* Miss */
    {
        compShip->findNextCoordinates();

    }
    pause();
    if(playerBoard->checkGameOver() == 1)
    {
        pause();
        shipAnimation(0);
        pause();
        cls();
        return true;
    }
    return false;
}//end computerTurn

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

    cls();
    //Signals for player 1 to place his/her ships
    cout << "Player 1, it is time to place your ships!" << endl;
    //calls the initialShipPlacement method, to properly place the ships
    initialShipPlacement(playerOne, player1);
    //randomPlacement(playerOne, player1);
    //quickPlacement(playerOne, player1);
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
    switch(mode)
    {
    case 0:  //PVP
        //Signals for player 2 to place his/her ships
        cout << "Player 2, it is time to place your ships!" << endl;
        //calls the initialShipPlacement method, to properly place the ships
        initialShipPlacement(playerTwo, player2);
        //quickPlacement(playerTwo, player2);

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
        //calls the randomPlacement method to randomly place ships
        //quickPlacement(playerTwo, player2
        cls();
        cout << "The computer is now placing its ships";
        for(int i = 3; i > 0; i--)
		{
			cout << ". ";
			sleep(1000);
		}
        randomPlacement(playerTwo, computer1);

        /*
         * this while loop checks to see if all ships are sunk, meaning that the
         *  game is over and a winner has been determined.
         */
        while(true)
        {
            if(playerTurn(playerOne, playerTwo, computer1, 1))
                return true;
            if(computerTurn(playerOne, computer1, player1))
                return true;
        }
        break;
    }

    pause();

    return false;

}//end playGame
