#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;
#pragma once

class Server
{
public:
    Server(int portUser, int waitingFor);
    ~Server();
    void statusServer();
    void sendAll(sf::Packet packet);
    void stop();  
    void run();

private:
    int port;
    int nClients;
    int numConnections;
    bool running;
    sf::TcpListener listener;
    std::vector<std::shared_ptr<sf::TcpSocket>> clients;
    
};
