#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "Blocks.h"


Grid::Grid(int cell_size, int rows, int cols )
{
    this->rows = rows;
    this->cols = cols;
    this->cell_size = cell_size;
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
                if(matrixGrid[x][y] == 1) cell.setFillColor(sf::Color::Green);
                else cell.setFillColor(sf::Color::Black);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::White);
                window->draw(cell);
            }
        }
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

std::vector<std::vector<unsigned char>> Grid::getmatrixGrid(){
    return matrixGrid;
};