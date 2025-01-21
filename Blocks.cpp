#include "Blocks.h"
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Colors.h"
#include <iostream>
using namespace std;

Blocks::Blocks(int cell_size){
    this->cell_size = cell_size;
    matrixPieces = {
        {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
        {{0, 0, 0, 0}, {0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}}, // O
        {{0, 0, 0, 0}, {3, 3, 3, 0}, {0, 3, 0, 0}, {0, 0, 0, 0}}, // T
        {{0, 0, 0, 0}, {4, 4, 4, 0}, {0, 0, 4, 0}, {0, 0, 0, 0}}, // L
        {{0, 0, 0, 0}, {0, 5, 5, 5}, {0, 5, 0, 0}, {0, 0, 0, 0}}, // J
        {{0, 0, 0, 0}, {6, 6, 0, 0}, {0, 6, 6, 0}, {0, 0, 0, 0}}, // Z
        {{0, 7, 7, 0}, {7, 7, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}  // S
    };
}

Blocks::~Blocks(){
}

void Blocks::draw_piece(sf::RenderWindow* window, Matrix4x4& piece, int cx, int cy){
    for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                if (piece[x][y]) {

                    sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                    cell.setPosition(cell_size * (x + cx), cell_size * (y + cy));
                    sf::Color color = GetCellColors()[piece[x][y] - 1];
                    cell.setFillColor(color);
                    cell.setOutlineThickness(1);
                    cell.setOutlineColor(sf::Color::White);
                    window->draw(cell);
                }
            }
        }
}

void Blocks::draw_Ghost_piece(sf::RenderWindow* window, Matrix4x4& piece, int cx, int cy){
    for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                if (piece[x][y]) {

                    sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                    cell.setPosition(cell_size * (x + cx), cell_size * (y + cy));
                    sf::Color color = GetCellColors()[piece[x][y] - 1];
                    cell.setFillColor(sf::Color(128, 128, 128, 255));
                    cell.setOutlineThickness(2);
                    cell.setOutlineColor(color);
                    window->draw(cell);
                }
            }
        }
}

Matrix4x4 Blocks::getPiece(int idx) const{
    return matrixPieces[idx];
}



