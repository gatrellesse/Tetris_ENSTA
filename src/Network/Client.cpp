#include "Client.h"
#include "Colors.h"
#include "PacketsMap.cpp"
#include <SFML/Audio.hpp>
#include <chrono>

/**
 * @class Client
 * @brief Manages client-side operations, including server connections and interactions.
 */

/**
 * @brief Constructs a new Client instance.
 * 
 * @param clientType The type of client (e.g., "Client" or "Server").
 */
Client::Client(string clientType ): clientType(clientType) {
    connected = false;
    nGamesOver = 0;
    timeout = 60;
    std::cout<<"Client instance created" << std::endl;
}

/**
 * @brief Destructor for the Client class.
 */
Client::~Client()
{
    
}

/**
 * @brief Connects the client to the server.
 * 
 * Attempts to establish a connection to the server. Retries until connected or until timeout occurs.
 */
void Client::connect(){
    auto startTime = std::chrono::steady_clock::now();
    std::string serverIp;
   
   while(!connected){
     if(clientType == "Client"){ 
         serverIp = (string)IP_SERVER;
         cout<<"SERVER IP ALLOCATED" << endl;
         }
    else if(clientType == "ClientServer") {
        serverIp = (string)LOCAL_HOST;
        cout <<"LOCALHOST IP ALLOCATED" << endl;
    }
    currentPort = (int)PORT_SERVER;
        std::cout << "Client trying to connect to: " << serverIp << ":"<< currentPort << std::endl;
        auto elapsed = std::chrono::steady_clock::now() - startTime;
        if(socket.connect(serverIp, currentPort) != sf::Socket::Done){
            cout << "Client failed to connect to server-->Retrying" << endl;
        }
        else{
            // Load the music
            sf::Music music;
            if (!music.openFromFile("src/Assets///playerConnected.ogg")) { 
                std::cout << "Error loading music!" << std::endl;
            }
        
            // Play the music
            music.play();
            sf::Clock clock;
            while (clock.getElapsedTime().asSeconds() < 1.5f) {}
            connected = true;
            break;
        }
        if(std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() > timeout){
            return;
        }
    }
    cout << "Client connected to server" << endl;
    // 1 packet sent by the server
    sf::Packet idPacket;
    if(socket.receive(idPacket) != sf::Socket::Done){
        cout << "Failed to get ID froms server" << endl;
        connected = false;
        return;
    }
    idPacket >> id;
    cout << "Client started with ID " << id << endl;

    // 2 packet sent by the server
    sf::Packet nOpponentsPacket;
    if(socket.receive(nOpponentsPacket) != sf::Socket::Done){
        cout << "Failed to get number of opponents froms server" << endl;
        connected = false;
        return;
    }
    nOpponentsPacket >> nOpponents;
    
    scores.resize(nOpponents, 0);
    ranking.resize(nOpponents, 0);
    //Iniate a empty grid for the client connection
    for(int i = 0; i < nOpponents; i++) { 
       gridCollection.emplace_back(10, std::vector<unsigned char>(20, 0));
    }


    cout << "Client competing with  " << id << " players"<<endl;
     // Ensure any previous thread is stopped before starting a new one
    if (receiveThread.joinable()) {
        receiveThread.join();
    }
    // Start the network communication thread
    // This allows the client to keep receiving and sending data
    //    without pertubating the thread of the game per say
    //AVOID USING DETACH TO AVOID SEGMENTATION FAULT WHEN DISCONNECTING
    receiveThread = std::thread(&Client::connectedLoop, this);

}

/**
 * @brief Handles the main communication loop while connected.
 * 
 * Continuously receives data packets from the server and processes them using the handlePacket method.
 */
void Client::connectedLoop() {
    while (connected) {
        sf::Packet dataPack;
        if (socket.receive(dataPack) != sf::Socket::Done) {
            std::cout << "Failed to receive data from server" << std::endl;
            connected = false;
            break;
        }
        
        int type;
        dataPack >> type;
        handlePacket(type, dataPack); // Handle packet based on its type
    }
}

