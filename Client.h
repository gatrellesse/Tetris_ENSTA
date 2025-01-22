#include <SFML/Network.hpp>
#include <iostream>
using namespace std;
#pragma once

class Client
{
public:
    Client(int myPort, string myIP);
    ~Client(); 
    void sendMessage(sf::Packet packet);
    void connect();
    void connectedLoop();
    void handlePacket(int type, sf::Packet& packet);
    bool isConnected();
    bool isGameStarted();

private:
    sf::TcpSocket socket;
    int currentPort;
    string IP;
    int id;
    int gameWinner = 0;
    int timeout;
    bool connected;
    bool gameStarted = false;
    bool gameFinished = false;

};
