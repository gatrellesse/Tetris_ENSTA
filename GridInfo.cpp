#include "GridInfo.h"
#include <SFML/Graphics.hpp>
#include "Colors.h"
#include <iostream>
using namespace std;

GridInfo::GridInfo(std::shared_ptr<sf::RenderWindow> parentWindow, int rows, int cols, int rows_setOff, int cols_setOff, int cell_size)
    : WindowManager(), // Initialize the parent class her
      rows(rows), cols(cols), rows_setOff(rows_setOff),cols_setOff(cols_setOff) 
    {
        window = parentWindow;
        matrixGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
        // Load the texture for the sprite
    }

GridInfo::~GridInfo()
{
}

void GridInfo::draw_grid(int currentLevel, int currentScore){
    for (int y = 0; y < rows; ++y){
            for (int x = 0; x < cols; ++x){
                sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                cell.setPosition((x + cols_setOff) * cell_size, (y + rows_setOff) * cell_size);
                if(matrixGrid[x][y]){
                    sf::Color color = GetCellColors()[matrixGrid[x][y] - 1];
                    cell.setFillColor(color);
                }
                else cell.setFillColor(sf::Color::Black);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);
                window->draw(cell);
            }
    }
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        throw std::runtime_error("Failed to load font file");
    }
    sf::Texture texture;
    if (!texture.loadFromFile("infoScreen.png")) { // Replace with your image path
        std::cout << "Erro ao carregar a imagem!" << std::endl;
    }

    // Create a sprite and set the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(30*10, 0); // Adjust position as needed
    window->draw(sprite);
    sf::Text level;
    level.setFont(font);
    level.setString("Level: " + std::to_string(currentLevel));
    level.setCharacterSize(24); // in pixels, not points!
    level.setPosition(30 * 13, 30 * 8);
    level.setFillColor(sf::Color::Red);
    window->draw(level);
    sf::Text score;
    score.setFont(font);
    score.setString("Score: " + std::to_string(currentScore));
    score.setCharacterSize(24); // in pixels, not points!
    score.setPosition(30 * 13, 30 * 10);
    score.setFillColor(sf::Color::Magenta);
    window->draw(score);
}


void GridInfo::draw_nextPiece(Matrix4x4 nextPiece){
    for (int y = 0; y < 4; ++y){
            for (int x = 0; x < 4; ++x){
                sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                cell.setPosition((x + 13) * cell_size, (y + 3) * cell_size);
                if(nextPiece[x][y]){
                    sf::Color color = GetCellColors()[nextPiece[x][y] - 1];
                    cell.setFillColor(color);
                    cell.setOutlineThickness(1);
                    cell.setOutlineColor(sf::Color::Black);
                }
                else {  
                    cell.setFillColor(sf::Color::White);
                    cell.setOutlineThickness(1);
                    cell.setOutlineColor(sf::Color::White);
                }
                window->draw(cell);
            }
    }
}