/**
 * @brief Processes received packets based on their type.
 * 
 * @param type The type of the received packet.
 * @param packet The packet to be processed.
 */
void Client::handlePacket(int type, sf::Packet& packet) {
     switch (type) {
        case PACKET_TYPE_GAMEOVER:// Handle when someone has lost
            nGamesOver++;
            break;
        case PACKET_TYPE_START: // Handle game start packet
            gameStarted = true;
            break;
        case PACKET_TYPE_FINISHGAME:{ // Handle when everyone has lost
            std::cout << "Game finished" << std::endl;
            for (int i = 0; i < nOpponents; i++){
                packet >> ranking[i] >> scores[i];
            }
            gameFinished = true;
            break;
        }
        case PACKET_TYPE_GRID:{
            int updateID, numChanges;
            //cout << "Client received enemy grid"<<endl;
            packet >> updateID >> numChanges;
            //cout<<"ID changed: " << updateID<<  " Changed cells: " << numChanges << endl;
            for (int i = 0; i < numChanges; ++i) {
                int x, y;
                unsigned char value;
                packet >> x >> y >> value;
                //cout << "x : " << x << " y: " << y  <<endl;
                gridCollection[updateID][x][y] = value; // Apply changes
            }
            break;
        }
        case PACKET_TYPE_SCORE:{
            scoreRegistred = true;
            break;
        }
        default:
            std::cout << "Unknown packet type received: " << type << std::endl;
    }
}

/**
 * @brief Sends a message to the server.
 * 
 * @param packet The packet to send.
 */
void Client::sendMessage(sf::Packet packet){
    if(socket.send(packet) != sf::Socket::Done){
        cout << "Failed to send pack from client " << endl;
    }
}

/**
 * @brief Sends a "Game Over" notification to the server.
 */
void Client::sendGameOver(){
    sf::Packet gameOverPack;
    gameOverPack << (int)PACKET_TYPE_GAMEOVER;
    if(socket.send(gameOverPack) != sf::Socket::Done){
        cout << "Failed to send pack from client " << endl;
    }
}

/**
 * @brief Sends the client's score to the server.
 * 
 * @param score The score to send.
 */
void Client::sendScore(int score){
    sf::Packet scorePack;
    scorePack << (int)PACKET_TYPE_SCORE << score;
    if(socket.send(scorePack) != sf::Socket::Done){
        cout << "Failed to send pack from client " << endl;
    }
}

/**
 * @brief Sends grid updates to the server.
 * 
 * @param changedCells A vector of cells that have changed, each represented as a tuple (x, y, value).
 */
void Client::sendGrid(const std::vector<std::tuple<int, int, unsigned char>>& changedCells) {
    if (changedCells.empty()) return; // Skip sending if nothing changed
    sf::Packet gridPack;
    gridPack << (int)PACKET_TYPE_GRID <<id << (int)changedCells.size();
    //cout<<"ID changed: " << id<<  " Changed cells: " << (int)changedCells.size() << endl;
    for (const auto& cell : changedCells) {
        gridPack << std::get<0>(cell) << std::get<1>(cell) << std::get<2>(cell);
        //cout << "x : " <<std ::get<0>(cell)  << " y: " << std::get<1>(cell)  <<endl;
    }

    if (socket.send(gridPack) != sf::Socket::Done) {
        std::cout << "Failed to send grid update." << std::endl;
    }
}

/**
 * @brief Marks the game as finished for the client.
 */
void Client::setGameOver(){
    gameFinished = true;
}

/**
 * @brief Retrieves the number of opponents in the game.
 * 
 * @return The number of opponents.
 */
int Client::getNumberOpponents() const{
    return nOpponents;
}

/**
 * @brief Retrieves the number of players who have lost the game.
 * 
 * @return The number of players who have lost.
 */
