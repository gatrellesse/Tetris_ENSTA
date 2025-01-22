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
    bool connected;
    bool gameStarted = false;
    bool gameFinished = false;
    int gameWinner = 0;
};
