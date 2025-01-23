#include "Server.h"
#include "PacketsMap.cpp"
#include <thread>
#include <chrono>

/**
 * @brief Constructs a Server object.
 * 
 * Initializes the server with the specified port and the number of clients to wait for.
 * Sets up default values for state variables like `running`, `inGame`, and `numConnections`.
 * 
 * @param portUser The port number the server will listen on.
 * @param waitingfor The number of clients the server will manage.
 */
Server::Server(int portUser, int waitingfor):
        port(portUser), nClients(waitingfor){
    clients.resize(nClients);  /**< Resize the clients vector to hold `nClients` entries. */
    running = false; /**< Server is not running initially. */
    inGame = true; /**< Default game state is set to `inGame`. */
    numConnections = 0; /**< Number of currently connected clients. */
    timeout = 60; /**< Timeout duration in seconds. */
    cout << "Server instance created" << endl;
}

/**
 * @brief Destructor for the Server class.
 * 
 * Calls the `stop` function to ensure the server is properly shut down.
 */
Server::~Server()
{
    stop();
}

/**
 * @brief Binds the server listener to the specified port.
 * 
 * Sets the `running` flag to true if successful, or logs an error if the binding fails.
 */
void Server::statusServer(){
    sf::Socket::Status status = listener.listen(port);
    if (status != sf::Socket::Done) {
        std::cout << "Error binding the listener to the port" << std::endl;
        running = false;
    }
    else{
        running = true;
        cout << "Server is listening on port:" << port << endl; ; 
    }
}

/**
 * @brief Starts the server and begins listening for clients.
 * 
 * Spawns a separate thread to handle client connections asynchronously.
 * Logs an error if the server fails to start.
 */
void Server::run() {
    running = true;

    if (listener.listen(port) != sf::Socket::Done) {
        std::cout << "Failed to start server." << std::endl;
        running = false;
        return;
    }

    std::cout << "Server listening on port " << port << std::endl;
    std::thread clientsThread(&Server::acceptingClients, this); /**< Spawn a thread to accept clients. */
    clientsThread.detach(); /**< Detach the thread to allow it to run independently. */

}

/**
 * @brief Accepts clients until the maximum number is reached or the timeout expires.
 * 
 * Sends a start game packet to all clients once the required number of connections is achieved.
 */
void Server::acceptingClients(){
    auto startTime = std::chrono::steady_clock::now();
    while (running) {
        auto elapsed = std::chrono::steady_clock::now() - startTime;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() > timeout) {
            std::cout << "Server timed out after " << timeout << " seconds." << std::endl;
            stop();
            break;
        }

        if (numConnections >= nClients) { // All clients are connected
            sf::Packet gameStartPacket;
            gameStartPacket << (int)PACKET_TYPE_START;/**< Packet type for starting the game. */
            sendAll(gameStartPacket);
            inGame = true;
            running = false;
            continue;
        }

        auto socket = std::make_shared<sf::TcpSocket>();
        if (listener.accept(*socket) == sf::Socket::Done) { // Accept a new client connection
            std::cout << "Client connected!" << std::endl;
            clients[numConnections] = socket;

            // 1 packet is the ID
            sf::Packet idPacket;
            idPacket << numConnections;
            socket->send(idPacket);
            numConnections++;
        }
    }
    std::cout << "Server stoppedd looking player" << std::endl;
}

/**
 * @brief Sends a packet to all connected clients.
 * 
 * Iterates through the `clients` vector and sends the provided packet to each client.
 * Logs an error if sending fails for any client.
 * 
 * @param packet The packet to send to all clients.
 */
void Server::sendAll(sf::Packet packet) {
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i]) {
            if (clients[i]->send(packet) != sf::Socket::Done) {
                std::cout << "Failed to send message to client " << i + 1 << std::endl;
            }
        }
    }
}

/**
 * @brief Stops the server and closes all client connections.
 * 
 * Sets the `running` flag to false and closes the server listener.
 */
void Server::stop() {
    running = false;
    // for (auto& client : clients) {
    //     if (client) {
    //         client->disconnect();
    //     }
    // }
    // clients.clear();
    listener.close(); /**< Close the listener socket. */
    std::cout << "Server stopped." << std::endl;
}
