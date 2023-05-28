#pragma once

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "io_utils.h"
#include "Symbols.h"

class System; // important not to put #include here.

void printMenu();
void printInstructions();
void handleNewGame(const std::vector<std::string>& names);
void handleScreenUser();
int chooseLevel();
bool checkLevel(int level);
void printWin(int typeWin);
void printLose();
bool playGame(const std::string& name, int level, int* score, int* lives);



void printMenu()
{
    cout << "(1) start a new game" << endl 
        << "(2) load your screen" << endl
        << "(8) present instructions and keys" << endl
        << "(9) exit" << endl;
}

void printInstructions()
{
    cout << "Instructions:" << endl
        << "The player controls the Pac-Man character (" << (char)2 << ") through an enclosed maze." << endl
        << "The objective of the game is to eat all of the food (.) placed in the maze while avoiding two ghosts (" << (char)19 << ") that pursue it." << endl
        << "When Pac-Man eats all of the food, the player wins!" << endl
        << "If Pac-Man makes contact with a ghost, it loses a life." << endl
        << "The game ends when all lives are lost." << endl << endl;

    cout << "Keys:" << endl
        << "UP - W/w " << endl
        << "DOWN - S/s" << endl
        << "LEFT - A/a" << endl
        << "RIGHT - D/d" << endl
        << "STAY - Q/q" << endl
        << "PAUSE - ESC" << endl << endl;

    cout << "Press any key to return to the main menu." << endl;
}

void handleNewGame(const std::vector<std::string>& names) {
    int score=0, lives=3;
    int level = 0;
    bool winScreen = true, isChose = false;
    int i = 0;

    while (i < names.size() && winScreen) {
        clear_screen();
        if (!isChose) {
            level = chooseLevel();
            while (!checkLevel(level))
                level = chooseLevel();
            isChose = true;
        }
        winScreen = playGame(names[i++], level, &score, &lives);
        if (winScreen && i < names.size()) {
            printWin(MOVEBOARD); 
            _getch();
        }
        else if (!winScreen) {
            printLose();
            _getch();
            break;
        }
    }
    if (winScreen) {
        printWin(FINISH);
        _getch();
    }
    clear_screen();
}

void handleScreenUser() {
    clear_screen();
    std::string userScreen;
    std::cout << "Enter your screen name: " << std::endl;
    std::cin >> userScreen;
    clear_screen();
    int level = chooseLevel();
    while (!checkLevel(level))
        level = chooseLevel();
    int score = 0, lives = 3;
    playGame(userScreen, level, &score, &lives);
}

int chooseLevel()
{
    int level = 0, tempLevel;
    cout << "choose level of ghosts: " << endl << "(a) BEST" << endl << "(b) GOOD" << endl << "(c) NOVICE" << endl;
    level = _getch();
    tempLevel = level;
    if (isupper(tempLevel))
    {
        level = tolower(tempLevel);
    }
    clear_screen();
    return level;
}

bool checkLevel(int level)
{
    if ((level == BEST) || (level == GOOD) || (level == NOVICE))
    {
        return true;
    }
    return false;
}

void printWin(int typeWin)
{
    if (typeWin == MOVEBOARD)
        cout << "Good Job, you move to the next screen" << endl << "press any key to continue." << endl;
    else if (typeWin == FINISH)
        cout << "Well done! You finished all the screens!" << endl << "press any key to return menu." << endl;
    else
        cout << "Winner!" << endl << "press any key to return menu." << endl;
}

void printLose()
{
    cout << "GAME OVER!" << endl << "press any key to return menu." << endl;
}

bool playGame(const std::string& name, int level, int* score, int* lives) {
    return System(name).run(score, lives, level);
}



#endif
