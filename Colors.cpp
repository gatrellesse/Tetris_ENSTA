#include "colors.h"
#include <SFML/Graphics.hpp> 

// Define colors using the correct sf::Color constructor

/**
 * @brief Represents a dark grey color.
 */
const sf::Color darkGrey(26, 31, 40, 255);

/**
 * @brief Represents a green color.
 */
const sf::Color green(47, 230, 23, 255);

/**
 * @brief Represents a red color.
 */
const sf::Color red(232, 18, 18, 255);

/**
 * @brief Represents an orange color.
 */
const sf::Color orange(226, 116, 17, 255);

/**
 * @brief Represents a yellow color.
 */
const sf::Color yellow(237, 234, 4, 255);

/**
 * @brief Represents a purple color.
 */
const sf::Color purple(166, 0, 247, 255);

/**
 * @brief Represents a cyan color.
 */
const sf::Color cyan(21, 204, 209, 255);

/**
 * @brief Represents a blue color.
 */
const sf::Color blue(13, 64, 216, 255);

/**
 * @brief Represents a light blue color.
 */
const sf::Color lightBlue(59, 85, 162, 255);

/**
 * @brief Represents a dark blue color.
 */
const sf::Color darkBlue(44, 44, 127, 255);

/**
 * @brief Represents a pink color.
 */
const sf::Color pink(255, 105, 180, 255);  // RGB values for pink

/**
 * @brief Retrieves a vector of predefined cell colors.
 *
 * This function returns a vector containing the predefined colors
 * used for rendering Tetris pieces on the grid.
 *
 * @return std::vector<sf::Color> A vector containing the predefined colors.
 */
std::vector<sf::Color> GetCellColors()
{
    return {blue, green, red, orange, yellow, purple, pink};
}

