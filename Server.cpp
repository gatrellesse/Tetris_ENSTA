#include "Server.h"
#include "PacketsMap.cpp"
#include <thread>
#include <functional> //for bind
#include <chrono>

Server::Server(int portUser, int waitingfor):
        port(portUser), nClients(waitingfor){
    clients.resize(nClients); // Resize the vector to hold `nClients` entries
    running = false;
    inGame = true;
    gamesOver = new std::vector<bool>(nClients, false);
    scores = new std::vector<int>(nClients, 0);
    ranking = new std::vector<int>(nClients, 0);
    nGamesOver =0;
    numConnections = 0;
    timeout = 60;
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

    if (listener.listen(port) != sf::Socket::Done) {
        std::cout << "Failed to start server." << std::endl;
        running = false;
        return;
    }

    std::cout << "Server listening on port " << port << std::endl;
    std::thread clientsThread(&Server::acceptingClients, this);
    clientsThread.detach(); // Detach the thread to run independently

}

void Server::acceptingClients() {
    auto startTime = std::chrono::steady_clock::now();
    std::vector<std::thread> clientThreads;  // Store threads for later joining

    while (running) {
        auto elapsed = std::chrono::steady_clock::now() - startTime;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() > timeout) {
            std::cout << "Server timed out after " << timeout << " seconds." << std::endl;
            stop();
            break;
        }

        if (numConnections >= nClients) {
            startGame();
            break;
        }

        auto socket = std::make_shared<sf::TcpSocket>();
        if (listener.accept(*socket) == sf::Socket::Done) {
            std::cout << "Client connected!" << std::endl;
            clients[numConnections] = socket;

            // 1 packet is the ID (keep before detach)
            sf::Packet idPacket;
            idPacket << numConnections;
            socket->send(idPacket);

            // 2 packet is the number of opponents
            sf::Packet nOpponentsPacket;
            nOpponentsPacket << nClients;
            socket->send(nOpponentsPacket);

            // Start handling this client in a new thread
            clientThreads.push_back(std::thread(std::bind(&Server::handleClient, this, socket, numConnections)));
        

            numConnections++;
        }
    }

    std::cout << "Server stopped looking for players." << std::endl;

    // Wait for all client handling threads to finish
    for (auto& clientThread : clientThreads) {
        if (clientThread.joinable()) {
            clientThread.join();
        }
    }
}

void Server::handleClient(std::shared_ptr<sf::TcpSocket>& socket, int clientID) {
    while (running) {
        sf::Packet dataPack;
        if (socket->receive(dataPack) == sf::Socket::Done) {
            // Process the packet
            int type;
            dataPack >> type;
            std::cout << "Received packet type: " << type << " from client " << clientID << std::endl;
            handlePacket(type, dataPack, clientID);
        } else {
            // Handle client disconnect or connection issue
            std::cout << "Client " << clientID << " has connection issues." << std::endl;

            // Lock the mutex to safely access and modify `clients`
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                if (clients[clientID]) {
                    clients[clientID]->disconnect();
                    clients[clientID] = nullptr;
                }
            }

            numConnections--;
            (*gamesOver)[clientID] = true;
            break;
        }
    }
}


void Server::getWinner(){
    for(int i = 0; i < nClients; i++){
        int scoreMax = -1;
        int idMax = 0;
        for(int j = i; j < nClients; j++ ){
            if ((*scores)[i] > scoreMax) {
                scoreMax = (*scores)[i];
                idMax = j;
            }
        }
        (*ranking)[i] = idMax;
    }
    std::sort(scores->begin(), scores->end()); 
}

void Server::handlePacket(int type, sf::Packet& packet, int clientID) {
     switch (type) {
        case PACKET_TYPE_GRID:{
            //Resend the new grid of this client for all clients with clientID attached
            //which means, the serves only repass it
            
            sendAllExcept(packet, clientID);
            break;
        }
        case PACKET_TYPE_GAMEOVER:{ // Handle game over
            (*gamesOver)[clientID] = true;
            nGamesOver++;
            sf::Packet gameOverCounting;
            gameOverCounting << (int)PACKET_TYPE_GAMEOVER;
            sendAll(gameOverCounting);
            if(nGamesOver == nClients){//Last gamerover packet is the winner
                sf::Packet gameEndPacket;
                gameEndPacket << (int)PACKET_TYPE_FINISHGAME;
                getWinner();
                for(int i = 0; i < nClients; i++){
                    gameEndPacket << (*ranking)[i] << (*scores)[i];
                }
                sendAll(gameEndPacket);
                break;
                
            }
            break;
        }
        case PACKET_TYPE_SCORE:{
            int score;
            packet >> score;
            (*scores)[clientID] = score;
            sf::Packet scoreRegistredPack;
            scoreRegistredPack <<(int)PACKET_TYPE_SCORE;
            clients[clientID]->send(scoreRegistredPack);
            break;
        }
        default:
           std::cout << "Unknown packet type received: " << type << std::endl;
     }
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

void Server::sendAllExcept(sf::Packet packet, int id) {
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i] != NULL && i != id) {
            if (clients[i]->send(packet) != sf::Socket::Done) {
                std::cout << "Failed to send message to client " << i + 1 << std::endl;
            }
        }
    }
}


void Server::startGame(){
    sf::Packet gameStartPacket;
    gameStartPacket << (int)PACKET_TYPE_START;
    sendAll(gameStartPacket);
    inGame = true;
}

void Server::stop() {
    running = false;
    std::cout << "Disconnecting clients from server..." << std::endl;

    // Lock the mutex to ensure thread-safe access to clients
    {
        std::lock_guard<std::mutex> lock(clientsMutex);
        for (auto& client : clients) {
            if (client) {
                client->disconnect();
                client = nullptr;
            }
        }

        // Make sure to clear the vector after disconnecting clients
        clients.clear();
    }

    std::cout << "Clients disconnected from server." << std::endl;
    delete scores; scores = nullptr;
    delete ranking; ranking = nullptr;
    delete gamesOver; gamesOver = nullptr;
    std::cout << "Stopping server..." << std::endl;
    listener.close();
    nClients = 0;
    std::cout << "Server stopped." << std::endl;
}
