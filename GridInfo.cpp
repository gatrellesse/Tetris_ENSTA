#include "GridInfo.h"
#include <SFML/Graphics.hpp>
#include "Colors.h"

GridInfo::GridInfo(std::shared_ptr<sf::RenderWindow> parentWindow, int rows, int cols, int rows_setOff, int cols_setOff, int cell_size)
    : WindowManager(), // Initialize the parent class her
      rows(rows), cols(cols), rows_setOff(rows_setOff),cols_setOff(cols_setOff) 
    {
        window = parentWindow;
        matrixGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
    }

GridInfo::~GridInfo()
{
}

void GridInfo::draw_grid(){
    for (int y = 0; y < rows; ++y){
            for (int x = 0; x < cols; ++x){
                sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                cell.setPosition((x + cols_setOff) * cell_size, (y + rows_setOff) * cell_size);
                if(matrixGrid[x][y]){
                    sf::Color color = GetCellColors()[matrixGrid[x][y] - 1];
                    cell.setFillColor(color);
                }
                else cell.setFillColor(sf::Color::White);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Red);
                window->draw(cell);
            }
    }
}
