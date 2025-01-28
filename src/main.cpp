/**
 * @file main.cpp
 * @brief Entry point for the Tetris game.
 * 
 * Initializes the game and starts the main game loop.
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Grid.h"
#include "Blocks.h"
#include "Game.h"
using namespace std;

/**
 * @brief Main function of the Tetris game.
 * 
 * Creates an instance of the `Game` class and runs the game loop.
 * 
 * @return Returns 0 when the program exits successfully.
 */
int main(){
    Game Tetris;
    Tetris.run(); 
    return 0 ;
}