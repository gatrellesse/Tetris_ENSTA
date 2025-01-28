#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>  // Ensure this is included to use sf::RenderWindow
#include <iostream>
#include <thread>
using namespace std;
#pragma once

/**
 * @class Client
 * @brief Represents a network client that communicates with a server and manages game states.
 */
class Client
{
public:
    /**
     * @brief Constructs a new Client instance.
     * 
     * @param clientType The type of client (default is "Client").
     */
    Client(string clientType = "Client");

    /**
     * @brief Destructor for the Client class.
     */
    ~Client(); 

    /**
     * @brief Sends a custom packet to the server.
     * 
     * @param packet The packet to be sent.
     */
    void sendMessage(sf::Packet packet);

    /**
     * @brief Notifies the server that the client has lost (game over).
     */
    void sendGameOver();

    /**
     * @brief Sends the client's current score to the server.
     * 
     * @param score The score to send.
     */
    void sendScore(int score);

    /**
     * @brief Sends grid updates to the server.
     * 
     * @param changedCells A vector of cells that have changed, each represented as a tuple (x, y, value).
     */
    void sendGrid(const std::vector<std::tuple<int, int, unsigned char>>& changedCells);

    /**
     * @brief Connects the client to the server.
     */
    void connect();

    /**
     * @brief Disconnects the client from the server and cleans up resources.
     */
    void disconnect();

    /**
     * @brief Handles the communication loop while the client is connected.
     */
    void connectedLoop();

    /**
     * @brief Processes a packet received from the server.
     * 
     * @param type The type of the packet.
     * @param packet The packet to process.
     */
    void handlePacket(int type, sf::Packet& packet);

    /**
     * @brief Sets the game state to "Game Over" for single-player purposes.
     */
    void setGameOver();//single player purposes

    /**
     * @brief Draws the grids of opponents on the provided SFML window.
     * 
     * @param window Pointer to the SFML window for rendering.
     */
    void drawEnemies(sf::RenderWindow *window);

    /**
     * @brief Retrieves the current ranking of players.
     * 
     * @return A constant reference to the ranking vector.
     */
    const std::vector<int>& getRanking() const;

    /**
     * @brief Retrieves the current scores of players.
     * 
     * @return A constant reference to the scores vector.
     */
    const std::vector<int>& getScores() const;

    /**
     * @brief Retrieves the number of opponents in the game.
     * 
     * @return The number of opponents.
     */
    int getNumberOpponents() const;

    /**
     * @brief Retrieves the number of players who have lost the game.
     * 
     * @return The number of players who have lost.
     */
    int getNumberGamesOver() const;

    /**
     * @brief Retrieves the ID of the client.
     * 
     * @return The client ID.
     */
    int getID() const;

    /**
     * @brief Checks if the client is connected to the server.
     * 
     * @return True if connected, false otherwise.
     */
    bool isConnected();

    /**
     * @brief Checks if the game has started.
     * 
     * @return True if the game has started, false otherwise.
     */
    bool isGameStarted();

    /**
     * @brief Checks if the game has finished.
     * 
     * @return True if the game has finished, false otherwise.
     */
    bool isScoreRegistred();
    
    /**
     * @brief Checks if the game has finished.
     * 
     * @return True if the game has finished, false otherwise.
     */
    bool isGameFinished();

private:
    sf::TcpSocket socket;
    std::thread receiveThread;  
    int currentPort;
    int id;
    int gameWinner = 0;
    int nGamesOver;
    int nOpponents;
    int timeout;
    bool connected;
    bool scoreRegistred = false;
    bool gameStarted = false;
    bool gameFinished = false;
    string clientType;
    std::vector<std::vector<std::vector<unsigned char>>> gridCollection;
    std::vector<int> scores;
    std::vector<int> ranking;


};
