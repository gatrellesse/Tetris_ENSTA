#ifndef GRID_H
#define GRID_H

#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Grid
{
public:
    explicit Grid(int cell_size = 30 , int rows = 20, int cols = 10);
    ~Grid();
    std::shared_ptr<sf::RenderWindow> getWindow() const;
    void draw_grid();
    std::vector<std::vector<unsigned char>>& getmatrixGrid();
    int getCell_size() const;
    int getCols_size() const;
    int getRows_size() const;
    void lineCleaning() ;

private:
    bool gameover = 0;
    int cell_size;
    int cols;
    int rows;
    std::vector<std::vector<unsigned char>> matrixGrid;
    std::shared_ptr<sf::RenderWindow> window;
    

};

#endif