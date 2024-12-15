#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "Blocks.h"
#include "Colors.h"

Grid::Grid(int cell_size, int rows, int cols ): cell_size(cell_size), rows(rows), cols(cols)
{
    matrixGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(cell_size * cols, cell_size * rows), "Tetris");
}

Grid::~Grid()
{

}

void Grid::draw_grid(){
    for (int y = 0; y < rows; ++y){
            for (int x = 0; x < cols; ++x){
                sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                cell.setPosition(x * cell_size, y * cell_size);
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

void Grid::lineCleaning() {
    int target = rows - 1;
    // Iterate through the rows from bottom to top
    for (int y = rows - 1; y >= 1; --y) {
        int count = 0;
        // Check if the row is full by checking each cell in the row
        for (int x = 0; x < cols; ++x) {
            if (matrixGrid[y][x])
                count++;
        }
        if(count < cols){
            for(int x = 0; x < cols; x++){
                matrixGrid[target][x] = matrixGrid[y][x];
            }
            target--;
        }

    }

    //return count;
}


std::shared_ptr<sf::RenderWindow> Grid::getWindow() const {
    return window;
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