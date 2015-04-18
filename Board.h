#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <stdlib.h>
#include "Definitions.h"
#include "Computer.h"

using namespace std;

//For traditonal play, the number of rows and columns is predefined to be 10
const int ROWS = 10;
const int COLUMNS = 10;

//Converts the column to its corresponding integer value in the array
int convertColumn(char column);

//Board class - holds 2D array that represents a player's board
class Board
{

public:
    int **board;

    /*Constructor for the board class
    Each board object consists of a 2-dimensional 10 by 10 array.*/

    Board()
    {

        board = new int *[ROWS];

        for(int i = 0; i < ROWS; i++)
            board[i] = new int[10];

        //The elements in the array are all initialized to zero
        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                board[i][j] = 0;
            }
        }
    }//end Board()

    //A method of the board class that prints the board
    void printBoard(int type)
    {

        //prints the top of the board, with the coordinates easily visible
        cout << "---------------------------" << endl;
        cout << "    A B C D E F G H I J"     << endl;
        cout << "---------------------------" << endl;

        if(type == 1)
        {

            //Type 1 means that the board will be printed as is, for the player to see their own board.

            for(int i = 0; i < ROWS; i++)
            {

                cout << i << "\t\b\b\b\b";

                /*
                 * A note about the code system: Code 0 means that there is no ship placed here, and it has not been guessed yet.
                 *  When the board is printed, 0 is printed as a "~", to emulate the waves in the ocean.
                 *  Code 1 means that There is a ship in this location that has not yet been hit. When printed, it is printed as an "S".
                 *  Code 2 means that there is no ship in this location, but that this location has been guessed. When printed, it is printed as an "O".
                 *  Code 3 means that there is a ship in this location that has already been hit. When printed, it is printed as an "X".
                 */

                for(int j = 0; j < COLUMNS; j++)
                {
                    if(this->board[i][j] == 0)
                        cout << "~";
                    else if(this->board[i][j] == 1)
                        cout << "S";
                    else if(this->board[i][j] == 2)
                        cout << "O";
                    else
                        cout << "X";
                    cout << " ";
                }

                cout << "  " << i;

                cout << endl;

            }
        }

        else if(type == 2)
        {

            //Type 2 prints the board for the opposite player. Doens't use code 1. Abstracts the other player's ships. "Enemy ships" Printing.

            for(int i = 0; i < ROWS; i++)
            {

                cout << i << "\t\b\b\b\b";

                for(int j = 0; j < COLUMNS; j++)
                {
                    if(this->board[i][j] == 0)
                        cout << "~";
                    else if(this->board[i][j] == 1)
                        //although there is a ship in this location, it is abstracted as a wave, "~"
                        cout << "~";
                    else if(this->board[i][j] == 2)
                        cout << "O";
                    else
                        cout << "X";
                    cout << " ";
                }

                cout << "  " << i;

                cout << endl;
            }
        }

        //prints the bottom of the board, with the coordinates easily visible
        cout << "---------------------------" << endl;
        cout << "    A B C D E F G H I J"     << endl;
        cout << "---------------------------" << endl;

    }//end printBoard

    void takeInGuess(Player *player)
    {
        std::string guess;

        for(;;)
        {
            guess = "";
            std::cout << "Enter coordinate for guess: ";
            std::cin >> guess;
            if(guess.compare("rand") == 0)
            {
                checkGuess(rand() % 10, rand() % 10, player);
                break;
            }
            else if (guess.length() != 2)
            {
                std::cout << "Invalid coordinate entered. Coordinates should be two characters long." << std::endl;
                continue;
            }
            switch (guess.at(0))
            {
            case '0':
                break;
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                break;
            case '9':
                break;
            default:
                std::cout << "Invalid row entered. Rows should be 0-9." << std::endl;
                continue;
            }
            switch (toupper((guess).at(1)))
            {
            case 'A':
                break;
            case 'B':
                break;
            case 'C':
                break;
            case 'D':
                break;
            case 'E':
                break;
            case 'F':
                break;
            case 'G':
                break;
            case 'H':
                break;
            case 'I':
                break;
            case 'J':
                break;
            default:
                std::cout << "Invalid column entered. Columns should be A-J." << std::endl;
                continue;
            }
            if(checkGuess((int)(guess.at(0) - '0'), (int)toupper(guess.at(1))-'A', player) == -2)
            {
                continue; // Re-enter coordinates.
            }
            break;
        }
        //this infinite loop executes until the coordinates are value.

    }//end takeInGuess

    int checkGuess(int row, int column, Player *player)
    {
        //This method takes in the values as ints for the row and column that the specified player wishes to guess about their opponent

        if(this->board[row][column] == 1)
        {
            //A code of 1 means that there is a ship in this location that has not yet been hit.
            //Now that this location has been guessed, it is marked as a hit (3)
            //A message is displayed stating that they have hit a ship.

            cout << "Hit!\n";
            this->board[row][column] = 3;
            for(int i = 0; i < 5; i++)
            {
                bool x = player->sunk(i, row, column);
                if(x)
                {
                    //A check is done to see if all of the positions for this particular ship have been hit. If so, the ship was sunk and a message is displayed.
                    //switch(player->getShipSize(index)) cout << "You've sunk their Battleship!; << endl;
                    cout<<"You just sunk their " << player->getShipName(i) << "!"<<endl;
                    return i; // signifies sunken ship
                }
            }
            return -1;
        }

        else if((this->board[row][column] == 2) || (this->board[row][column] == 3))
        {
            //A code of 2 means that there is a ship in this location that has already been guessed
            //If this is the case, a message will be displayed and the player will be prompted to enter another guess.

            cout << "Invalid guess. You have already guessed this location." << endl;
            return -2;
        }

        else
        {
            //If the above statements aren't executed, that means that the location guessed was a miss.
            //The location is changed to a 2, indicating that there was a guess, without hitting a ship
            //A message is displayed stating this for the user.

            cout << "Miss!\n";
            this->board[row][column] = 2;
        }
        return -3;
        //If the guess was successful, meaning the player hadn't already guessed that location, the true is returned, indicating so.

    }//end checkGuess

    // takes in the Computer's next guess
    void takeInCGuess(Computer *computer)
    {
        std::string guess;

        for(;;)
        {
            guess = "";
            std::cout << "Enter coordinate for guess: ";
            std::cin >> guess;
            if(guess.compare("rand") == 0)
            {
                checkGuess(rand() % 10, rand() % 10, computer);
                break;
            }
            else if (guess.length() != 2)
            {
                std::cout << "Invalid coordinate entered. Coordinates should be two characters long." << std::endl;
                continue;
            }
            switch (guess.at(0))
            {
            case '0':
                break;
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                break;
            case '9':
                break;
            default:
                std::cout << "Invalid row entered. Rows should be 0-9." << std::endl;
                continue;
            }
            switch (toupper((guess).at(1)))
            {
            case 'A':
                break;
            case 'B':
                break;
            case 'C':
                break;
            case 'D':
                break;
            case 'E':
                break;
            case 'F':
                break;
            case 'G':
                break;
            case 'H':
                break;
            case 'I':
                break;
            case 'J':
                break;
            default:
                std::cout << "Invalid column entered. Columns should be A-J." << std::endl;
                continue;
            }
            if(checkCGuess((int)(guess.at(0) - '0'), (int)toupper(guess.at(1))-'A', computer) == -2)
            {
                continue; // Re-enter coordinates.
            }
            break;
        }
        //this infinite loop executes until the coordinates are value.

    }//end takeInCGuess

    int checkCGuess(int row, int column, Computer *computer)
    {
        //This method takes in the values as ints for the row and column that the specified player wishes to guess about their opponent

        if(this->board[row][column] == 1)
        {
            //A code of 1 means that there is a ship in this location that has not yet been hit.
            //Now that this location has been guessed, it is marked as a hit (3)
            //A message is displayed stating that they have hit a ship.

            cout << "Hit!\n";
            this->board[row][column] = 3;
            for(int i = 0; i < 5; i++)
            {
                bool x = computer->sunk(i, row, column);
                if(x)
                {
                    //A check is done to see if all of the positions for this particular ship have been hit. If so, the ship was sunk and a message is displayed.
                    //switch(player->getShipSize(index)) cout << "You've sunk their Battleship!; << endl;
                    cout<<"You just sunk their " << computer->getShipName(i) << "!"<<endl;
                    return i; // signifies sunken ship
                }
            }
            return -1;
        }

        else if((this->board[row][column] == 2) || (this->board[row][column] == 3))
        {
            //A code of 2 means that there is a ship in this location that has already been guessed
            //If this is the case, a message will be displayed and the player will be prompted to enter another guess.

            cout << "Invalid guess. You have already guessed this location." << endl;
            return -2;
        }

        else
        {
            //If the above statements aren't executed, that means that the location guessed was a miss.
            //The location is changed to a 2, indicating that there was a guess, without hitting a ship
            //A message is displayed stating this for the user.

            cout << "Miss!\n";
            this->board[row][column] = 2;
        }
        return -3;
        //If the guess was successful, meaning the player hadn't already guessed that location, the true is returned, indicating so.

    }//end checkGuess

    void placeShip(int startRow, int endRow, char startC, char endC, Player *playership, int index)
    {
        int size = playership->getShipSize(index);
        //This method is used to place the ships in the locations that the user specifies.
        //The values for the starting and ending columns and rows are passed as parameters, as well as the size of the ship and the player object that is placing the ship

        //The column positions, as entered by the user are converted to their respective integer values.
        int startColumn = convertColumn(startC), endColumn = convertColumn(endC);

        int j=1;

        //if the size of the ship is 2...
        if(size == 2)
        {
            //The location of the specified coordinates are changed to 1, meaning a ship exists at this location that hasn't been hit.
            //This also indicates to the ship class that a specific sized ship has been placed, whose coordinates are tracked, to indicate whether a ship has been sunk, later in the game.
            this->board[startRow][startColumn] = 1;
            playership->ships[index][0] = this->board[startRow][startColumn];
            playership->rows[index][0] = startRow;
            playership->cols[index][0] = startColumn;
            this->board[endRow][endColumn] = 1;
            playership->ships[index][1] = this->board[endRow][endColumn];
            playership->rows[index][1] = endRow;
            playership->cols[index][1] = endColumn;
        }

        //if the size of the ship is 3...
        else if(size == 3)
        {
            this->board[startRow][startColumn] = 1;
            playership->ships[index][0] = this->board[startRow][startColumn];
            playership->rows[index][0] = startRow;
            playership->cols[index][0] = startColumn;
            this->board[endRow][endColumn] = 1;
            playership->ships[index][2] = this->board[endRow][endColumn];
            playership->rows[index][2] = endRow;
            playership->cols[index][2] = endColumn;

            //This sequence of checks is done to account for the different number of ways that the user could enter the coordinates.
            if(startRow == endRow && startColumn < endColumn)
            {
                for(int i = startColumn + 1; i < endColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    playership->ships[index][i] = this->board[startRow][i];
                    playership->rows[index][1] = startRow;
                    playership->cols[index][1] = i;
                }
            }

            else if(startRow == endRow && startColumn > endColumn)
            {
                for(int i = endColumn + 1; i < startColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    playership->ships[index][i] = this->board[startRow][i];
                    playership->rows[index][1] = startRow;
                    playership->cols[index][1] = i;
                }
            }

            else if(startColumn == endColumn && startRow < endRow)
            {
                for(int i = startRow + 1; i < endRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    playership->ships[index][1] = this->board[i][startColumn];
                    playership->rows[index][1] = i;
                    playership->cols[index][1] = startColumn;
                }
            }

            else if(startColumn == endColumn && startRow > endRow)
            {
                for(int i = endRow + 1; i < startRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    playership->ships[index][1] = this->board[i][startColumn];
                    playership->rows[index][1] = i;
                    playership->cols[index][1] = startColumn;
                }
            }
        }

        //if the size of the ship is 4...
        else if(size == 4)
        {
            this->board[startRow][startColumn] = 1;
            playership->ships[index][0] = this->board[startRow][startColumn];
            playership->rows[index][0] = startRow;
            playership->cols[index][0] = startColumn;
            this->board[endRow][endColumn] = 1;
            playership->ships[index][3] = this->board[endRow][endColumn];
            playership->rows[index][3] = endRow;
            playership->cols[index][3] = endColumn;

            if(startRow == endRow && startColumn < endColumn)
            {
                for(int i = startColumn + 1; i < endColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    playership->ships[index][j] = this->board[startRow][i];
                    playership->rows[index][j] = startRow;
                    playership->cols[index][j] = i;
                    j++;
                }
            }

            else if(startRow == endRow && startColumn > endColumn)
            {
                for(int i = endColumn + 1; i < startColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    playership->ships[index][j] = this->board[startRow][i];
                    playership->rows[index][j] = startRow;
                    playership->cols[index][j] = i;
                    j++;
                }
            }

            else if(startColumn == endColumn && startRow < endRow)
            {
                for(int i = startRow + 1; i < endRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    playership->ships[index][j] = this->board[i][startColumn];
                    playership->rows[index][j] = i;
                    playership->cols[index][j] = startColumn;
                    j++;
                }
            }

            else if(startColumn == endColumn && startRow > endRow)
            {
                for(int i = endRow + 1; i < startRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    playership->ships[index][j] = this->board[i][startColumn];
                    playership->rows[index][j] = i;
                    playership->cols[index][j] = startColumn;
                    j++;
                }
            }
        }

        //if the size of the ship is 5..
        else if(size == 5)
        {
            this->board[startRow][startColumn] = 1;
            playership->ships[index][0] = this->board[startRow][startColumn];
            playership->rows[index][0] = startRow;
            playership->cols[index][0] = startColumn;
            this->board[endRow][endColumn] = 1;
            playership->ships[index][4] = this->board[endRow][endColumn];
            playership->rows[index][4] = endRow;
            playership->cols[index][4] = endColumn;

            if(startRow == endRow && startColumn < endColumn)
            {
                for(int i = startColumn + 1; i < endColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    playership->ships[index][j] = this->board[startRow][i];
                    playership->rows[index][j] = startRow;
                    playership->cols[index][j] = i;
                    j++;
                }
            }

            else if(startRow == endRow && startColumn > endColumn)
            {
                for(int i = endColumn + 1; i < startColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    playership->ships[index][j] = this->board[startRow][i];
                    playership->rows[index][j] = startRow;
                    playership->cols[index][j] = i;
                    j++;
                }
            }

            else if(startColumn == endColumn && startRow < endRow)
            {
                for(int i = startRow + 1; i < endRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    playership->ships[index][j] = this->board[i][startColumn];
                    playership->rows[index][j] = i;
                    playership->cols[index][j] = startColumn;
                    j++;
                }
            }

            else if(startColumn == endColumn && startRow > endRow)
            {
                for(int i = endRow + 1; i < startRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    playership->ships[index][j] = this->board[i][startColumn];
                    playership->rows[index][j] = i;
                    playership->cols[index][j] = startColumn;
                    j++;
                }
            }
        }

    }//end placeShip

    void placeCShip(int startRow, int endRow, char startC, char endC, Computer *compShip, int index)
    {
        int size = compShip->getShipSize(index);
        //This method is used to place the ships in the locations that the user specifies.
        //The values for the starting and ending columns and rows are passed as parameters, as well as the size of the ship and the player object that is placing the ship

        //The column positions, as entered by the user are converted to their respective integer values.
        int startColumn = convertColumn(startC), endColumn = convertColumn(endC);

        int j=1;

        //if the size of the ship is 2...
        if(size == 2)
        {
            //The location of the specified coordinates are changed to 1, meaning a ship exists at this location that hasn't been hit.
            //This also indicates to the ship class that a specific sized ship has been placed, whose coordinates are tracked, to indicate whether a ship has been sunk, later in the game.
            this->board[startRow][startColumn] = 1;
            compShip->ships[index][0] = this->board[startRow][startColumn];
            compShip->rows[index][0] = startRow;
            compShip->cols[index][0] = startColumn;
            this->board[endRow][endColumn] = 1;
            compShip->ships[index][1] = this->board[endRow][endColumn];
            compShip->rows[index][1] = endRow;
            compShip->cols[index][1] = endColumn;
        }

        //if the size of the ship is 3...
        else if(size == 3)
        {
            this->board[startRow][startColumn] = 1;
            compShip->ships[index][0] = this->board[startRow][startColumn];
            compShip->rows[index][0] = startRow;
            compShip->cols[index][0] = startColumn;
            this->board[endRow][endColumn] = 1;
            compShip->ships[index][2] = this->board[endRow][endColumn];
            compShip->rows[index][2] = endRow;
            compShip->cols[index][2] = endColumn;

            //This sequence of checks is done to account for the different number of ways that the user could enter the coordinates.
            if(startRow == endRow && startColumn < endColumn)
            {
                for(int i = startColumn + 1; i < endColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    compShip->ships[index][i] = this->board[startRow][i];
                    compShip->rows[index][1] = startRow;
                    compShip->cols[index][1] = i;
                }
            }

            else if(startRow == endRow && startColumn > endColumn)
            {
                for(int i = endColumn + 1; i < startColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    compShip->ships[index][i] = this->board[startRow][i];
                    compShip->rows[index][1] = startRow;
                    compShip->cols[index][1] = i;
                }
            }

            else if(startColumn == endColumn && startRow < endRow)
            {
                for(int i = startRow + 1; i < endRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    compShip->ships[index][1] = this->board[i][startColumn];
                    compShip->rows[index][1] = i;
                    compShip->cols[index][1] = startColumn;
                }
            }

            else if(startColumn == endColumn && startRow > endRow)
            {
                for(int i = endRow + 1; i < startRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    compShip->ships[index][1] = this->board[i][startColumn];
                    compShip->rows[index][1] = i;
                    compShip->cols[index][1] = startColumn;
                }
            }
        }

        //if the size of the ship is 4...
        else if(size == 4)
        {
            this->board[startRow][startColumn] = 1;
            compShip->ships[index][0] = this->board[startRow][startColumn];
            compShip->rows[index][0] = startRow;
            compShip->cols[index][0] = startColumn;
            this->board[endRow][endColumn] = 1;
            compShip->ships[index][3] = this->board[endRow][endColumn];
            compShip->rows[index][3] = endRow;
            compShip->cols[index][3] = endColumn;

            if(startRow == endRow && startColumn < endColumn)
            {
                for(int i = startColumn + 1; i < endColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    compShip->ships[index][j] = this->board[startRow][i];
                    compShip->rows[index][j] = startRow;
                    compShip->cols[index][j] = i;
                    j++;
                }
            }

            else if(startRow == endRow && startColumn > endColumn)
            {
                for(int i = endColumn + 1; i < startColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    compShip->ships[index][j] = this->board[startRow][i];
                    compShip->rows[index][j] = startRow;
                    compShip->cols[index][j] = i;
                    j++;
                }
            }

            else if(startColumn == endColumn && startRow < endRow)
            {
                for(int i = startRow + 1; i < endRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    compShip->ships[index][j] = this->board[i][startColumn];
                    compShip->rows[index][j] = i;
                    compShip->cols[index][j] = startColumn;
                    j++;
                }
            }

            else if(startColumn == endColumn && startRow > endRow)
            {
                for(int i = endRow + 1; i < startRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    compShip->ships[index][j] = this->board[i][startColumn];
                    compShip->rows[index][j] = i;
                    compShip->cols[index][j] = startColumn;
                    j++;
                }
            }
        }

        //if the size of the ship is 5..
        else if(size == 5)
        {
            this->board[startRow][startColumn] = 1;
            compShip->ships[index][0] = this->board[startRow][startColumn];
            compShip->rows[index][0] = startRow;
            compShip->cols[index][0] = startColumn;
            this->board[endRow][endColumn] = 1;
            compShip->ships[index][4] = this->board[endRow][endColumn];
            compShip->rows[index][4] = endRow;
            compShip->cols[index][4] = endColumn;

            if(startRow == endRow && startColumn < endColumn)
            {
                for(int i = startColumn + 1; i < endColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    compShip->ships[index][j] = this->board[startRow][i];
                    compShip->rows[index][j] = startRow;
                    compShip->cols[index][j] = i;
                    j++;
                }
            }

            else if(startRow == endRow && startColumn > endColumn)
            {
                for(int i = endColumn + 1; i < startColumn; i++)
                {
                    this->board[startRow][i] = 1;
                    compShip->ships[index][j] = this->board[startRow][i];
                    compShip->rows[index][j] = startRow;
                    compShip->cols[index][j] = i;
                    j++;
                }
            }

            else if(startColumn == endColumn && startRow < endRow)
            {
                for(int i = startRow + 1; i < endRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    compShip->ships[index][j] = this->board[i][startColumn];
                    compShip->rows[index][j] = i;
                    compShip->cols[index][j] = startColumn;
                    j++;
                }
            }

            else if(startColumn == endColumn && startRow > endRow)
            {
                for(int i = endRow + 1; i < startRow; i++)
                {
                    this->board[i][startColumn] = 1;
                    compShip->ships[index][j] = this->board[i][startColumn];
                    compShip->rows[index][j] = i;
                    compShip->cols[index][j] = startColumn;
                    j++;
                }
            }
        }

    }//end placeShip

    int getIndex(int r, int c)
    {

        //This method returns the index for a specific place on the board.
        return this->board[r][c];

    }

    bool checkGameOver()
    {
        /*This method checks to see if all ships are sunk. If all are sunk, it
        returns true (game over) if they aren't all sunk, or it returns false (game continues).
        It works by seeing how many spots are labeled "3", meaning hit ship. There
        will be 17 spots labeled "3" if all ships are hit*/

        int countOf3 = 0;

        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                if(this->board[i][j] == 3)
                    countOf3++;
            }
        }


        if(countOf3 == 17)
            return true;

        return false;
    }

};//end class Board

int convertColumn(char column)
{
    //This method converts the char values entered by the user to ints, to work with the integer arrays utilized in the program.
    if((int)column <= 9 && (int) column >= 0)
        return column;
    else
        return (int)column - 'A';
}//end convertColumn
#endif
