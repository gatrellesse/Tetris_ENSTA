#pragma once
#include <vector>
#include <memory>
#include "WindowManager.h"
#include <SFML/Graphics.hpp>

class Grid: public WindowManager
{
public:
    explicit Grid(std::shared_ptr<sf::RenderWindow> parentWindow, int rows = 20, int cols = 10,  int rows_setOff = 0, int cols_setOff = 0, int cell_size = 30);
    virtual ~Grid();
    virtual void draw_grid();
    std::vector<std::vector<unsigned char>>& getmatrixGrid();
    void restartValues();
    int getCell_size() const;
    int getCols_size() const;
    int getRows_size() const;
    void lineCleaning() ;

private:
    bool gameover = 0;
    int rows;
    int rows_setOff;
    int cols;
    int cols_setOff;
    std::vector<std::vector<unsigned char>> matrixGrid;
    

};