#ifndef GRID_H
#define GRID_H

#pragma once

class Grid
{
public:
    Grid();
    ~Grid();

private:
    const int cell_size = 30;
    const int cols = 10;
    const int rows = 20;

};

#endif