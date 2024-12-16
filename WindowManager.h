#include <memory>
#include <SFML/Graphics.hpp>
#pragma once

class WindowManager
{
public:
    explicit WindowManager(int cell_size = 30, int window_w = 20, int window_h = 20);
    virtual ~WindowManager();
    virtual std::shared_ptr<sf::RenderWindow> getWindow() const;
    
protected:
    int cell_size;
    int window_w;//width
    int window_h;//height
    std::shared_ptr<sf::RenderWindow> window;

};

