#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>
#include <queue>

/*
 * Relatively platform independent screen clearing. :)
 */

#if defined(_WIN32)
/* Compiling on Windows. */
#include <windows.h>
void cls(void)
{
    system("cls");
    return;
}
void pause()
{
    std::cout << std::endl;
    system("pause");
    return;
}
void sleep(unsigned millis)
{
    Sleep(millis);
    return;
}

#elif defined(_WIN64)
/* Compiling on Windows. (64 bit) */
#include <windows.h>
void cls(void)
{
    system("cls");
}
void pause()
{
    std::cout << std::endl;
    system("pause");
    return;
}
void sleep(unsigned millis)
{
    Sleep(millis);
    return;
}

#else
/* Not compiling on Windows assuming *nix-like */
void cls(void)
{
    system("clear");
    return;
}
void pause()
{
    std::cout << "\nPlease press enter to continue. . ." << std::endl;
    std::string ui("");
    do
    {
        std::getline(std::cin, ui);
    }
    while(ui.length() > 0);
    return;
}
void sleep(int millis)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

#endif

/*
 * Prompts the user for a choice.
 */

void ask_choice()
{
    std::cout << "choice - ";
    return;
}

void printSecret()
{
    std::string password;
    cls();
    std::cout << "    ___________________" << std::endl;
    std::cout << "   |                   | " << std::endl;
    std::cout << "   | SPEAK             | " << std::endl;
    std::cout << "   | ___ _ ___ _    _  | " << std::endl;
    std::cout << "   ||__ |_) | |_|\\|| \\ |   _             _,-----------._        ___ " << std::endl;
    std::cout << "   ||   | \\_|_|_| ||_/ |  (_,.-      _,-'_,-----------._`-._    _)_) " << std::endl;
    std::cout << "   |                   |           ,'_,-'  ___________  `-._`. " << std::endl;
    std::cout << "   | AND               |         ,','  _,-'___________`-._  `.`. " << std::endl;
    std::cout << "   | ___   ___ _ _     |       ,','  ,'_,-'     .     `-._`.  `.`. " << std::endl;
    std::cout << "   ||__ |\\| | |_|_)    |      /,'  ,','        >|<        `.`.  `.\\ " << std::endl;
    std::cout << "   ||___| | | |_| \\    |     //  ,','      ><  ,^.  ><      `.`.  \\\\ " << std::endl;
    std::cout << "   |___________________|    //  /,'      ><   / | \\   ><      `.\\  \\\\ " << std::endl;
    std::cout << "                           //  //      ><    \\/\\^/\\/    ><      \\\\  \\\\ " << std::endl;
    std::cout << "                          ;;  ;;              `---'              ::  :: " << std::endl;
    std::cout << "                          ||  ||              (____              ||  || " << std::endl;
    std::cout << "                         _||__||_            ,'----.            _||__||_ " << std::endl;
    std::cout << "                        (o.____.o)____        `---'        ____(o.____.o) " << std::endl;
    std::cout << "                          |    | /,--.)                   (,--.\\ |    | " << std::endl;
    std::cout << "                          |    |((  -`___               ___`   ))|    | " << std::endl;
    std::cout << "                          |    | \\\\,'',  `.           .'  .``.// |    | " << std::endl;
    std::cout << "                          |    |  // (___,'.         .'.___) \\\\  |    | " << std::endl;
    std::cout << "                         /|    | ;;))  ____) .     . (____  ((\\\\ |    |\\ " << std::endl;
    std::cout << "                         \\|.__ | ||/ .'.--.\\/       `/,--.`. \\;: | __,|; " << std::endl;
    std::cout << "                          |`-,`;.| :/ /,'  `)-'   `-('  `.\\ \\: |.;',-'| " << std::endl;
    std::cout << "                          |   `..  ' / \\__.'         `.__/ \\ `  ,.'   | " << std::endl;
    std::cout << "                          |    |,\\  /,                     ,\\  /,|    | " << std::endl;
    std::cout << "                          |    ||: : )          .          ( : :||    | " << std::endl;
    std::cout << "                         /|    |:; |/  .      ./|\\,      ,  \\| :;|    |\\ " << std::endl;
    std::cout << "                         \\|.__ |/  :  ,/-    <--:-->    ,\\.  ;  \\| __,|; " << std::endl;
    std::cout << "                          |`-.``:   `'/-.     '\\|/`     ,-\\`;   ;'',-'| " << std::endl;
    std::cout << "                          |   `..   ,' `'       '       `  `.   ,.'   | " << std::endl;
    std::cout << "                          |    ||  :                         :  ||    | " << std::endl;
    std::cout << "                          |    ||  |                         |  ||    | " << std::endl;
    std::cout << "                          |    ||  |                         |  ||    | " << std::endl;
    std::cout << "                          |    |'  |            _            |  `|    | " << std::endl;
    std::cout << "                          |    |   |          '|))           |   |    | " << std::endl;
    std::cout << "                          ;____:   `._        `'           _,'   ;____: " << std::endl;
    std::cout << "                         {______}     \\___________________/     {______} " << std::endl;
    std::cout << "                         |______|_______________________________|______|" << std::endl;
    std::cout << std::endl;
    std::cout << "Type the correct password to unlock God Mode:" << std::endl;
    do
    {
        std::getline(std::cin, password);
    }
    while(password.compare("friend") != 0);
    std::cout << "Correct!  Activating God Mode in ";
    for(int i = 5; i > 0; i--)
    {
        std::cout << i << "...";
        sleep(1000);
        std::cout << "\b\b\b\b";
    }
    std::cout << "0...\nJust kidding." << std::endl;
    pause();
    cls();
}

#endif
