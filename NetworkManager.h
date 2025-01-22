#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;
#pragma once

class NetworkManager
{
public:
    NetworkManager(int portUser, int waitingFor);
    ~NetworkManager();
    int statusServer();
    int connectClients(string serverIP);
    void sendMessage();
     // Deleted copy constructor and assignment operator

private:
    int port;
    int nClients;
    sf::TcpListener listener;
    std::vector<std::unique_ptr<sf::TcpSocket>> clients; 
    
};
