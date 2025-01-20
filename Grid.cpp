
#include "Grid.h"
#include "Blocks.h"
#include "Colors.h"

using namespace std;
#include <iostream>

Grid::Grid( std::shared_ptr<sf::RenderWindow> parentWindow, int rows, int cols, int rows_setOff, int cols_setOff, int cell_size): 
 WindowManager(), 
 rows(rows), cols(cols), rows_setOff(rows_setOff), cols_setOff(cols_setOff)
{
    window = parentWindow;
    matrixGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
}

Grid::~Grid()
{

}

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

int Grid::getCell_size() const{ 
    return cell_size;
}
int Grid::getCols_size() const{
    return  cols;
}

int Grid::getRows_size() const{
    return  rows;
}

std::vector<std::vector<unsigned char>>& Grid::getmatrixGrid(){
    return matrixGrid;
};

void Grid::restartValues(){
    matrixGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
};