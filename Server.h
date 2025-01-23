#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;
#pragma once

/**
 * @class Server
 * @brief Manages the server-side logic for a multiplayer game.
 * 
 * The Server class handles client connections, broadcasting messages, and managing the game state.
 * It supports a specified number of clients and uses TCP sockets for communication.
 */
class Server
{
public:
    /**
     * @brief Constructs a Server object.
     * 
     * Initializes the server on the given port and prepares to accept the specified number of clients.
     * 
     * @param portUser The port number the server will listen on.
     * @param waitingFor The number of clients the server will manage.
     */
    Server(int portUser, int waitingFor);

    /**
     * @brief Destructor for the Server class.
     * 
     * Ensures that the server is properly shut down and all resources are released.
     */
    ~Server();

    /**
     * @brief Binds the server to the specified port and starts listening for connections.
     * 
     * Logs an error if the binding fails and updates the server's running status.
     */
    void statusServer();

    /**
     * @brief Sends a packet to all connected clients.
     * 
     * Iterates through the list of clients and sends the provided packet to each one.
     * Logs an error for any client that fails to receive the packet.
     * 
     * @param packet The SFML packet to broadcast to all clients.
     */
    void sendAll(sf::Packet packet);

    /**
     * @brief Stops the server and closes all connections.
     * 
     * Sets the server's running status to false and closes the listener socket.
     */
    void stop();  

    /**
     * @brief Starts the server's main loop.
     * 
     * Begins listening for incoming connections and handles them in a separate thread.
     */
    void run();

    /**
     * @brief Accepts clients until the maximum number is reached or the timeout expires.
     * 
     * Manages incoming client connections, assigns unique IDs to each client,
     * and broadcasts a start game packet once all clients are connected.
     */
    void acceptingClients();

private:
    int port; /**< The port number the server listens on. */
    int nClients; /**< The maximum number of clients the server will manage. */
    int numConnections; /**< The current number of connected clients. */
    int timeout; /**< The timeout duration in seconds for accepting clients. */
    bool running; /**< Indicates whether the server is currently running. */
    bool inGame; /**< Indicates whether the game is in progress. */
    sf::TcpListener listener; /**< Listener socket to accept incoming client connections. */
    std::vector<std::shared_ptr<sf::TcpSocket>> clients; /**< List of client sockets connected to the server. */
};
