#pragma once
#include "WindowManager.h" 

class GridInfo: public WindowManager
{
public:
    explicit GridInfo(std::shared_ptr<sf::RenderWindow> parentWindow, int rows = 20, 
                int cols = 10, int rows_setOff = 0, int cols_setOff = 11, int cell_size = 30);
    ~GridInfo();
    void draw_grid();

private:
    int rows;
    int rows_setOff;
    int cols;
    int cols_setOff;
    std::vector<std::vector<unsigned char>> matrixGrid;
};