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
    void sendGameOver();
    void connect();
    void disconnect();
    void connectedLoop();
    void handlePacket(int type, sf::Packet& packet);
    void setGameOver();//single player purposes
    int getNumberOpponents() const;
    int getNumberGamesOver() const;
    bool isConnected();
    bool isGameStarted();
    bool isGameFinished();

private:
    sf::TcpSocket socket;
    int currentPort;
    string IP;
    int id;
    int gameWinner = 0;
    int nGamesOver;
    int nOpponents;
    int timeout;
    bool connected;
    bool gameStarted = false;
    bool gameFinished = false;

};
