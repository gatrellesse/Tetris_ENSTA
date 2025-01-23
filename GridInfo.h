#pragma once
#include "WindowManager.h" 
using Matrix4x4 = std::vector<std::vector<int>>;

/**
 * @class GridInfo
 * @brief Manages the information display for Tetris, such as score, level, and the next piece preview.
 *
 * The GridInfo class is responsible for rendering additional game information, including the
 * current score, level, and the next Tetris piece. It also manages the pause button.
 */
class GridInfo: public WindowManager
{
public:
    /**
     * @brief Constructs a GridInfo object.
     * 
     * Initializes the grid used for displaying game information and sets up the pause button.
     * 
     * @param parentWindow A shared pointer to the SFML render window.
     * @param rows The number of rows in the informational grid (default is 20).
     * @param cols The number of columns in the informational grid (default is 10).
     * @param rows_setOff The vertical offset for rendering the grid (default is 0).
     * @param cols_setOff The horizontal offset for rendering the grid (default is 11).
     * @param cell_size The size of each grid cell in pixels (default is 30).
     */
    explicit GridInfo(std::shared_ptr<sf::RenderWindow> parentWindow, int rows = 20, 
                int cols = 10, int rows_setOff = 0, int cols_setOff = 11, int cell_size = 30);

    /**
     * @brief Destructor for the GridInfo class.
     */           
    ~GridInfo();

    /**
     * @brief Draws the informational grid, including score, level, and the pause button.
     * 
     * This method renders the cells of the grid and displays additional game information,
     * such as the player's score and level.
     * 
     * @param level The current level of the game.
     * @param score The player's current score.
     */
    void draw_grid(int level, int score);

    /**
     * @brief Draws the next Tetris piece in the preview area.
     * 
     * Renders the next piece using a 4x4 matrix in a designated area of the window.
     * 
     * @param nextPiece A 4x4 matrix representing the next Tetris piece.
     */
    void draw_nextPiece(Matrix4x4 nextPiece);

    /**
     * @brief Initializes the pause button.
     * 
     * Sets the size, position, color, and outline of the pause button.
     */
    void initializePauseButton();

    /**
     * @brief Retrieves a reference to the pause button.
     * 
     * Provides access to the pause button for interaction and rendering.
     * 
     * @return sf::RectangleShape& A reference to the pause button.
     */
    sf::RectangleShape& getPauseButton() ;

private:
    int rows; /**< The number of rows in the grid. */
    int rows_setOff; /**< The vertical offset for rendering the grid. */
    int cols; /**< The number of columns in the grid. */
    int cols_setOff; /**< The horizontal offset for rendering the grid. */
    sf::RectangleShape pauseButton; /**< The pause button displayed on the screen. */
    std::vector<std::vector<unsigned char>> matrixGrid; /**< The matrix representing the grid's state. */
};