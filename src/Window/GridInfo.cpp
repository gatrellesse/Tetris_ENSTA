#include "GridInfo.h"
#include <SFML/Graphics.hpp>
#include "Colors.h"
#include <iostream>
using namespace std;


/**
 * @class GridInfo
 * @brief Manages the informational grid for the Tetris game, including level, score, next piece display, and pause button.
 */

/**
 * @brief Constructs a new GridInfo instance.
 * 
 * @param parentWindow A shared pointer to the SFML render window.
 * @param rows The number of rows in the informational grid.
 * @param cols The number of columns in the informational grid.
 * @param rows_setOff Vertical offset for rendering the grid.
 * @param cols_setOff Horizontal offset for rendering the grid.
 * @param cell_size The size of each cell in pixels.
 */
GridInfo::GridInfo(std::shared_ptr<sf::RenderWindow> parentWindow, int rows, int cols, int rows_setOff, int cols_setOff, int cell_size)
    : WindowManager(), // Initialize the parent class her
      rows(rows), cols(cols), rows_setOff(rows_setOff),cols_setOff(cols_setOff) 
    {
        window = parentWindow;
        matrixGrid = std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(rows, 0));
        pauseButton.setSize(sf::Vector2f(cell_size * 2, cell_size));
        pauseButton.setFillColor(sf::Color(128, 128, 128, 255));
        pauseButton.setPosition(cell_size * 13, cell_size * 18);
        pauseButton.setOutlineThickness(1);
        pauseButton.setOutlineColor(sf::Color::White);
    }

/**
 * @brief Destructor for the GridInfo class.
 */
GridInfo::~GridInfo()
{
}

/**
 * @brief Renders the informational grid, including level, score, and pause button, on the game window.
 * 
 * @param currentLevel The current level of the game.
 * @param currentScore The current score of the player.
 */
void GridInfo::draw_grid(int currentLevel, int currentScore){
    for (int y = 0; y < rows; ++y){
            for (int x = 0; x < cols; ++x){
                sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                cell.setPosition((x + cols_setOff) * cell_size, (y + rows_setOff) * cell_size);
                if(matrixGrid[x][y]){
                    sf::Color color = GetCellColors()[matrixGrid[x][y] - 1];
                    cell.setFillColor(color);
                }
                else cell.setFillColor(sf::Color::Black);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);
                window->draw(cell);
            }
    }
    sf::Font font;
    if (!font.loadFromFile("src/Assets/arial.ttf")) {
        throw std::runtime_error("Failed to load font file");
    }
    sf::Texture texture;
    if (!texture.loadFromFile("src/Assets/infoScreen.png")) { // Replace with your image path
        std::cout << "Error loading image!" << std::endl;
    }

    // Create a sprite and set the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(cell_size * 10, 0); // Adjust position as needed
    window->draw(sprite);
    sf::Text level;
    // Background Score
    sf::RectangleShape scoreGrid(sf::Vector2f(cell_size*4, cell_size*2));
    scoreGrid.setFillColor(sf::Color(128, 128, 128, 255));
    scoreGrid.setPosition(cell_size * 13, cell_size*8); // Adjusted to the new screen
    scoreGrid.setOutlineThickness(20);
    scoreGrid.setOutlineColor(sf::Color(128, 128, 128, 30));
    window->draw(scoreGrid);
    //Level
    level.setFont(font);
    level.setString("Level: " + std::to_string(currentLevel));
    level.setCharacterSize(25); // in pixels, not points!
    level.setPosition(cell_size * 13, cell_size * 9);
    level.setFillColor(sf::Color::White);
    window->draw(level);
    //Score
    sf::Text score;
    score.setFont(font);
    score.setString("Score: " + std::to_string(currentScore));
    score.setCharacterSize(25); // in pixels, not points!
    score.setPosition(cell_size * 13, cell_size * 8);
    score.setFillColor(sf::Color::White);
    window->draw(score);
    //Pause Button
    sf::Text pauseText("Pause", font, 20);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(cell_size * 13, cell_size*18); // Adjusted to center on button
    window->draw(pauseButton);
    window->draw(pauseText);
    
}

/**
 * @brief Initializes the pause button with default size, color, and position.
 */
void GridInfo::initializePauseButton() {
    pauseButton.setSize(sf::Vector2f(cell_size * 2, cell_size));
    pauseButton.setFillColor(sf::Color(128, 128, 128, 255));
    pauseButton.setPosition(cell_size * 13, cell_size * 18);
    pauseButton.setOutlineThickness(1);
    pauseButton.setOutlineColor(sf::Color::White);
}

/**
 * @brief Retrieves the pause button for external interaction.
 * 
 * @return A reference to the pause button as a rectangle shape.
 */
sf::RectangleShape& GridInfo::getPauseButton() {
    return pauseButton;
}

/**
 * @brief Renders the next Tetris piece on the informational grid.
 * 
 * @param nextPiece A 4x4 matrix representing the next Tetris piece.
 */
void GridInfo::draw_nextPiece(Matrix4x4 nextPiece){
    for (int y = 0; y < 4; ++y){
            for (int x = 0; x < 4; ++x){
                sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                cell.setPosition((x + 13) * cell_size, (y + 3) * cell_size);
                if(nextPiece[x][y]){
                    sf::Color color = GetCellColors()[nextPiece[x][y] - 1];
                    cell.setFillColor(color);
                    cell.setOutlineThickness(1);
                    cell.setOutlineColor(sf::Color::Black);
                }
                else {  
                    cell.setFillColor(sf::Color::White);
                    cell.setOutlineThickness(1);
                    cell.setOutlineColor(sf::Color::White);
                }
                window->draw(cell);
            }
    }
}


