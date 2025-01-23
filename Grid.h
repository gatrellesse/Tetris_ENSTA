#pragma once
#include <vector>
#include <memory>
#include "WindowManager.h"
#include <SFML/Graphics.hpp>

/**
 * @class Grid
 * @brief Represents the main game grid for Tetris.
 *
 * The Grid class handles the rendering of the game grid, the state of each cell,
 * and operations such as line cleaning and grid resetting. It extends the 
 * WindowManager class for managing rendering within a window.
 */
class Grid: public WindowManager
{
public:
    /**
     * @brief Constructs a Grid object.
     * 
     * Initializes the grid with a specified number of rows, columns, offsets, 
     * and cell size. The grid tracks the state of the Tetris board.
     * 
     * @param parentWindow A shared pointer to the SFML render window.
     * @param rows The number of rows in the grid (default is 20).
     * @param cols The number of columns in the grid (default is 10).
     * @param rows_setOff The vertical offset for rendering the grid (default is 0).
     * @param cols_setOff The horizontal offset for rendering the grid (default is 0).
     * @param cell_size The size of each cell in pixels (default is 30).
     */
    explicit Grid(std::shared_ptr<sf::RenderWindow> parentWindow, int rows = 20, int cols = 10,  int rows_setOff = 0, int cols_setOff = 0, int cell_size = 30);
    
    /**
     * @brief Destructor for the Grid class.
     */
    virtual ~Grid();

    /**
     * @brief Draws the game grid on the window.
     * 
     * This method iterates through the grid matrix and renders each cell,
     * coloring them based on their state (filled or empty).
     */
    virtual void draw_grid();

    /**
     * @brief Gets a reference to the grid's matrix.
     * 
     * Provides access to the matrix that represents the current state of the grid.
     * 
     * @return std::vector<std::vector<unsigned char>>& A reference to the grid matrix.
     */
    std::vector<std::vector<unsigned char>>& getmatrixGrid();

    /**
     * @brief Resets the grid to its initial state.
     * 
     * Clears the grid by replacing all cells with empty values (0).
     */
    void restartValues();

    /**
     * @brief Gets the size of each cell in pixels.
     * 
     * @return int The size of each cell in pixels.
     */
    int getCell_size() const;

    /**
     * @brief Gets the number of columns in the grid.
     * 
     * @return int The number of columns in the grid.
     */
    int getCols_size() const;

    /**
     * @brief Gets the number of rows in the grid.
     * 
     * @return int The number of rows in the grid.
     */
    int getRows_size() const;

    /**
     * @brief Cleans full lines in the grid.
     * 
     * Checks for full rows in the grid and removes them, shifting all rows above 
     * the cleared line down. The cleared rows are replaced with empty rows.
     * 
     * @return int The number of lines that were cleaned.
     */
    int lineCleaning() ;

private:
    bool gameover = 0; /**< Flag to indicate if the game is over. */
    int rows; /**< Number of rows in the grid. */
    int rows_setOff; /**< Vertical offset for rendering the grid. */
    int cols; /**< Number of columns in the grid. */
    int cols_setOff; /**< Horizontal offset for rendering the grid. */
    std::vector<std::vector<unsigned char>> matrixGrid; /**< Matrix representing the grid's state. */
    
};