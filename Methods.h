#ifndef METHODS_H_
#define METHODS_H_

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include "Player.h"
#include "Board.h"
#include "Definitions.h"
using namespace std;

/*
TODO:
*/

bool rowWithinBounds(int row)
{
    if(row < 0 || row > 9)
        return false;
    return true;
}//end rowWithinBounds

bool colWithinBounds(char col)
{
    if(col < 'A' || col > 'J')
        return false;
    return true;
}//end colWithinBounds

bool isValid(int startRow, int endRow, char startColumn, char endColumn, Player *playerShip, Board *playerBoard, int shipSize)
{
    for(int r = startRow; r <= endRow; r++)
    {
        for(int c = convertColumn(startColumn); c <= convertColumn(endColumn); c++)
        {
            if(playerBoard->getIndex(r, c) != 0 )
            {
                //indicates overlapping ships.
                //The board is reprinted, so that the player can see where they could alternatively place their ships
                cout << "Invalid ship placement, cannot overlap ships." << endl;
                return false;
            }
        }
    }

    if(startRow != endRow && startColumn != endColumn )
    {
        //indicates diagonal placement
        //cls();
        //playerBoard->printBoard(1);
        //The board is reprinted, so that the player can see where they could alternatively place their ships

        cout << "Invalid ship placement, cannot place diagonally." << endl;
        //pause();
        return false;
    }

    if(abs((float)(startRow - endRow))+1 != shipSize &&
            abs((float)(convertColumn(startColumn) - convertColumn(endColumn)))+1 !=
            shipSize)
    {

        //indicates an invalid ship size

        //cls();
        //playerBoard->printBoard(1);
        //The board is reprinted, so that the player can see where they could alternatively place their ships

        cout << "Invalid ship placement, ship must be of size " << shipSize << "." << endl;
        //pause();
        return false;
    }
    return true;
}//end isValid

void tutorialCoordinate(int expectedRow, int expectedCol)
{
	std::string guess;

	for(;;)
	{
		guess = "";
		std::cout << "Enter coordinate for guess: ";
		std::cin >> guess;
		if (guess.length() != 2)
		{
			std::cout << "Invalid coordinate entered. Coordinates should be two characters long." << std::endl;
			continue;
		}
		if(((guess.at(0)-'0') != expectedRow || (char)toupper(guess.at(1)) != (char)expectedCol))
		{
			std::cout << "Invalid coordinate entered. Enter " << expectedRow << (char)expectedCol << "." << std::endl;
			continue;
		}
		return;
	}
	//this infinite loop executes until the coordinates are value.
}

