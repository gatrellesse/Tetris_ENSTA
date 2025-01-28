#include <SFML/System.hpp> //for clock
#include <SFML/Graphics/Text.hpp> //for clock
#include <vector>
#include "Blocks.h"
#include "Score.h"
#include "WindowManager.h"
#include <SFML/Audio.hpp>
#include "Grid.h"
#include "GridInfo.h"
#include "Server.h"
#include "Client.h"

/**
 * @typedef Matrix
 * @brief Represents a 2D grid of unsigned characters.
 */
using Matrix = std::vector<std::vector<unsigned char>>;

#pragma once

/**
 * @class Game
 * @brief Manages the main gameplay mechanics, including rendering, user input, and game state transitions.
 */
class Game
{
public:
    /**
     * @brief Constructs a new Game instance.
     */
    Game();

    /**
     * @brief Destructor for the Game class. Cleans up resources.
     */
    ~Game();

    /**
     * @brief Runs the main game loop.
     */
    void run();

    /**
     * @brief Handles player input, such as movement, rotation, and hard drop.
     */
    void player_Input();

    /**
     * @brief Draws the ghost piece (shadow of the current piece) on the game window.
     * 
     * @param window Shared pointer to the SFML render window.
     */
    void drawGhostTetromino(std::shared_ptr<sf::RenderWindow> window);

    /**
     * @brief Verifies if the current piece collides with the grid or walls.
     * 
     * @return True if a collision is detected, false otherwise.
     */
    bool verify_Collision( );

    /**
     * @brief Verifies if the current piece collides at its spawn position.
     * 
     * @return True if a collision is detected at spawn, false otherwise.
     */
    bool verify_CollisionAtSpawn( );

    /**
     * @brief Verifies if the ghost piece collides with the grid or walls.
     * 
     * @return True if a collision is detected, false otherwise.
     */
    bool verify_Ghost_Collision( );

    /**
     * @brief Sets the game over state and handles endgame logic.
     */
    void setGameOver();

    /**
     * @brief Generates a new random Tetris piece and updates the current piece.
     */
    void random_Piece();

    /**
     * @brief Rotates the current Tetris piece clockwise.
     */
    void rotate();

    /**
     * @brief Prints game over information (placeholder).
     */
    void printgameOver();

    /**
     * @brief Moves the current piece one row down.
     * 
     * @return True if the piece can continue moving down, false otherwise.
     */
    bool moveDown();

    /**
     * @brief Moves the ghost piece one row down.
     * 
     * @return True if the ghost piece can continue moving down, false otherwise.
     */
    bool moveGhostDown();

    /**
     * @brief Resets the game values to their initial state.
     */
    void restartValues();

private:
    int cx; /**< Current x-coordinate of the pivot of the current piece. */
    int cy; /**< Current y-coordinate of the pivot of the current piece. */
    int cx_ghost; /**< Current x-coordinate of the pivot of the ghost piece. */
    int cy_ghost; /**< Current y-coordinate of the pivot of the ghost piece. */
    int idx_cp; /**< Index of the current piece. */
    int rows;
    int cols;
    float delay;
    float delayDefault;
    bool gameOver = 0;
    bool flag_up = 0;
    bool flag_hardDrop = 0;
    bool exitPressed = false;
    sf::Clock clock;
    sf::Clock clockFall;
    sf::Music musicGame;
    sf::Music soundGameOver;
    Matrix4x4 currentPiece;
    Matrix4x4 nextPiece;
    string gameMode;
    string whichWindow;
    Blocks blocks;
    WindowManager windowGame;
    Grid gridGame;
    GridInfo gridInfo;
    Score score;
    Server* server = nullptr;
    Client* client = nullptr;
    
};