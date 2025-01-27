#include <SFML/System.hpp> //for clock
#include <SFML/Graphics/Text.hpp> //for clock
#include <vector>
#include "Blocks.h"
#include "Score.h"
#include "WindowManager.h"
#include <SFML/Audio.hpp>
#include "Grid.h"
#include "GridInfo.h"
#include "Server.h"
#include "Client.h"
using Matrix = std::vector<std::vector<unsigned char>>;
#pragma once

class Game
{
public:
    Game();
    ~Game();
    void run();
    void player_Input();
    void drawGhostTetromino(std::shared_ptr<sf::RenderWindow> window);
    bool verify_Collision( );
    bool verify_CollisionAtSpawn( );
    bool verify_Ghost_Collision( );
    void setGameOver();
    void random_Piece();
    void rotate();
    void printgameOver();
    bool moveDown();
    bool moveGhostDown();
    void restartValues();

private:
    int cx; //current cx of the current piece (pivot)
    int cy; //current cy of the current piece (pivot)
    int cx_ghost; //current cx of the current ghost piece (pivot)
    int cy_ghost; //current cy of the current ghost piece (pivot)
    int idx_cp; //idx current piece
    int rows;
    int cols;
    float delay;
    float delayDefault;
    bool gameOver = 0;
    bool flag_up = 0;
    bool flag_hardDrop = 0;
    bool exitPressed = false;
    sf::Clock clock;
    sf::Clock clockFall;
    sf::Music musicGame;
    sf::Music soundGameOver;
    Matrix4x4 currentPiece;
    Matrix4x4 nextPiece;
    string gameMode;
    string whichWindow;
    Blocks blocks;
    WindowManager windowGame;
    Grid gridGame;
    GridInfo gridInfo;
    Score score;
    Server* server = nullptr;
    Client* client = nullptr;
    
};