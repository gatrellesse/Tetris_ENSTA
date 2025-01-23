#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

/**
 * @typedef Matrix4x4
 * @brief Defines a 4x4 matrix used to represent Tetris pieces.
 */
using Matrix4x4 = std::vector<std::vector<int>>;

/**
 * @class Blocks
 * @brief Manages Tetris pieces, including their shapes, rendering, and ghost pieces.
 *
 * The Blocks class defines the shapes of Tetris pieces as 4x4 matrices, provides
 * methods to render the pieces on the game board, and supports ghost pieces to
 * help players visualize where a piece will land.
 */
class Blocks
{
public:
    /**
     * @brief Constructs a Blocks object with a given cell size.
     * @param cell_size The size of each cell in pixels.
     */
    Blocks(int cell_size);

    /**
     * @brief Destructor for the Blocks class.
     */
    ~Blocks();

    /**
     * @brief Draws a Tetris piece on the game window.
     * @param window Pointer to the SFML render window.
     * @param piece A 4x4 matrix representing the piece.
     * @param cx The X-coordinate offset on the board.
     * @param cy The Y-coordinate offset on the board.
     */
    void draw_piece(sf::RenderWindow* window, Matrix4x4& piece, int cx, int cy);

    /**
     * @brief Draws a ghost version of a Tetris piece.
     *
     * A ghost piece is a translucent version of the Tetris piece that
     * shows where the piece will land on the board.
     *
     * @param window Pointer to the SFML render window.
     * @param piece A 4x4 matrix representing the piece.
     * @param cx The X-coordinate offset on the board.
     * @param cy The Y-coordinate offset on the board.
     */
    void draw_Ghost_piece(sf::RenderWindow* window, Matrix4x4& piece, int cx, int cy);

    /**
     * @brief Retrieves the matrix representation of a specific Tetris piece.
     * @param idx The index of the piece (0 for I, 1 for O, etc.).
     * @return Matrix4x4 The 4x4 matrix representing the piece.
     */
    Matrix4x4 getPiece(int idx) const;

private:
    int cell_size; /**< The size of each cell in pixels. */
    std::vector<Matrix4x4> matrixPieces ; /**< Stores the predefined matrices for Tetris pieces. */

};