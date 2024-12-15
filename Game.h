#ifndef GAME_H
#define GAME_H
#include <SFML/System.hpp> //for clock
#include <vector>
#include "Blocks.h"
#include "Grid.h"
using Matrix = std::vector<std::vector<unsigned char>>;

#pragma once

class Game
{
public:
    Game();
    ~Game();
    void run();
    void player_Input();
    bool verify_Collision( );
    void random_Piece();
    void rotate();
    bool moveDown();

private:
    int cx; //current cx of the current piece (pivot)
    int cy; //current cy of the current piece (pivot)
    int idx_cp; //idx current piece
    int rows;
    int cols;
    int score;
    float delay;
    bool flag_up = 0;
    sf::Clock clock;
    sf::Clock clockFall;
    Matrix4x4 currentPiece;
    Blocks blocks;
    Grid grid;
    
};

#endif