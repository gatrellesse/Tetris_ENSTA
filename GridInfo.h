#pragma once
#include "WindowManager.h" 
using Matrix4x4 = std::vector<std::vector<int>>;

class GridInfo: public WindowManager
{
public:
    explicit GridInfo(std::shared_ptr<sf::RenderWindow> parentWindow, int rows = 20, 
                int cols = 10, int rows_setOff = 0, int cols_setOff = 11, int cell_size = 30);
    ~GridInfo();
    void draw_grid(int level, int score);
    void draw_nextPiece(Matrix4x4 nextPiece);

private:
    int rows;
    int rows_setOff;
    int cols;
    int cols_setOff;
    std::vector<std::vector<unsigned char>> matrixGrid;
};