#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() : windowGame(), gridGame(windowGame.getWindow()), gridInfo(windowGame.getWindow()), blocks(30){ //era pra ser grid.getCell_size()

    std::cout << "Play time!" << std::endl; // Timer to control delay
    delay = 0.4f; // Delay in seconds 
    nextPiece = blocks.getPiece(rand() % 7); //First piece of the game
    random_Piece();
    cx = 5;//grid.getCols_size()/2 ;//Starts the piece in the middle top
    cy = 0;
    rows = 20;
    cols = 10;
}

Game::~Game(){
}


void Game::rotate(){
    int len = 0;
    int idx_piece = 0;
    for (int x = 0; x < 4; x++) 
        for (int y = 0; y < 4; y++)
            if (currentPiece[x][y]) {
                idx_piece = currentPiece[x][y];
                len = max(max(x, y) + 1, len); //Verifica se é de 2/3/4
            } 
    int rot[4][4] = { 0 };
    for (int x = 0; x < len; x++) 
        for (int y = 0; y < len; y++)
            if (currentPiece[x][y]) 
                rot[len - 1 - y][x] = idx_piece;

    for (int x = 0; x < 4; x++) 
        for (int y = 0; y < 4; y++)
            currentPiece[x][y] = rot[x][y];
}

void Game::player_Input(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        --cx; 
            if(verify_Collision())
            ++cx; 
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        ++cx;   
        if(verify_Collision())
        --cx;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        ++cy;   
        if(verify_Collision())
        --cy;
        delay = 0.05f;
    }
    else if (flag_up == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        flag_up = 1;
        rotate(); // Rotação temporária
        if (verify_Collision())
            rotate();rotate();rotate();//Desfaz a rotacao q colidiu
    }
    else if(flag_hardDrop == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ //hardrop
        flag_hardDrop = 1;
        while(moveDown() == true){}
    }
    
    
}

bool Game::verify_Collision(){
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            if (currentPiece[x][y] != 0) {
                int limx = x + cx;
                int limy = y + cy ; 
                if (limx < 0 || limx >= cols ||  limy  >= rows) {
                    return true;  // Collision with ground/walls detected
                }
                if( gridGame.getmatrixGrid()[limx][limy] != 0){
                    return true;  //Collision with other pieces detected
                }
            }
        }
    }
    return false;  // No collision
}

void Game::random_Piece(){
    int idx_cp = rand() % 7;
    currentPiece = nextPiece;
    idx_cp = rand() % 7;
    nextPiece = blocks.getPiece(idx_cp);
}

bool Game::moveDown(){
    // The only if statement check here is concerning the piece trespassing the ground
        ++cy;
        if(verify_Collision() == false){
            clockFall.restart();
            return true;
        }
        else{
            --cy; 
            for (int x = 0; x < 4; ++x) {
                for (int y = 0; y < 4; ++y) {
                    if (currentPiece[x][y] != 0) {
                        int limx = x + cx;
                        int limy = y + cy ; 
                        if (limy <=0) {
                            gameOver = 1;
                        }
                    }
                }
            }
            for (int x = 0; x < 4; ++x) {
                for (int y = 0; y < 4; ++y) {
                    if (currentPiece[x][y]) {
                        gridGame.getmatrixGrid()[cx + x][cy + y] = currentPiece[x][y] ;//Register the piece(memory)
                    } 
                }
            }
            gridGame.lineCleaning();
            random_Piece(); //Generates another piece when collides
            cx = 5;//grid.getCols_size()/2 ;//Starts the piece in the middle top
            cy = 0;
            clockFall.restart();
            return false;
            
        }
    return true;
}

void Game::printgameOver(){
        sf::Text text;
        sf::Font font;
        text.setFont(font);// set the string to display
        if (!font.loadFromFile("arial.ttf"))
            std::cout << "Letter font not found" << std::endl;
        std::cout << "Game over !" << std::endl;
        text.setString("Perdeu tudo");
        // set the character size
        text.setCharacterSize(24); // in pixels, not points!
        text.setPosition(0, 0 );
        // set the color
        text.setFillColor(sf::Color::Red);
        std::shared_ptr<sf::RenderWindow> window = gridGame.getWindow();
        window->draw(text);
}

void Game::run(){
    std::shared_ptr<sf::RenderWindow> window = windowGame.getWindow();
    int Lobby = windowGame.LobbyWindow();
    while(window->isOpen()){
        sf::Event event;
        while (window->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed)
                player_Input();
            if (event.type == sf::Event::KeyReleased)
                if(event.key.code == sf::Keyboard::Up)
                    flag_up = 0;
                if(event.key.code == sf::Keyboard::Space)
                    flag_hardDrop = 0;
        }
        delay = 0.5f;
        if(!gameOver && clockFall.getElapsedTime().asSeconds() > delay) moveDown(); 
        window->clear();
        gridGame.draw_grid();
        gridInfo.draw_grid();
        gridInfo.draw_nextPiece(nextPiece);
        if(gameOver) printgameOver();
        else blocks.draw_piece(window.get(), currentPiece, cx, cy);       
        window->display();
    }
}