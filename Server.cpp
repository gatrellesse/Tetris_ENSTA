#include "Server.h"
#include <chrono>

Server::Server(int portUser, int waitingfor):
        port(portUser), nClients(waitingfor){
    clients.resize(nClients); // Resize the vector to hold `nClients` entries
    running = false;
    numConnections = 0;
    cout << "Server instance created" << endl;
}

Server::~Server()
{
    stop();
}


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

void Server::run() {
    running = true;
    auto startTime = std::chrono::steady_clock::now();

    if (listener.listen(port) != sf::Socket::Done) {
        std::cout << "Failed to start server." << std::endl;
        running = false;
        return;
    }

    std::cout << "Server listening on port " << port << std::endl;

    while (running) {
        auto elapsed = std::chrono::steady_clock::now() - startTime;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() > 60) {
            std::cout << "Server timed out after 15 seconds." << std::endl;
            stop();
            break;
        }

        if (numConnections >= nClients) {
            running = false;
            continue;
        }

        auto socket = std::make_shared<sf::TcpSocket>();
        if (listener.accept(*socket) == sf::Socket::Done) {
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


void Server::sendAll(sf::Packet packet) {
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i]) {
            if (clients[i]->send(packet) != sf::Socket::Done) {
                std::cout << "Failed to send message to client " << i + 1 << std::endl;
            }
        }
    }
}

void Server::stop() {
    running = false;
    // for (auto& client : clients) {
    //     if (client) {
    //         client->disconnect();
    //     }
    // }
    // clients.clear();
    listener.close();
    std::cout << "Server stopped." << std::endl;
}
