#include "Game.h"
#include <SFML/Audio.hpp>
#include <iostream>


#include <thread>  // For sleep functionality
#include <chrono>
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
    if (gameMode == "Match") {
    std::vector<std::tuple<int, int, unsigned char>> changedCells = gridGame.getChangedCells();
    if (!changedCells.empty()) {
        client->sendGrid(changedCells); // Send only modified cells
    }
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

void Game::random_Piece() {
    int idx_cp = rand() % 7;
    currentPiece = nextPiece;
    cx = 5;
    cy = 0;
    // Generate next piece
    idx_cp = rand() % 7;
    nextPiece = blocks.getPiece(idx_cp);
    if(verify_CollisionAtSpawn()){
        setGameOver();
    }  // Check for collision at spawn position
}

bool Game::verify_CollisionAtSpawn() {
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            if (currentPiece[x][y] != 0) {
                int limx = x + 5;  // Default spawn position (middle of the grid)
                int limy = y;  // Top of the grid
                if (gridGame.getmatrixGrid()[limx][limy] != 0) {
                    return true;  // Collision detected
                }
            }
        }
    }
    return false;  // No collision
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
            if (gameMode == "Match") {
        std::vector<std::tuple<int, int, unsigned char>> changedCells = gridGame.getChangedCells();
        if (!changedCells.empty()) {
            client->sendGrid(changedCells); // Send only modified cells
        }
        }
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
                        if (limy <=-1) {
                            setGameOver();  // End game if a piece is stuck at the top
                        

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
            if (gameMode == "Match") {
            std::vector<std::tuple<int, int, unsigned char>> changedCells = gridGame.getChangedCells();
            if (!changedCells.empty()) {
                client->sendGrid(changedCells); // Send only modified cells
            }
            }
            if(gameOver){
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
    if(whichWindow == "Gaming"){
    musicGame.setLoop(true);  // Loop the music
    musicGame.play();
    }
    gameOver = 0;
    delay = delayDefault;
    cx = 5;
    cy = 0;

    delay = 1.0f; // Delay in seconds 
    delayDefault = 1.0f;
    nextPiece = blocks.getPiece(rand() % 7); //First piece of the game
    random_Piece(); 

    cx_ghost = cx;
    cy_ghost = cy;
    Score newScore;
    score = newScore;
    
}

void Game::setGameOver(){
    client->sendScore(score.getScore());//Send score before sending endgame
    while(!client->isScoreRegistred()){
        //Wait to sendGameOver to avoid desinc.
    }
    client->sendGameOver();
    musicGame.stop();
    soundGameOver.play();
    int endGame;
    while(!client->isGameFinished()){
        endGame = windowGame.EndGameWindow(gameMode, client->getNumberOpponents(), client->getNumberGamesOver(),
                                            client->isGameFinished(), client->getScores(), client->getRanking());
    }
    endGame = windowGame.EndGameWindow(gameMode, client->getNumberOpponents(), client->getNumberGamesOver(),
                                            client->isGameFinished(), client->getScores(), client->getRanking());
    if(endGame == 1) restartValues();
    else if(endGame == 2) {
        whichWindow = "Lobby";}
}

void Game::run(){
    while(!exitPressed){
    restartValues();
    std::shared_ptr<sf::RenderWindow> window = windowGame.getWindow();
    sf::RectangleShape pauseButton = gridInfo.getPauseButton();
    int Lobby = windowGame.LobbyWindow();
    if(Lobby == 0){ 
        exitPressed = true;
        break; //Exit pressed
        }
    int Match = 2;
    while(Lobby == 2 && Match == 2){ //Match pressed
        if(Lobby == 2){//Chose to do match
            Match = windowGame.MatchWindow();
        }
        if(Match == 2){//Chose to go back to lobby
            Lobby = windowGame.LobbyWindow();
        }
    }

    int nPlayers;
    if(Lobby == 1){
        gameMode = "Single";
        nPlayers = 1;
        cout<<"single player started" << endl;
    }
    else if(Lobby == 2){ 
        gameMode = "Match";
        nPlayers = 2;
    }
    if(Match == 0) {//Client
        if (client) { client->disconnect(); delete client; client = nullptr; }
        if (server) { server->stop(); delete server; server = nullptr; }
        client = new Client("Client");
        client->connect();
    }
    if(Match == 1 || gameMode == "Single"){//Host client
        if (server) { server->stop(); delete server; server = nullptr; }
        if (client) { client->disconnect(); delete client; client = nullptr; }
        server = new Server(nPlayers);
        server->run();
        

        client = new Client("ClientServer");
        client->connect();
    }
    while(Lobby != 1 && !client->isGameStarted()){
        //The players are waiting for all clients to connect
        //Skip it if start single game pressed(instantaly)
    }
    if(Lobby == 2) { 
        int fenetre = nPlayers;
    if (nPlayers % 2 == 1) fenetre = nPlayers - 1;
    unsigned int newWidth = 30 * (20 +  6.5 * (fenetre / 2));;
    unsigned int newHeight = 600; //never changes

    window->setSize(sf::Vector2u(newWidth, newHeight));
    windowGame.resizeWindow(newWidth, newHeight);

    // Update the view to match the new window size
    sf::View view(sf::FloatRect(0, 0, newWidth, newHeight));
    window->setView(view);
    }
    whichWindow = "Gaming";
    musicGame.setLoop(true);  // Loop the music
    musicGame.play();
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
                if (gameMode == "Single" && pauseButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    whichWindow = "Pause";
                    musicGame.pause();
                    int pauseReturn = windowGame.PauseWindow();
                    // pauseReturn == 0 exit game
                    if(pauseReturn == 1) musicGame.play();//continue
                    else if(pauseReturn == 2){//restart
                        whichWindow = "Gaming";
                        musicGame.stop();
                        restartValues();
                    }
                    else if(pauseReturn == 3){//lobby
                        restartValues();
                        whichWindow = "Lobby";
                        break;
                    }
                }
            }
                
        }
    if(whichWindow == "Lobby") {//Player paused the game and clicked lobby
        musicGame.stop();
        unsigned int newWidth = 600;
        unsigned int newHeight = 600;
        window->setSize(sf::Vector2u(newWidth, newHeight));
        windowGame.resizeWindow(newWidth, newHeight);

        // Update the view to match the new window size
        sf::View view(sf::FloatRect(0, 0, newWidth, newHeight));
        window->setView(view);
        client->disconnect();
        if(server) server->stop();
        break;
    }
    delay = delayDefault * score.getSpeedFactor(); //Increases it based on levelmake
    window->clear();
    gridGame.draw_grid();
    if(gameMode == "Match") client->drawEnemies(window.get());
    gridInfo.draw_grid(score.getLevel(), score.getScore());
    gridInfo.draw_nextPiece(nextPiece);
    drawGhostTetromino(window);
    blocks.draw_piece(window.get(), currentPiece, cx, cy);       
    window->display();
    if(!gameOver && clockFall.getElapsedTime().asSeconds() > delay) moveDown(); 
    }
 }
}