#include "Client.h"
#include "PacketsMap.cpp"
#include <chrono>
#include <thread>

Client::Client(int myPort, string myIP): IP(myIP), currentPort(myPort)
{
    connected = false;
    timeout = 60;
    cout<<"Client instance created" << endl;
}

Client::~Client()
{

}
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
    dataPacketsThread.detach(); // Detach the thread to run independently

}

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

void Client::sendMessage(sf::Packet packet){
    if(socket.send(packet) != sf::Socket::Done){
        cout << "Failed to send pack from client " << endl;
    }
}

bool Client::isConnected(){
    return connected;
}

bool Client::isGameStarted(){
    return gameStarted;
}