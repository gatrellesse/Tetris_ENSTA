#include "Game.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include "Client.h"
#include "NetworkManager.h"
using namespace std;

Game::Game() : windowGame(), gridGame(windowGame.getWindow()), gridInfo(windowGame.getWindow()), blocks(30){ //era pra ser grid.getCell_size()

    std::cout << "Play time!" << std::endl; // Timer to control delay
    if (!musicGame.openFromFile("musicGaming.ogg")) { // Replace with your music file path
        std::cout << "Erro ao carregar a música!" << std::endl;
    }
    if (!soundGameOver.openFromFile("soundGameOver.ogg")) { // Replace with your music file path
        std::cout << "Erro ao carregar a música!" << std::endl;
    }
    delay = 1.0f; // Delay in seconds 
    delayDefault = 1.0f;
    nextPiece = blocks.getPiece(rand() % 7); //First piece of the game
    random_Piece();
    cx = 5;//grid.getCols_size()/2 ;//Starts the piece in the middle top
    cy = 0;
    cx_ghost = cx;
    cy_ghost = cy;
    rows = 20;
    cols = 10;
}

Game::~Game(){
}

void Game::drawGhostTetromino(std::shared_ptr<sf::RenderWindow> window){
    while(moveGhostDown() == true){
    }
    blocks.draw_Ghost_piece(window.get(), currentPiece, cx_ghost, cy_ghost);       
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
        if (verify_Collision()){ 
            rotate();rotate();rotate();//Desfaz a rotacao q colidiu
            }
    }
    else if(flag_hardDrop == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ //hardrop
        flag_hardDrop = 1;
        while(moveDown() == true){}
    }

    
}
bool Game::verify_Ghost_Collision(){
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            if (currentPiece[x][y] != 0) {
                int limx = x + cx_ghost;
                int limy = y + cy_ghost ; 
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

bool Game::moveGhostDown(){
    ++cy_ghost;
    if(verify_Ghost_Collision() == false){
            return true;
        }
    else{
        --cy_ghost; 
        return false;}
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
            if(gameOver){
                musicGame.stop();
                soundGameOver.play();
                windowGame.EndGameWindow();// Is going to another loop of window
                restartValues();
                return false;
                }
            int linesCleaned = gridGame.lineCleaning();
            score.calculatePoints(linesCleaned);
            random_Piece(); //Generates another piece when collides
            cx = 5;//grid.getCols_size()/2 ;//Starts the piece in the middle top
            cy = 0;
            cx_ghost = cx;
            cy_ghost = cy;
            clockFall.restart();
            return false;
            
            
        }
    return true;
}

void Game::restartValues(){
    gridGame.restartValues();
    clockFall.restart();
    musicGame.setLoop(true);  // Loop the music
    musicGame.play();
    gameOver = 0;
    delay = delayDefault;
    cx = 5;
    cy = 0;
    Score newScore;
    score = newScore;
    
}

void Game::run(){
    std::shared_ptr<sf::RenderWindow> window = windowGame.getWindow();
    sf::RectangleShape pauseButton = gridInfo.getPauseButton();
    int Lobby = windowGame.LobbyWindow();
    if(Lobby == 0) return;
    int Match = 2;
    string flagChosen = "Nothing";
    while(Lobby == 2 && Match == 2){
        if(Lobby == 2){//Chose to do match
            Match = windowGame.MatchWindow();
        }
        if(Match == 2){//Chose to go back to lobby
            Lobby = windowGame.LobbyWindow();
        }
    }
    NetworkManager serverTem(550,1);
    if(Match == 0) {
        Client client(550, "127.0.0.1");
        while(!client.searchServer()){}
        client.receiveMessage();
    }
    else{
         serverTem.statusServer();
         while(!serverTem.connectClients("127.0.0.1")){}
         serverTem.sendMessage();
         }
         
    
    //Chose to play solo
    musicGame.setLoop(true);  // Loop the music
    musicGame.play();
    // Load the music
    while(window->isOpen()){
        sf::Event event;
        while (window->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed){
                player_Input();
                cx_ghost = cx;
                cy_ghost = cy;
            }
            if (event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::Up)
                    flag_up = 0;
                if(event.key.code == sf::Keyboard::Space)
                    flag_hardDrop = 0;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
                if (pauseButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    musicGame.pause();
                    int pauseReturn = windowGame.PauseWindow();
                    if(pauseReturn == 1) musicGame.play();
                    else if(pauseReturn == 2){
                        musicGame.stop();
                        restartValues();
                    }
                }
            }
                
        }
        delay = delayDefault * score.getSpeedFactor(); //Increases it based on levelmake
        window->clear();
        gridGame.draw_grid();
        gridInfo.draw_grid(score.getLevel(), score.getScore());
        gridInfo.draw_nextPiece(nextPiece);
        drawGhostTetromino(window);
        blocks.draw_piece(window.get(), currentPiece, cx, cy);       
        window->display();
        if(!gameOver && clockFall.getElapsedTime().asSeconds() > delay) moveDown(); 
    }
}