int Client::getNumberGamesOver() const{
    return nGamesOver;
}

/**
 * @brief Retrieves the current ranking of all players.
 * 
 * @return A constant reference to the ranking vector.
 */
const std::vector<int>& Client::getRanking() const{
    return ranking;
}

/**
 * @brief Retrieves the scores of all players.
 * 
 * @return A constant reference to the scores vector.
 */
const std::vector<int>& Client::getScores() const {
    return scores;
}

/**
 * @brief Retrieves the ID of the client.
 * 
 * @return The client ID.
 */
int Client::getID() const{
    return id;
}

/**
 * @brief Checks if the client is connected to the server.
 * 
 * @return True if connected, false otherwise.
 */
bool Client::isConnected(){
    return connected;
}

/**
 * @brief Checks if the game has started for the client.
 * 
 * @return True if the game has started, false otherwise.
 */
bool Client::isGameStarted(){
    return gameStarted;
}

/**
 * @brief Checks if the game has finished for the client.
 * 
 * @return True if the game has finished, false otherwise.
 */
bool Client::isGameFinished() {
    return gameFinished;
}

/**
 * @brief Checks if the score has been registered.
 * 
 * @return True if the score has been registered, false otherwise.
 */
bool Client::isScoreRegistred() {
    return scoreRegistred;
}

/**
 * @brief Draws the grids of all opponents on the provided window.
 * 
 * @param window Pointer to the SFML window where the grids will be drawn.
 */
void Client::drawEnemies(sf::RenderWindow *window) {
    int rows = 20;
    int cols = 10;
    int cell_size = 14;  // Half of the main grid cell size
    int cell_size_original = 30;
    int spacing_x = 35;  // Small gap between enemy grids

    // Positioning starts from the rightmost part of the window
    int baseX = cell_size_original * 20 + spacing_x;  // Start at 600px where enemy grids should be drawn
    int baseY = (rows*cell_size_original - 2*(rows*cell_size + spacing_x))/2;  // Align enemy grids at the top

    int countingTwo = 0;
    int offset = 0;

    for (int k = 0; k < nOpponents; ++k) {
        if (k == id) continue;  // Skip the current player's grid

        int startX = baseX;
        int startY = baseY + ((offset % 2) * (rows * cell_size + spacing_x));  // Offset for vertical stacking

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                sf::RectangleShape cell(sf::Vector2f(cell_size - 0.8, cell_size - 0.8));
                cell.setPosition(startX + x * cell_size, startY + y * cell_size);

                if (gridCollection[k][x][y]) {
                    sf::Color color = GetCellColors()[gridCollection[k][x][y] - 1];
                    cell.setFillColor(color);
                } else {
                    cell.setFillColor(sf::Color::Black);
                }

                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::White);
                window->draw(cell);
            }
        }

        ++countingTwo;
        ++offset;  // Move to the next enemy grid

        // After two grids, adjust the baseX for the next pair
        if (countingTwo == 2) {
            countingTwo = 0;
            baseX = startX + (cols * cell_size) + spacing_x;  // Update baseX based on the furthermost right cell
            baseY = (rows*cell_size_original - 2*(rows*cell_size + spacing_x))/2;    
        }
    }
}

/**
 * @brief Disconnects the client from the server.
 * 
 * Ensures all threads are joined and resources are cleaned up.
 */
void Client::disconnect(){
    std::cout << "Disconnecting..." << std::endl;
    if (connected) {
        socket.disconnect(); // Disconnect from the server
        connected = false;
        std::cout << "Client disconnected from the server." << std::endl;
    }
    // Wait for the receive thread to stop
    std::cout << "Deleting thread..." << std::endl;
    if (receiveThread.joinable()) {
        receiveThread.join();
        std::cout << "Receive thread stopped." << std::endl;
    }
    std::cout << "No more client and its threads" << std::endl;

    
}


