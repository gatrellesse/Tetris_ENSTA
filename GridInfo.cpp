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
                cell.setOutlineColor(sf::Color::White);
                window->draw(cell);
            }
    }
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        throw std::runtime_error("Failed to load font file");
    }

    sf::Text text;
    text.setFont(font);
    text.setString("EU TE AMO");
    text.setCharacterSize(24); // in pixels, not points!
    text.setPosition(30 * 13, 30 * 8);
    text.setFillColor(sf::Color::Red);
    window->draw(text);
    sf::Text text2;
    text2.setFont(font);
    text2.setString("Gigi");
    text2.setCharacterSize(24); // in pixels, not points!
    text2.setPosition(30 * 15, 30 * 10);
    text2.setFillColor(sf::Color::Magenta);
    window->draw(text2);
}

void GridInfo::draw_nextPiece(Matrix4x4 nextPiece){
    for (int y = 0; y < 4; ++y){
            for (int x = 0; x < 4; ++x){
                sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                cell.setPosition((x + 13) * cell_size, (y + 3) * cell_size);
                if(nextPiece[x][y]){
                    sf::Color color = GetCellColors()[nextPiece[x][y] - 1];
                    cell.setFillColor(color);
                }
                else cell.setFillColor(sf::Color::White);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);
                window->draw(cell);
            }
    }
}


