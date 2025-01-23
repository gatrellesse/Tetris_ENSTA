#include <SFML/Network.hpp>
#include <iostream>
using namespace std;
#pragma once

/**
 * @class Client
 * @brief Manages the client-side networking for a Tetris game.
 * 
 * The Client class handles connecting to the server, sending and receiving packets,
 * and managing the game state based on server communication.
 */
class Client
{
public:
    /**
     * @brief Constructs a Client object.
     * 
     * Initializes the client instance with the provided port and IP address.
     * Sets default values for connection status, timeout, and game state.
     * 
     * @param myPort The port number to connect to.
     * @param myIP The IP address of the server.
     */
    Client(int myPort, string myIP);

    /**
     * @brief Destructor for the Client class.
     */
    ~Client(); 

    /**
     * @brief Sends a message (packet) to the server.
     * 
     * @param packet The SFML packet to send to the server.
     */
    void sendMessage(sf::Packet packet);

    /**
     * @brief Attempts to connect the client to the server.
     * 
     * Tries to establish a connection to the server at the specified IP and port.
     * Starts a separate thread for handling communication if successful.
     */
    void connect();

    /**
     * @brief The main loop for handling server communication.
     * 
     * Continuously receives packets from the server and processes them.
     */
    void connectedLoop();

    /**
     * @brief Handles incoming packets from the server.
     * 
     * Processes packets based on their type and updates the game state accordingly.
     * 
     * @param type The type of the packet.
     * @param packet The SFML packet received from the server.
     */
    void handlePacket(int type, sf::Packet& packet);

    /**
     * @brief Checks if the client is connected to the server.
     * 
     * @return bool Returns `true` if the client is connected, otherwise `false`.
     */
    bool isConnected();

    /**
     * @brief Checks if the game has started.
     * 
     * @return bool Returns `true` if the game has started, otherwise `false`.
     */
    bool isGameStarted();

private:
    sf::TcpSocket socket; /**< TCP socket for client-server communication. */
    int currentPort; /**< The port number used to connect to the server. */
    string IP; /**< The IP address of the server. */
    int id; /**< The unique ID assigned to the client by the server. */
    int gameWinner = 0; /**< The ID of the game winner (if applicable). */
    int timeout; /**< Timeout duration for connection attempts. */
    bool connected; /**< Connection status of the client. */
    bool gameStarted = false; /**< Indicates whether the game has started. */
    bool gameFinished = false; /**< Indicates whether the game has finished. */

};
