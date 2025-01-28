
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <mutex>
#include <functional>
using namespace std;
#pragma once

/**
 * @class Server
 * @brief Manages server-side operations, including client connections, game state management, and packet handling.
 */
class Server
{
public:
    /**
     * @brief Constructs a new Server instance.
     * 
     * @param waitingFor The number of clients the server is waiting to connect.
     */
    Server(int waitingFor);

    /**
     * @brief Destructor for the Server class. Cleans up resources and stops the server.
     */
    ~Server();

    /**
     * @brief Sends a packet to all connected clients.
     * 
     * @param packet The packet to be sent.
     */
    void sendAll(sf::Packet packet);

    /**
     * @brief Sends a packet to all connected clients except one specified.
     * 
     * @param packet The packet to be sent.
     * @param id The ID of the client to exclude from receiving the packet.
     */
    void sendAllExcept(sf::Packet packet, int id);

    /**
     * @brief Stops the server and disconnects all clients.
     */
    void stop();  

    /**
     * @brief Starts the server and begins listening for client connections.
     */
    void run();

    /**
     * @brief Starts the game by notifying all connected clients.
     */
    void startGame();

    /**
     * @brief Accepts incoming client connections.
     */
    void acceptingClients();

    /**
     * @brief Handles communication with a specific client.
     * 
     * @param socket The socket of the client.
     * @param clientID The ID of the client.
     */
    void handleClient(std::shared_ptr<sf::TcpSocket>& socket, int clientID);

    /**
     * @brief Processes a packet received from a specific client.
     * 
     * @param type The type of the packet.
     * @param packet The packet to process.
     * @param clientID The ID of the client who sent the packet.
     */
    void handlePacket(int type, sf::Packet& packet, int clientID);

private:
    int port;
    int nClients;
    int numConnections;
    bool running;
    bool inGame;
    sf::TcpListener listener;
    sf::IpAddress adress;
    std::vector<std::shared_ptr<sf::TcpSocket>> clients;
    std::mutex clientsMutex;
    void getWinner();
    int nGamesOver;
    int winner;
    std::vector<bool>* gamesOver;
    std::vector<int>* scores;
    std::vector<int>* ranking;
    
};
