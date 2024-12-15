#include "Game.h"
#include "Grid.h"
#include <iostream>
using namespace std;

Game::Game(){
    std::cout << "Play time!" << std::endl; // Timer to control delay
    this->delay = 0.4f; // Delay in seconds 
}

Game::~Game(){
}

void Game::run(){
    Grid grid;
    cx = 5;//grid.getCols_size()/2 ;//Starts the piece in the middle top
    cy = 0;
    rows = 20;
    cols = 10;
    Blocks blocks(grid.getCell_size());
    currentPiece = blocks.getPiece(rand() % 7);
    std::shared_ptr<sf::RenderWindow> window = grid.getWindow();

    while(window->isOpen()){
        delay = 0.4f;
        sf::Event event;
        while (window->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window->close();
        }
        player_Input( grid.getmatrixGrid());
        window->clear();
        grid.draw_grid();
        blocks.draw_piece(window.get(), currentPiece, cx, cy);
        window->display();
    }
}

void Game::rotate(){
    int len = 0;
    for (int x = 0; x < 4; x++) 
        for (int y = 0; y < 4; y++)
            if (currentPiece[x][y]) 
                len = max(max(x, y) + 1, len); //Verifica se é de 2/3/4
    
    int rot[4][4] = { 0 };
    for (int x = 0; x < len; x++) 
        for (int y = 0; y < len; y++)
            if (currentPiece[x][y]) 
                rot[len - 1 - y][x] = 1;

    for (int x = 0; x < 4; x++) 
        for (int y = 0; y < 4; y++)
            currentPiece[x][y] = rot[x][y];
}

void Game::player_Input(const Matrix& matrixGrid){
    flag_up = 0;

    if(clock.getElapsedTime().asSeconds() > delay){ 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                --cx; 
                 std::cout << "Left pressed, new cx: " << cx << std::endl;  // Debugging
                 if(verify_Collision(matrixGrid)){
                    ++cx;
                     std::cout << "Left unpressed, new cx: " << cx << std::endl;  // Debugging
                 }
                //++cx;
                clock.restart(); // Reset timer
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                ++cx;   
                if(verify_Collision(matrixGrid))
                --cx;
                clock.restart(); // Reset timer
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                ++cy;   
                if(verify_Collision(matrixGrid))
                --cy;
                delay = 0.05f;
                clock.restart(); // Reset timer
            }
            else if (flag_up == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                flag_up = 1;
                rotate(); // Rotação temporária
                if (verify_Collision(matrixGrid))
                    rotate();rotate();rotate();//Desfaz a rotacao q colidiu
                clock.restart(); // Reset timer
            }
            else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    flag_up = 0;

        }
}

bool Game::verify_Collision(const Matrix& matrixGrid){
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            std::cout << currentPiece[x][y] <<endl;
        }
        std::cout << std::endl;
    }

    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            if (currentPiece[x][y] == 1) {
                int limx = x + cx;
                int limy = y + cy ; //SE EU TIRAR ESSE 1,A COLISAO VERTICAL PARA DE FUNCIONAR
                if (limx < 0 || limx >= cols ||  limy  >= rows) {
                    return true;  // Collision with ground/walls detected
                }
                if( matrixGrid[limx][limy] != 0){
                    return true;  //Collision with other pieces detected
                }
            }
        }
    }
    return false;  // No collision
}

void Game::random_Piece(Blocks blocks){
    int idx = rand() % 7;
    currentPiece = blocks.getPiece(idx);
}