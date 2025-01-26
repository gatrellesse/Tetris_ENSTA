#include <memory>
#include <SFML/Graphics.hpp>
#pragma once
#include <iostream>
using namespace std;

class WindowManager
{
public:
    explicit WindowManager(int cell_size = 30, int window_w = 20, int window_h = 20);
    virtual ~WindowManager();
    virtual std::shared_ptr<sf::RenderWindow> getWindow() const;
    int LobbyWindow();
    int MatchWindow();
    int PauseWindow();
    int EndGameWindow(string gameMode, int numberOpponents, int numberGamesOver, bool gameFinished, std::vector<int> scores, std::vector<int> ranking);
    void resizeWindow(unsigned int newWidth, unsigned int newHeight);
    
protected:
    int cell_size;
    int window_w;//width
    int window_h;//height
    std::shared_ptr<sf::RenderWindow> window;

};

