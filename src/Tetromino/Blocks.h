#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

/**
 * @typedef Matrix4x4
 * @brief Defines a 4x4 matrix representation for Tetris pieces.
 */
using Matrix4x4 = std::vector<std::vector<int>>;

/**
 * @class Blocks
 * @brief Manages the representation and drawing of Tetris pieces.
 */
class Blocks
{
public:
    /**
     * @brief Constructs a new Blocks instance.
     * 
     * @param cell_size The size of each cell in pixels.
     */
    Blocks(int cell_size);

    /**
     * @brief Destructor for the Blocks class.
     */
    ~Blocks();

    /**
     * @brief Draws a Tetris piece on the game window.
     * 
     * @param window Pointer to the SFML render window.
     * @param piece The 4x4 matrix representation of the piece to draw.
     * @param cx The x-coordinate of the piece's top-left corner in grid space.
     * @param cy The y-coordinate of the piece's top-left corner in grid space.
     */
    void draw_piece(sf::RenderWindow* window, Matrix4x4& piece, int cx, int cy);

    /**
     * @brief Draws a ghost representation of a Tetris piece on the game window.
     * 
     * @param window Pointer to the SFML render window.
     * @param piece The 4x4 matrix representation of the piece to draw.
     * @param cx The x-coordinate of the piece's top-left corner in grid space.
     * @param cy The y-coordinate of the piece's top-left corner in grid space.
     */
    void draw_Ghost_piece(sf::RenderWindow* window, Matrix4x4& piece, int cx, int cy);

    /**
     * @brief Retrieves a Tetris piece by its index.
     * 
     * @param idx The index of the piece to retrieve (0 for I, 1 for O, etc.).
     * @return A 4x4 matrix representing the Tetris piece.
     */
    Matrix4x4 getPiece(int idx) const;

private:
    int cell_size;
    std::vector<Matrix4x4> matrixPieces ;

};