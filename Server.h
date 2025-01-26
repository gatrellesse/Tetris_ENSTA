
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <mutex>
#include <functional>
using namespace std;
#pragma once

class Server
{
public:
    Server(int portUser, int waitingFor);
    ~Server();
    void sendAll(sf::Packet packet);
    void sendAllExcept(sf::Packet packet, int id);
    void stop();  
    void run();
    void startGame();
    void acceptingClients();
    void handleClient(std::shared_ptr<sf::TcpSocket>& socket, int clientID);
    void handlePacket(int type, sf::Packet& packet, int clientID);

private:
    int port;
    int nClients;
    int numConnections;
    int timeout;
    bool running;
    bool inGame;
    sf::TcpListener listener;
    std::vector<std::shared_ptr<sf::TcpSocket>> clients;
    std::mutex clientsMutex;
    void getWinner();
    int nGamesOver;
    int winner;
    std::vector<bool>* gamesOver;
    std::vector<int>* scores;
    std::vector<int>* ranking;
    
};
