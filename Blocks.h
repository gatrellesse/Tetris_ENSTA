#ifndef BLOCKS_H
#define BLOCKS_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

using Matrix4x4 = std::vector<std::vector<int>>;
#pragma once

class Blocks
{
public:
    Blocks(int cell_size);
    ~Blocks();
    void draw_piece(sf::RenderWindow* window, Matrix4x4& piece, int cx, int cy);
    Matrix4x4 getPiece(int idx) const;

private:
    int cell_size;
    int width;
    std::vector<Matrix4x4> matrixPieces ;

};

#endif