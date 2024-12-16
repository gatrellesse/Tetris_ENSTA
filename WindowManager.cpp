#include "WindowManager.h"

WindowManager::WindowManager(int cell_size, int window_w, int window_h):
    cell_size(cell_size), window_w(window_w), window_h(window_h)
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(cell_size * window_w, cell_size * window_h), "TrelleTetris");
}

WindowManager::~WindowManager()
{
}

std::shared_ptr<sf::RenderWindow> WindowManager::getWindow() const {
    return window;
}