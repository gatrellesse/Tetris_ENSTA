
#include "Grid.h"
#include "Blocks.h"
#include "Colors.h"

using namespace std;
#include <iostream>

/**
 * @class Grid
 * @brief Manages the Tetris game grid, including drawing, clearing lines, and tracking cell changes.
 */

/**
 * @brief Constructs a new Grid instance.
 * 
 * @param parentWindow A shared pointer to the SFML render window.
 * @param rows The number of rows in the grid.
 * @param cols The number of columns in the grid.
 * @param rows_setOff The vertical offset for rendering the grid.
 * @param cols_setOff The horizontal offset for rendering the grid.
 * @param cell_size The size of each cell in pixels.
 */
Grid::Grid( std::shared_ptr<sf::RenderWindow> parentWindow, int rows, int cols, int rows_setOff, int cols_setOff, int cell_size): 
 WindowManager(), 
 rows(rows), cols(cols), rows_setOff(rows_setOff), cols_setOff(cols_setOff)
{
    window = parentWindow;
    matrixGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
    previousGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
    
}

/**
 * @brief Destructor for the Grid class.
 */
Grid::~Grid()
{

}

/**
 * @brief Draws the grid on the game window.
 * 
 * Colors the cells based on their state and adds a white outline for each cell.
 */
void Grid::draw_grid(){
    for (int y = 0; y < rows; ++y){
            for (int x = 0; x < cols; ++x){
                sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                cell.setPosition((x + cols_setOff)* cell_size, (y + rows_setOff )* cell_size);
                if(matrixGrid[x][y]){
                    sf::Color color = GetCellColors()[matrixGrid[x][y] - 1];
                    cell.setFillColor(color);
                }
                else cell.setFillColor(sf::Color::Black);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::White);
                window->draw(cell);
            }
        }
}

/**
 * @brief Cleans full lines from the grid and shifts rows downward.
 * 
 * @return The number of lines cleaned.
 */
int Grid::lineCleaning() {
    int target = rows - 1;
    int linesCleaned = 0;
    // Iterate through the rows from bottom to top
    for (int y = rows - 1; y >= 0; --y) {
        int count = 0;        
        // Check if the row is full
        for (int x = 0; x < cols; ++x) {
            if (matrixGrid[x][y] != 0) {
                //std::cout << "    Cell filled at (" << y << ", " << x << ")" << std::endl;
                count++;
            }
        }
        
        if (count == cols) {
            linesCleaned++;
            //std::cout << "Row " << y << " is full, clearing row." << std::endl;
        } else {
            //std::cout << "Copying row " << y << " to target " << target << std::endl;
            for (int x = 0; x < cols; ++x) {
                matrixGrid[x][target] = matrixGrid[x][y];
            }
            target--;
        }
    }
    return linesCleaned;
}

/**
 * @brief Retrieves the size of a single cell in pixels.
 * 
 * @return The size of a cell in pixels.
 */
int Grid::getCell_size() const{ 
    return cell_size;
}

/**
 * @brief Retrieves the number of columns in the grid.
 * 
 * @return The number of columns.
 */
int Grid::getCols_size() const{
    return  cols;
}

/**
 * @brief Retrieves the number of rows in the grid.
 * 
 * @return The number of rows.
 */
int Grid::getRows_size() const{
    return  rows;
}

/**
 * @brief Provides access to the grid's current state.
 * 
 * @return A reference to the matrix representing the grid.
 */
std::vector<std::vector<unsigned char>>& Grid::getmatrixGrid(){
    return matrixGrid;
};

/**
 * @brief Retrieves the cells in the grid that have changed since the last update.
 * 
 * @return A vector of tuples representing the changed cells (column, row, value).
 */
std::vector<std::tuple<int, int, unsigned char>> Grid::getChangedCells() {
        std::vector<std::tuple<int, int, unsigned char>> changedCells;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (matrixGrid[c][r] != previousGrid[c][r]) { // Detect change
                    changedCells.push_back({c, r, matrixGrid[c][r]});
                    previousGrid[c][r] = matrixGrid[c][r]; // Update previous state
                }
            }
        }
        return changedCells;
    }

/**
 * @brief Resets the grid to its initial empty state.
 */
void Grid::restartValues(){
    matrixGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
    previousGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
};