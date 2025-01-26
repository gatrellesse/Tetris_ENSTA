#include <SFML/System.hpp> // For sf::Clock
#include <SFML/Graphics/Text.hpp> // For rendering text
#include <vector>
#include "Blocks.h"
#include "Score.h"
#include "WindowManager.h"
#include <SFML/Audio.hpp> // For music and sounds
#include "Grid.h"
#include "GridInfo.h"
#include "Server.h"
#include "Client.h"

using Matrix = std::vector<std::vector<unsigned char>>; /**< Alias for the matrix representing the game grid. */
#pragma once

/**
 * @class Game
 * @brief Manages the core gameplay mechanics, rendering, and game state.
 * 
 * The Game class handles all aspects of the game, including player input, 
 * grid updates, rendering, music, and networking for multiplayer modes.
 */
class Game
{
public:
    /**
     * @brief Constructs a Game object.
     * 
     * Initializes the game grid, blocks, music, and other core elements.
     */
    Game();

    /**
     * @brief Destructor for the Game class.
     * 
     * Cleans up dynamically allocated resources, such as server and client instances.
     */
    ~Game();

    /**
     * @brief Runs the main game loop.
     * 
     * Handles the game's core logic, such as rendering, input handling, and state updates.
     */
    void run();

    /**
     * @brief Handles player input for moving and rotating the current piece.
     */
    void player_Input();

    /**
     * @brief Draws the ghost piece on the grid.
     * 
     * The ghost piece shows where the current piece will land if dropped.
     * 
     * @param window A shared pointer to the SFML render window.
     */
    void drawGhostTetromino(std::shared_ptr<sf::RenderWindow> window);

    /**
     * @brief Checks if the current piece collides with the grid or other pieces.
     * 
     * @return bool Returns true if a collision is detected, otherwise false.
     */
    bool verify_Collision( );

    /**
     * @brief Checks if the ghost piece collides with the grid or other pieces.
     * 
     * @return bool Returns true if a collision is detected, otherwise false.
     */
    bool verify_Ghost_Collision( );

    /**
     * @brief Generates a new random piece.
     * 
     * Updates the current and next piece for the game.
     */
    void random_Piece();

    /**
     * @brief Rotates the current piece clockwise.
     */
    void rotate();

    /**
     * @brief Placeholder function to handle game-over logic (if needed).
     */
    void printgameOver();

    /**
     * @brief Moves the current piece down one step.
     * 
     * If the piece collides, it registers the piece on the grid and generates a new piece.
     * 
     * @return bool Returns true if the piece moved successfully, otherwise false.
     */
    bool moveDown();

    /**
     * @brief Moves the ghost piece down one step.
     * 
     * @return bool Returns true if the ghost piece moved successfully, otherwise false.
     */
    bool moveGhostDown();

    /**
     * @brief Resets the game state to its initial values.
     */
    void restartValues();

    void loadSounds();
    
private:
    int cx = 5; /**< The current x-coordinate of the current piece's pivot. */
    int cy = 0; /**< The current y-coordinate of the current piece's pivot. */
    int cx_ghost = cx; /**< The current x-coordinate of the ghost piece's pivot. */
    int cy_ghost = cy; /**< The current y-coordinate of the ghost piece's pivot. */
    int idx_cp; /**< Index of the current piece. */
    int rows = 20; /**< Number of rows in the game grid. */
    int cols = 10; /**< Number of columns in the game grid. */
    float delay = 1.0f; /**< Current delay between piece movements. */
    float delayDefault = 1.0f; /**< Default delay between piece movements. */
    bool gameOver = false; /**< Flag to indicate if the game is over. */
    bool flag_up = false; /**< Flag to track if the up key is pressed (rotation). */
    bool flag_hardDrop = false; /**< Flag to track if the space key is pressed (hard drop). */
    sf::Clock clock; /**< Clock to track general timing. */
    sf::Clock clockFall; /**< Clock to manage piece falling delays. */
    sf::Music musicGame; /**< Background music during gameplay. */
    sf::Music soundGameOver; /**< Sound played when the game ends. */
    Matrix4x4 currentPiece; /**< The matrix representing the current Tetris piece. */
    Matrix4x4 nextPiece; /**< The matrix representing the next Tetris piece. */
    Blocks blocks; /**< Handles the Tetris pieces and their properties. */
    WindowManager windowGame; /**< Manages the game window and menus. */
    Grid gridGame; /**< Manages the game grid and updates. */
    GridInfo gridInfo; /**< Manages the display of score, level, and next piece. */
    Score score; /**< Manages the player's score and level progression. */
    Server* server = nullptr; /**< Pointer to the server instance for multiplayer mode. */
    Client* client = nullptr; /**< Pointer to the client instance for multiplayer mode. */
};