void randomPlacement(Board *&playerBoard, Player *&playerShip)
{
    /*
     * method used for the player should they choose to use it.  uses random 
     *  number generator to pick a starting point and an orientation, and 
     *  places a ship should the location be valid.
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

void randomPlacement(Board *&computerBoard, Computer *&computerShip)
{
    /*
     * method used for AI.  uses random number generator to pick a starting point
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

void initialShipPlacement(Board *&playerBoard, Player *&playerShip)
{
    //This method is used to do the initial ship placement for each player, at the start of the game
    //As parameters, it takes in a board object and a player object, corresponding to the same player

    int startRow = 0;
    int endRow = 0;
    char startColumn = 'A';
    char endColumn = 'A';
    string buffer;
    bool flag = false;
    
    cout << "Would you like to place your own ships? [y/n]" << endl;
    cin >> buffer;

    if(buffer.compare("n") == 0 || buffer.compare("N") == 0)
        randomPlacement(playerBoard, playerShip);
    else
    {
		for(int i = 0; i < MAX_SHIPS; i++)
		{
			//a for loop is used to iterate through the number of ships that needs to be placed

			do
			{
				if(!flag)
				{
					if(i != 0)
						cls();
					playerBoard->printBoard(1);
					//The player's board is printed, so they can see where they would like to place their ships
				}

				//Each player is prompted to enter the starting coordinate of the ship
				cout << "Enter starting coordinate for ship of size " << playerShip->getShipSize(i) << " " << "\n";
				cin >> startRow;

				//This loop is used to continually ask the user for a correct input value, if an incorrect value is entered.
				while (!rowWithinBounds(startRow))
				{
					cout << "Invalid entry, row must be between 0 and 9." << endl;
					cin >> startRow;
				}

				//The char that they entered is converted to an uppercase letter, in case they entered a lowercase letter.
				cin >> startColumn;
				startColumn = toupper(startColumn);

				//This loop is used to continually ask the user for a correct input value, if an incorrect value is entered.
				while(!colWithinBounds(startColumn))
				{
					cout << "Invalid entry, column must be between A and J." << endl;
					cin >> startColumn;
					startColumn = toupper(startColumn);
				}

				//Then the player is prompted for the ending coordinate of the ship
				cout << "Enter ending coordinate for ship of size " << playerShip->getShipSize(i) << " " << endl;
				cin >> endRow;

				//The loop checks and prompts the user until a valid input is given.
				while(!rowWithinBounds(endRow))
				{
					cout << "Invalid entry, row must be between 0 and 9." << endl;
					cin >> endRow;
				}

				//Finally, the user is prompted to enter the ending column of the ship
				cin >> endColumn;

				//The char that they entered is converted to an uppercase letter, in case they entered a lowercase letter.
				endColumn = toupper(endColumn);

				//Again, this loop is used to continually ask the user for a correct input value, if an incorrect value is entered.
				while(!colWithinBounds(endColumn))
				{
					cout << "Invalid entry, column must be between A and J." << endl;
					cin >> endColumn;
					endColumn = toupper(endColumn);
				}

				//flag used to indicate incorrect ship size, position, etc.
				flag = !isValid(startRow, endRow, startColumn, endColumn, playerShip, playerBoard, playerShip->getShipSize(i));

			}
			while(flag);

			//once the user has sucessfully entered the columns and rows for their ships, the ship can officially be placed, using the place ship method.
			playerBoard->placeShip(startRow, endRow, startColumn, endColumn, playerShip, i);

		}
	}
}//end initialShipPlacement

//This is a tuturial that shows the users how to play the game. It is an option on the menu
void runTutorial()
{

    //Board objects are created for the tutorial
    Board *board1 = new Board();
    Board *board2 = new Board();

    //Player objects are created for the tutorial
    Player *computer1 = new Player;
    Player *computer2 = new Player;

    //The tutorial begins to walk the player step by step on how to play the game
    cout << "Welcome to the tutorial!" << endl;
    cout << "First, let's begin by placing your ships." << endl << endl;
    pause();
    cls();

    //prints the board for the user to see.
    board1->printBoard(1);

    //The user is prompted to enter the starting row to place a ship in a predetermined location
    cout << "Our first ship is of size 2.  You'll need to first enter your ship's\n" <<
         "starting coordinate.\nEnter '7B'."<< endl;

	tutorialCoordinate(7, 'B');
	
    cls();
    board1->printBoard(1);

    //The user is prompted to enter the ending row to place a ship in a predetermined location
    cout << "Now you'll enter the ship's ending coordinate.\nEnter '8B'." << endl;
    
    tutorialCoordinate(8, 'B');

    //once the user has entered the points successfully, the ship is added to this location
    board1->placeShip(7, 8, 'B', 'B', computer1, 0);

    cls();
    board1->printBoard(1);
    cout << "Nice, you've placed a ship.  The process for the others is the same,\n" <<
         "we'll go ahead and place your remaining ships." << endl << endl;

    //The tutorial demonstrates ship placement, by helping the user place one ship, and goes ahead and places the rest for them.
    board1->placeShip(2, 2, 'D', 'F', computer1, 1);
    board1->placeShip(0, 2, 'I', 'I', computer1, 2);
    board1->placeShip(5, 5, 'B', 'E', computer1, 3);
    board1->placeShip(8, 4, 'H', 'H', computer1, 4);

    pause();
    cls();
    board1->printBoard(1);

    cout << "Here is your full board.  Now it's time for your opponent to place\n" <<
         "their ships.  We'll take care of that for you." << endl << endl;

    //The opponent's ships are placed on the respective board object
    board2->placeShip(8, 8, 'H', 'G', computer2, 0);
    board2->placeShip(7, 5, 'B', 'B', computer2, 1);
    board2->placeShip(1, 3, 'H', 'H', computer2, 2);
    board2->placeShip(0, 0, 'D', 'G', computer2, 3);
    board2->placeShip(3, 7, 'J', 'J', computer2, 4);

    pause();
    cls();

    //Two boards are printed for the user. Their own board, and that with their enemy's ships abstracted.

    cout << endl << "Enemy Board" << endl;
    board2->printBoard(2);
    cout << "Your Board" << endl;
    board1->printBoard(1);

    //A message is printed educating the user on the different boards.
    cout << "Here you see your board on top and your opponent's board without " <<
         "their ships.\nYour opponent sees a similar screen during their turn.  " <<
         "Now, your goal is\nto sink the enemy ships.  Let's take a shot at" <<
         " 2B." << endl << endl;

    //This stage of the tutorial takes the user through how to enter points to guess a ship
	tutorialCoordinate(2, 'B');
	
    board2->checkGuess(2, convertColumn('B'), computer2);
    cout << endl;
    pause();
    cls();

    //The guess was a miss, so now it's time for the opponent to take a shot

    cout << endl << "Enemy Board" << endl;
    board2->printBoard(2);
    cout << "Your Board" << endl;
    board1->printBoard(1);
    cout << "That spot was a miss, oh well.  Now your opponent is going to fire at 0A." << endl << endl;

    pause();
    board1->checkGuess(0, convertColumn('A'), computer1);
    cout << endl;
    pause();
    cls();

    //The enemy then hits one of the player's ships

    cout << endl << "Enemy Board" << endl;
    board2->printBoard(2);
    cout << "Your Board" << endl;
    board1->printBoard(1);
    cout << "Your ship was hit!  In the interest of time, we'll assume you've grasped\n" <<
         "the general idea and fast forward a bit." << endl << endl;
    pause();

    for(int i = 1; i < 10; i++)
    {
        board1->checkGuess(i, i, computer1);
        if(i < 6)
            board1->checkGuess(9-i, i, computer1);
    }

    //2-length ship
    board2->checkGuess(8, convertColumn('G'), computer2);
    board2->checkGuess(8, convertColumn('H'), computer2);

    //first 3-length ship
    board2->checkGuess(5, convertColumn('B'), computer2);
    board2->checkGuess(6, convertColumn('B'), computer2);
    board2->checkGuess(7, convertColumn('B'), computer2);

    //second 3-length ship
    board2->checkGuess(1, convertColumn('H'), computer2);
    board2->checkGuess(2, convertColumn('H'), computer2);
    board2->checkGuess(3, convertColumn('H'), computer2);

    //4-length ship
    board2->checkGuess(0, convertColumn('D'), computer2);
    board2->checkGuess(0, convertColumn('E'), computer2);
    board2->checkGuess(0, convertColumn('F'), computer2);
    board2->checkGuess(0, convertColumn('G'), computer2);

    //5-length ship, minus one segment
    board2->checkGuess(3, convertColumn('J'), computer2);
    board2->checkGuess(4, convertColumn('J'), computer2);
    board2->checkGuess(5, convertColumn('J'), computer2);
    board2->checkGuess(6, convertColumn('J'), computer2);
    //board2->checkGuess(8, convertColumn('G'), computer2);

    //maybe add some random misses

    cls();
    cout << endl << "Enemy Board" << endl;
    board2->printBoard(2);
    cout << "Your Board" << endl;
    board1->printBoard(1);

    cout << "Okay!  The enemy now has one ship left.  Sink it by firing at 7J." << endl;
    
    tutorialCoordinate(7, 'J');
    
    board2->checkGuess(7, convertColumn('J'), computer2);
    cout << endl;
    pause();

    cls();
    cout << endl << "Enemy Board" << endl;
    board2->printBoard(2);
    cout << "Your Board" << endl;
    board1->printBoard(1);

    cout << "Player 1 wins!" << endl;

    //tutorial finished
    cout << "You're now all set to play!  Returning to main menu." << endl << endl;
    pause();
    cls();

}//end runTutorial

void printInstructions()
{
    //This method prints the instructions for the user, from the menu

    cout << "PVP Directions: " << endl;
    cout << "Object of the game: be the first to sink all 5 of your opponent's ships." << endl << endl;
    pause();
    cls();

    cout << "Prepare for Battle: " << endl;
    cout << "You and your opponent sit across from each other and pass the laptop between\n moves." << endl;
    cout << "Follow the directions to place each of your 5 ships on your ocean grid.\n";
    cout << "Ships are placed by entering the column and row coordinates for both the bow\n and stern of each ship." << endl;
    cout << "Ships may be placed in any horizontal or vertical position within the grid.\n They may not, however, be placed diagonally.\n";
    cout << "Ships may not be placed so that they overlap the edge of the grid or another\n ship.\n";
    cout << "Ship positions will remain constant throughout the gameplay.\n";
    cout << "Now pass the computer to allow your opponent to place their ships.\n\n";
    pause();
    cls();

    cout << "Gameplay:\n";
    cout << "On your display will be both yours and your opponent's boards.\n";
    cout << "Your board will display ship locations with an 'S'.  Open water is marked '~'.\n";
    cout << "Your opponent's board will initially only display open water (~).\n";
    cout << "On your turn, you will enter the row and column coordinates for a shot at your\n opponent's ships.\n";
    cout << "If the shot hits one of their ships, your display for their board will record\n an 'X' where the hit took place.\n";
    cout << "If the shot misses any ships and lands in open water, the board will record an\n 'O'.\n";
    cout << "The computer is now passed to your opponent and they likewise try to hit your\n ships.\n";
    cout << "\nRepeat this process of shooting and switching until either player sinks all of\n the other player's ships and wins.\n";
    pause();
    cls();

    //cout << "Returning to main menu." << endl;

    cout << "Player vs. Computer Directions:" << endl;
    cout << "Object of the game: sink the computer's ships before it sinks yours." << endl << endl;
    pause();
    cls();

    cout << "Prepare for Battle: " << endl;
    cout << "Follow the directions to place each of your 5 ships on your ocean grid.\n";
    cout << "Ships are placed by entering the column and row coordinates for both the bow\n and stern of each ship." << endl;
    cout << "Ships may be placed in any horizontal or vertical position within the grid.\n They may not, however, be placed diagonally.\n";
    cout << "Ships may not be placed so that they overlap the edge of the grid or another\n ship.\n";
    cout << "Ship positions will remain constant throughout the gameplay.\n";
    cout << "The computer will automatically place its own ships.\n\n";
    pause();
    cls();

    cout << "Gameplay:\n";
    cout << "Your screen will display both yours and the computer's boards.\n";
    cout << "Your board will display whip location with an S . Open water is marked: ~\n";
    cout << "The computer's board will initially only display open water ~.\n";
    cout << "You will enter the row and column coordinates for a shot at the computer's ships\n";
    cout << "If the shot hits one of its ships, your display for its board will\n";
    cout << " record an X where the hit took place.\n";
    cout << "If the shot misses any ships and lands in open water, the board\n";
    cout << " will record an O.\n";
    cout << "Then the computer takes a shot at your ships.\n";
    cout << "Any hits on your ships will be marked X and any misses marked O.\n";
    pause();
    cls();

    cout << "Continue entering shot coordinates until you sink all the computer's\n";
    cout << "ships and win or have all your ships sunk and lose.\n";
    cout << "\nReturning to main menu." << endl;
    pause();
    cls();

}//end printInstructions

/*void shipAnimation(int player)
{

    vector<string> lines;
    ifstream file("ship.txt");
    string str;

    while(std::getline(file, str))
    {
        lines.push_back(str);
    }

    for(int j=0; j<44; j++)
    {
        for(int k=j; k>0; k--)
            cout<<endl;
        for(int i=0; i<lines.size(); i++)
        {
            cout<<lines[i]<<endl;
        }
        cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" <<endl;
        if(player != 0)
            cout << "Player " << player << " wins!" << endl;
        else
            cout << "YOU LOSE, COMPUTER WINS" <<endl;
        lines.pop_back();
        sleep(1000);
        cls();
    }
}// end shipAnimation*/

#endif
