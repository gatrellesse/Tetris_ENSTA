#pragma once
#include "WindowManager.h" 

/**
 * @typedef Matrix4x4
 * @brief Defines a 4x4 matrix representation for Tetris pieces.
 */
using Matrix4x4 = std::vector<std::vector<int>>;

/**
 * @class GridInfo
 * @brief Manages the informational interface of the Tetris game, including level, score, and next piece display.
 */
class GridInfo: public WindowManager
{
public:
    /**
     * @brief Constructs a new GridInfo instance.
     * 
     * @param parentWindow A shared pointer to the SFML render window.
     * @param rows The number of rows in the grid (default is 20).
     * @param cols The number of columns in the grid (default is 10).
     * @param rows_setOff Vertical offset for rendering the grid (default is 0).
     * @param cols_setOff Horizontal offset for rendering the grid (default is 11).
     * @param cell_size The size of each cell in pixels (default is 30).
     */
    explicit GridInfo(std::shared_ptr<sf::RenderWindow> parentWindow, 
            int rows = 20, int cols = 10, int rows_setOff = 0, 
            int cols_setOff = 11, int cell_size = 30);

    /**
     * @brief Destructor for the GridInfo class.
     */        
    ~GridInfo();

    /**
     * @brief Renders the informational grid, including level and score, on the game window.
     * 
     * @param level The current level of the game.
     * @param score The current score of the player.
     */
    void draw_grid(int level, int score);

    /**
     * @brief Renders the next Tetris piece on the informational grid.
     * 
     * @param nextPiece A 4x4 matrix representing the next Tetris piece.
     */
    void draw_nextPiece(Matrix4x4 nextPiece);

    /**
     * @brief Initializes the pause button with default size, color, and position.
     */
    void initializePauseButton();

    /**
     * @brief Retrieves the pause button for external interaction.
     * 
     * @return A reference to the pause button as a rectangle shape.
     */
    sf::RectangleShape& getPauseButton() ;

private:
    int rows;
    int rows_setOff;
    int cols;
    int cols_setOff;
    sf::RectangleShape pauseButton;
    std::vector<std::vector<unsigned char>> matrixGrid;
};

