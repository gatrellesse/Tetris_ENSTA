#pragma once
#include <vector>
#include <memory>
#include "WindowManager.h"
#include <SFML/Graphics.hpp>

/**
 * @class Grid
 * @brief Manages the Tetris grid, including rendering, line clearing, and tracking grid state.
 */
class Grid: public WindowManager
{
public:
    /**
     * @brief Constructs a new Grid instance.
     * 
     * @param parentWindow A shared pointer to the SFML render window.
     * @param rows The number of rows in the grid (default is 20).
     * @param cols The number of columns in the grid (default is 10).
     * @param rows_setOff Vertical offset for rendering the grid (default is 0).
     * @param cols_setOff Horizontal offset for rendering the grid (default is 0).
     * @param cell_size The size of each cell in pixels (default is 30).
     */
    explicit Grid(std::shared_ptr<sf::RenderWindow> parentWindow, int rows = 20, int cols = 10,  int rows_setOff = 0, int cols_setOff = 0, int cell_size = 30);
    
    /**
     * @brief Destructor for the Grid class.
     */
    virtual ~Grid();

    /**
     * @brief Renders the grid on the game window.
     */
    virtual void draw_grid();

    /**
     * @brief Provides access to the grid's current state.
     * 
     * @return A reference to the 2D matrix representing the grid.
     */
    std::vector<std::vector<unsigned char>>& getmatrixGrid();

    /**
     * @brief Retrieves the cells in the grid that have changed since the last update.
     * 
     * @return A vector of tuples representing changed cells (column, row, value).
     */
    std::vector<std::tuple<int, int, unsigned char>> getChangedCells();

    /**
     * @brief Resets the grid to its initial empty state.
     */
    void restartValues();

    /**
     * @brief Retrieves the size of a single cell in pixels.
     * 
     * @return The size of a cell in pixels.
     */
    int getCell_size() const;

    /**
     * @brief Retrieves the number of columns in the grid.
     * 
     * @return The number of columns.
     */
    int getCols_size() const;

    /**
     * @brief Retrieves the number of rows in the grid.
     * 
     * @return The number of rows.
     */
    int getRows_size() const;

    /**
     * @brief Clears full lines from the grid and shifts rows downward.
     * 
     * @return The number of lines cleared.
     */
    int lineCleaning() ;

private:
    bool gameover = 0;
    int rows;
    int rows_setOff;
    int cols;
    int cols_setOff;
    std::vector<std::vector<unsigned char>> matrixGrid;
    std::vector<std::vector<unsigned char>> previousGrid; 


};