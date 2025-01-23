#include "Client.h"
#include "PacketsMap.cpp"
#include <chrono>
#include <thread>

/**
 * @brief Constructs a Client object.
 * 
 * Initializes the client instance with the provided port and IP address. Sets default values for connection status and timeout.
 * 
 * @param myPort The port number to connect to.
 * @param myIP The IP address of the server.
 */
Client::Client(int myPort, string myIP): IP(myIP), currentPort(myPort)
{
    connected = false; /**< Initial connection status is set to false. */
    timeout = 60; /**< Default timeout duration in seconds. */
    cout<<"Client instance created" << endl;
}

/**
 * @brief Destructor for the Client class.
 */
Client::~Client()
{

}

/**
 * @brief Attempts to connect the client to the server.
 * 
 * Continuously tries to connect to the server until either the connection is successful
 * or the timeout period elapses. Once connected, starts a separate thread to handle network communication.
 */
void Client::connect(){
    auto startTime = std::chrono::steady_clock::now();
    while(!connected){
        auto elapsed = std::chrono::steady_clock::now() - startTime;
        if(socket.connect(IP, currentPort) != sf::Socket::Done){
            cout << "Client failed to connect to server-->Retrying" << endl;
        }
        else{
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

    // Start the network communication thread
    // This allows the client to keep receiving and sending data
    //    without pertubating the thread of the game per say
    std::thread dataPacketsThread(&Client::connectedLoop, this);
    dataPacketsThread.detach(); /**< Detach the thread to run independently. */

}

/**
 * @brief The main loop for handling server communication.
 * 
 * Continuously receives packets from the server and processes them. If an error occurs during communication,
 * the connection is terminated.
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
        handlePacket(type, dataPack); /**< Handles the packet based on its type. */
    }
}

/**
 * @brief Handles incoming packets from the server.
 * 
 * Processes the packet based on its type, performing the appropriate action for each type.
 * 
 * @param type The type of the packet (e.g., start, lobby, etc.).
 * @param packet The packet received from the server.
 */
void Client::handlePacket(int type, sf::Packet& packet) {
     switch (type) {
    //     case PACKET_TYPE_LOBBY:
    //         // Handle lobby packet
    //         break;
        case PACKET_TYPE_START:
            // Handle game start packet
            gameStarted = true;
            break;
    //     case PACKET_TYPE_WORLD:
    //         // Handle world update
    //         break;
    //     case PACKET_TYPE_PIECE:
    //         // Handle piece update
    //         break;
    //     case PACKET_TYPE_BLOCK:
    //         // Handle block addition
    //         break;
    //     case PACKET_TYPE_GAMEOVER:
    //         // Handle game over
    //         break;
    //     case PACKET_TYPE_FINISHGAME:
    //         // Handle game finish
    //         break;
        default:
            std::cout << "Unknown packet type received: " << type << std::endl;
    }
}

/**
 * @brief Sends a message (packet) to the server.
 * 
 * Attempts to send the provided packet to the server. Logs an error if the send operation fails.
 * 
 * @param packet The packet to send to the server.
 */
void Client::sendMessage(sf::Packet packet){
    if(socket.send(packet) != sf::Socket::Done){
        cout << "Failed to send pack from client " << endl;
    }
}

/**
 * @brief Checks if the client is connected to the server.
 * 
 * @return bool Returns `true` if the client is connected, otherwise `false`.
 */
bool Client::isConnected(){
    return connected;
}

/**
 * @brief Checks if the game has started.
 * 
 * @return bool Returns `true` if the game has started, otherwise `false`.
 */
bool Client::isGameStarted(){
    return gameStarted;
}