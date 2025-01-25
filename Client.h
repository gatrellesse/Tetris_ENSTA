#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>  // Ensure this is included to use sf::RenderWindow
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
    void sendGrid(const std::vector<std::tuple<int, int, unsigned char>>& changedCells);
    void connect();
    void disconnect();
    void connectedLoop();
    void handlePacket(int type, sf::Packet& packet);
    void setGameOver();//single player purposes
    void drawEnemies(sf::RenderWindow *window);
    int getNumberOpponents() const;
    int getNumberGamesOver() const;
    int getID() const;
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
    std::vector<std::vector<std::vector<unsigned char>>> gridCollection;


};
