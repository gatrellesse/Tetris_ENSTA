#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Grid.h"
#include "Blocks.h"
#include "Game.h"
using namespace std;

/**
 * @file main.cpp
 * @brief Entry point for the Tetris game.
 *
 * This file initializes the game and starts the main game loop.
 */

/**
 * @brief The main function where the Tetris game is initialized and executed.
 *
 * Creates an instance of the `Game` class, which manages the game's core logic,
 * and starts the game loop by calling the `run` method.
 * 
 * @return int Returns 0 on successful execution.
 */
int main(){
    /**
     * @brief Initializes the Tetris game instance.
     */
    Game Tetris;

    /**
     * @brief Starts the main game loop.
     *
     * The `run` method of the `Game` class handles rendering, input, and game logic.
     */
    Tetris.run();
    
    return 0 ;
}