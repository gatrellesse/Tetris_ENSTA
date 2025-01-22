#include <SFML/Network.hpp>
#include <iostream>
using namespace std;
#pragma once

class Client
{
public:
    Client(int myPort, string myIP);
    ~Client(); 
    void receiveMessage();
    int searchServer();
private:
    sf::TcpSocket socket;
    int currentPort;
    string IP;
};
