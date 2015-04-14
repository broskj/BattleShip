/*
 TODO:
    -Consider adding tally beside each board listing which ships are afloat
 */

#include "Methods.h"
#include "Game.h"
#include "Definitions.h"

const int MODE_PVP = 0;
const int MODE_PVC = 1;

/*
 * Use this if we have command line arguments. Nothing here for now.
 */
void usage(char **argv)
{
    exit(0);
}

/*
 * Asks the user for a menu choice. Add rows as necessary.
 */
void choices(void)
{
    // Put banner here if necessary.

    // It is completely necessary.
    std::cout << "__________         __    __  .__           _________.__    .__        " << std::endl;
    std::cout << "\\______   \\_____ _/  |__/  |_|  |   ____  /   _____/|  |__ |__|_____  " << std::endl;
    std::cout << " |    |  _/\\__  \\\\   __\\   __\\  | _/ __ \\ \\_____  \\ |  |  \\|  \\____ \\ " << std::endl;
    std::cout << " |    |   \\ / __ \\|  |  |  | |  |_\\  ___/ /        \\|   Y  \\  |  |_> >" << std::endl;
    std::cout << " |______  /(____  /__|  |__| |____/\\___  >_______  /|___|  /__|   __/ " << std::endl;
    std::cout << "        \\/      \\/                     \\/        \\/      \\/   |__|    " << std::endl << std::endl;

    std::cout << "\t" << "1. Player vs Player" << std::endl;
    std::cout << "\t" << "2. Player vs Computer" << std::endl;
    std::cout << "\t" << "3. Instructions" << std::endl;
    std::cout << "\t" << "4. Tutorial" << std::endl;
    std::cout << "\t" << "5. Quit" << std::endl;

    return;
}

int difficulty(void)
{
    std::string userinput = "";
    while(true)
    {
        std::cout << "\t" << "1. Normal" << std::endl;
        std::cout << "\t" << "2. Hard" << std::endl;
        std::cout << "choice - ";
        std::getline(std::cin, userinput);

        if(userinput.compare("1") == 0)
            return 0;
        else if(userinput.compare("2") == 0)
            return 1;
        else if(userinput.compare("") == 0)
        {
            cls();
            continue;
        }
        std::cout << "Error.  Invalid choice entered.  Please try again." << std::endl;
    }
}//end difficulty

/*
 * Gets user input and verifies it.
 */
int get_input()
{
    std::string userinput = "";
    while (true)
    {
        choices();
        ask_choice();
        std::getline(std::cin, userinput);

        if(userinput.compare("1") == 0)
        {
            return 1;
        }
        else if(userinput.compare("2") == 0)
        {
            return 2;
        }
        else if(userinput.compare("3") == 0)
        {
            return 3;
        }
        else if(userinput.compare("4") == 0)
        {
            return 4;
        }
        else if(userinput.compare("5") == 0)
        {
            return 5;
        }
        else if(userinput.compare("uuddlrlrba") == 0)
        {
            return 1337;
        }
        else if(userinput.compare("") == 0)
        {
            cls();
            continue;
        }
        std::cout << "Error. Invalid choice entered. Please try again.";
        std::cout << std::endl;

    }
    return 0;
}

int main(int argc, char** argv)
{
    while(true)
    {
        int choice = get_input();

        switch(choice)
        {
        case 5: // Quit selected, exit cleanly.
            // Clear any datastructurs here.
            exit(0);

        case 4: // tutorial
            cls(); // Clear screen.
            runTutorial();
            break;

        case 3:  // Print instructions.
        {
            cls(); // Clear screen.
            printInstructions();
            break;
        }

        case 2:  // Player vs Computer
        {
            cls();
            playGame(MODE_PVC, difficulty());
            break;
        }

        case 1: // Player vs Player
            cls(); // Clear screen.
            playGame(MODE_PVP, -1);
            break;

        case 1337:
            printSecret();
            break;
        }
    }

    return 0;
}//end main
