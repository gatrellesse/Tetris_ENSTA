#include "Game.h"
#include <SFML/Audio.hpp>
#include <iostream>


#include <thread>  // For sleep functionality
#include <chrono>
using namespace std;

/**
 * @brief Constructs a Game object.
 * 
 * Initializes the game elements, including the grid, blocks, music, and initial game state.
 */
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
    nextPiece = blocks.getPiece(rand() % 7); // First piece of the game
    random_Piece();
    cx = 5; // grid.getCols_size()/2 ;//Starts the piece in the middle top
    cy = 0;
    cx_ghost = cx;
    cy_ghost = cy;
    rows = 20;
    cols = 10;
}

/**
 * @brief Destructor for the Game class.
 */
Game::~Game(){
}

/**
 * @brief Draws the ghost piece on the grid.
 * 
 * The ghost piece indicates where the current piece will land if dropped.
 * 
 * @param window A shared pointer to the SFML render window.
 */
void Game::drawGhostTetromino(std::shared_ptr<sf::RenderWindow> window){
    while(moveGhostDown() == true){ // Moves the ghost piece down until it collides
    }
    blocks.draw_Ghost_piece(window.get(), currentPiece, cx_ghost, cy_ghost);       
}

/**
 * @brief Rotates the current piece clockwise.
 */
void Game::rotate(){
    int len = 0;
    int idx_piece = 0;
    for (int x = 0; x < 4; x++) 
        for (int y = 0; y < 4; y++)
            if (currentPiece[x][y]) {
                idx_piece = currentPiece[x][y];
                len = max(max(x, y) + 1, len); // Checks if it is 2/3/4
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

/**
 * @brief Handles player input for moving and rotating the piece.
 */
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
        rotate(); // Temporary rotation
        if (verify_Collision()){ 
            rotate();rotate();rotate(); // Reverses the rotation that caused a collision
            }
    }
    else if(flag_hardDrop == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ // Hardrop
        flag_hardDrop = 1;
        while(moveDown() == true){}
    }

    
}

/**
 * @brief Checks if the ghost piece collides with the grid.
 * 
 * @return bool Returns true if a collision is detected, otherwise false.
 */
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

/**
 * @brief Checks if the current piece collides with the grid.
 * 
 * @return bool Returns true if a collision is detected, otherwise false.
 */
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

/**
 * @brief Generates a new random piece.
 */
void Game::random_Piece(){
    int idx_cp = rand() % 7;
    currentPiece = nextPiece;
    idx_cp = rand() % 7;
    nextPiece = blocks.getPiece(idx_cp);
}

/**
 * @brief Moves the ghost piece down one step.
 * 
 * @return bool Returns true if the ghost piece moved successfully, otherwise false.
 */
bool Game::moveGhostDown(){
    ++cy_ghost;
    if(verify_Ghost_Collision() == false){
            return true;
        }
    else{
        --cy_ghost; 
        return false;}
}

/**
 * @brief Moves the current piece down one step.
 * 
 * If the piece collides, it registers the piece on the grid and generates a new piece.
 * 
 * @return bool Returns true if the piece moved successfully, otherwise false.
 */
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
                        gridGame.getmatrixGrid()[cx + x][cy + y] = currentPiece[x][y]; // Register the piece(memory)
                    } 
                }
            }
            if(gameOver){
                musicGame.stop();
                soundGameOver.play();
                windowGame.EndGameWindow(); // Is going to another loop of window
                restartValues();
                return false;
                }
            int linesCleaned = gridGame.lineCleaning();
            score.calculatePoints(linesCleaned);
            random_Piece(); // Generates another piece when collides
            cx = 5; // grid.getCols_size()/2; // Starts the piece in the middle top
            cy = 0;
            cx_ghost = cx;
            cy_ghost = cy;
            clockFall.restart();
            return false;
            
            
        }
    return true;
}

/**
 * @brief Resets the game state to its initial values.
 */
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

/**
 * @brief Main game loop.
 * 
 * Handles the game's core logic, including:
 * - Rendering the grid and pieces.
 * - Managing player input.
 * - Handling game states such as lobby, match, and pause.
 */
void Game::run(){
    // Get the window instance
    std::shared_ptr<sf::RenderWindow> window = windowGame.getWindow();

    // Retrieve the pause button from the grid information
    sf::RectangleShape pauseButton = gridInfo.getPauseButton();

    // Show the lobby menu
    int Lobby = windowGame.LobbyWindow();
    if(Lobby == 0) return; // Exit pressed

    int Match = 2; /**< Match state: 2 represents "undecided". */
    string flagChosen = "Nothing";

    // Match loop to handle match/lobby navigation
    while(Lobby == 2 && Match == 2){ // Match pressed
        if(Lobby == 2){ // Player chose to enter match menu
            Match = windowGame.MatchWindow();
        }
        if(Match == 2){ // Player chose to return to lobby
            Lobby = windowGame.LobbyWindow();
        }
    }
    
    // Network setup
    if(Match == 0) { // Client mode
        delete server; // Ensure no existing server is running
        delete client; // Ensure no existing client instance exists
        std::string address2 = "127.0.0.1";
        client = new Client(53000, address2); // Create a client instance
        client->connect(); // Connect to the server
    }
    else if(Match == 1){ // Host client mode
        delete server;
        delete client;
        server = new Server(53000, 2); // Create a server instance
        server->run(); // Start the server
        
        std::string address2 = "127.0.0.1";
        client = new Client(53000, address2); // Create a client instance
        client->connect(); // Connect to the server
    }

    // Start playing music
    musicGame.setLoop(true);  // Loop the music
    musicGame.play();

    // Wait for all players to connect if in multiplayer mode
    while(Lobby != 1 && !client->isGameStarted()){
        // The players are waiting for all clients to connect
        // Skip this if "Start Single Game" was selected
    }

    // Load the music
    while(window->isOpen()){
        sf::Event event;
        while (window->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window->close();
            
            // Handle key press events
            if (event.type == sf::Event::KeyPressed){
                player_Input(); // Handle player input
                cx_ghost = cx; // Update ghost piece position
                cy_ghost = cy;
            }

            // Handle key release events
            if (event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::Up)
                    flag_up = 0; // Reset rotation flag
                if(event.key.code == sf::Keyboard::Space)
                    flag_hardDrop = 0; // Reset hard drop flag
            }

            // Handle mouse button press (pause button)
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
                if (pauseButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    musicGame.pause();
                    int pauseReturn = windowGame.PauseWindow();  // Show pause menu
                    if(pauseReturn == 1) musicGame.play(); // Continue game
                    else if(pauseReturn == 2){ // Restart game
                        musicGame.stop();
                        restartValues();
                    }
                }
            }
                
        }

        // Adjust delay based on the player's level
        delay = delayDefault * score.getSpeedFactor(); 

        // Clear and redraw the game grid and elements
        window->clear();
        gridGame.draw_grid(); // Draw the grid
        gridInfo.draw_grid(score.getLevel(), score.getScore()); // Draw score and level info
        gridInfo.draw_nextPiece(nextPiece); // Draw the next piece
        drawGhostTetromino(window); // Draw the ghost piece
        blocks.draw_piece(window.get(), currentPiece, cx, cy); // Draw the current piece
        window->display();

        // Handle piece movement if the timer exceeds the delay
        if(!gameOver && clockFall.getElapsedTime().asSeconds() > delay) moveDown(); 
    }
}