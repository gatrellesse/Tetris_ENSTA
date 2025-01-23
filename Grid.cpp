
#include "Grid.h"
#include "Blocks.h"
#include "Colors.h"

using namespace std;
#include <iostream>

/**
 * @brief Constructs a Grid object.
 * 
 * Initializes the game grid with the specified number of rows and columns, 
 * along with offsets and cell sizes. The grid is used to track the placement 
 * of Tetris pieces.
 * 
 * @param parentWindow A shared pointer to the SFML render window.
 * @param rows The number of rows in the grid.
 * @param cols The number of columns in the grid.
 * @param rows_setOff The vertical offset for rendering the grid.
 * @param cols_setOff The horizontal offset for rendering the grid.
 * @param cell_size The size of each grid cell in pixels.
 */
Grid::Grid( std::shared_ptr<sf::RenderWindow> parentWindow, int rows, int cols, int rows_setOff, int cols_setOff, int cell_size): 
 WindowManager(), 
 rows(rows), cols(cols), rows_setOff(rows_setOff), cols_setOff(cols_setOff)
{
    window = parentWindow;
    matrixGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
}

/**
 * @brief Destructor for the Grid class.
 */
Grid::~Grid()
{

}

/**
 * @brief Draws the game grid on the window.
 * 
 * Iterates through the grid matrix and renders each cell, setting its color 
 * based on its state (filled or empty). Cells are drawn with a white outline.
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
                else cell.setFillColor(sf::Color::Black); // Empty cells are black
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::White);
                window->draw(cell);
            }
        }
}

/**
 * @brief Cleans full lines in the grid and shifts rows down.
 * 
 * This method checks each row from bottom to top for completeness. Full rows are cleared,
 * and rows above are shifted down. The cleared rows are replaced with empty rows.
 * 
 * @return int Returns the number of lines cleaned.
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
            linesCleaned++; // Full row detected
            //std::cout << "Row " << y << " is full, clearing row." << std::endl;
        } else {
            // Copy the row to the target row
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
 * @brief Gets the size of each cell in pixels.
 * 
 * @return int The size of each cell in pixels.
 */
int Grid::getCell_size() const{ 
    return cell_size;
}

/**
 * @brief Gets the number of columns in the grid.
 * 
 * @return int The number of columns in the grid.
 */
int Grid::getCols_size() const{
    return  cols;
}

/**
 * @brief Gets the number of rows in the grid.
 * 
 * @return int The number of rows in the grid.
 */
int Grid::getRows_size() const{
    return  rows;
}

/**
 * @brief Returns a reference to the grid matrix.
 * 
 * Provides access to the matrix that represents the grid's current state.
 * 
 * @return std::vector<std::vector<unsigned char>>& A reference to the grid matrix.
 */
std::vector<std::vector<unsigned char>>& Grid::getmatrixGrid(){
    return matrixGrid;
};

/**
 * @brief Resets the grid to its initial state.
 * 
 * Clears the grid by replacing its contents with empty cells.
 */
void Grid::restartValues(){
    matrixGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
};