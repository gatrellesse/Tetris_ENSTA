#include "Blocks.h"
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <iostream>
using namespace std;

Blocks::Blocks(int cell_size){
    this->cell_size = cell_size;
    matrixPieces = {
        {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
        {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // O
        {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // T
        {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}, // L
        {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}}, // J
        {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, // Z
        {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}  // S
    };
}

Blocks::~Blocks(){
}

void Blocks::draw_piece(sf::RenderWindow* window, Matrix4x4& piece, int cx, int cy){
    for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                if (piece[x][y] == 1) {
                    
                    sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                    cell.setPosition(cell_size * (x + cx), cell_size * (y + cy));
                    cell.setFillColor(sf::Color::Green);
                    cell.setOutlineThickness(1);
                    cell.setOutlineColor(sf::Color::White);
                    window->draw(cell);
                }
            }
        }
}

Matrix4x4 Blocks::getPiece(int idx) const{
    return matrixPieces[idx];
}



