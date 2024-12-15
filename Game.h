#ifndef GAME_H
#define GAME_H
#include <SFML/System.hpp> //for clock
#include <vector>
#include "Blocks.h"
using Matrix = std::vector<std::vector<unsigned char>>;

#pragma once

class Game
{
public:
    Game();
    ~Game();
    void run();
    void player_Input(const Matrix& matrixGrid);
    bool verify_Collision( const Matrix& matrixGrid);
    void random_Piece(Blocks blocks);
    void rotate();
    bool moveDown(Matrix& matrixGrid);

private:
    int cx; //current cx of the current piece (pivot)
    int cy; //current cy of the current piece (pivot)
    int rows;
    int cols;
    float delay;
    bool flag_up = 0;
    sf::Clock clock;
    sf::Clock clockFall;
    Matrix4x4 currentPiece;
    
};

#endif