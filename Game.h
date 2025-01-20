#include <SFML/System.hpp> //for clock
#include <SFML/Graphics/Text.hpp> //for clock
#include <vector>
#include "Blocks.h"
#include "Score.h"
#include "WindowManager.h"
#include "Grid.h"
#include "GridInfo.h"
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
    void printgameOver();
    bool moveDown();
    void restartValues();

private:
    int cx; //current cx of the current piece (pivot)
    int cy; //current cy of the current piece (pivot)
    int idx_cp; //idx current piece
    int rows;
    int cols;
    float delay;
    float delayDefault;
    bool gameOver = 0;
    bool flag_up = 0;
    bool flag_hardDrop = 0;
    sf::Clock clock;
    sf::Clock clockFall;
    Matrix4x4 currentPiece;
    Matrix4x4 nextPiece;
    Blocks blocks;
    WindowManager windowGame;
    Grid gridGame;
    GridInfo gridInfo;
    Score score;

    
    
};