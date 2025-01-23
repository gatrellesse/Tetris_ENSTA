#pragma once
#include <SFML/Graphics/Color.hpp>
#include <vector>

/**
 * @file colors.h
 * @brief Contains predefined color constants and a function to retrieve them.
 *
 * This header declares a set of predefined SFML color constants
 * and a function to retrieve these colors in a vector for use in Tetris.
 */

/**
 * @brief Represents a dark grey color.
 * 
 * Defined in `colors.cpp`.
 */
extern const sf::Color darkGrey;

/**
 * @brief Represents a green color.
 * 
 * Defined in `colors.cpp`.
 */
extern const sf::Color green;

/**
 * @brief Represents a red color.
 * 
 * Defined in `colors.cpp`.
 */
extern const sf::Color red;

/**
 * @brief Represents an orange color.
 * 
 * Defined in `colors.cpp`.
 */
extern const sf::Color orange;

/**
 * @brief Represents a yellow color.
 * 
 * Defined in `colors.cpp`.
 */
extern const sf::Color yellow;

/**
 * @brief Represents a purple color.
 * 
 * Defined in `colors.cpp`.
 */
extern const sf::Color purple;

/**
 * @brief Represents a cyan color.
 * 
 * Defined in `colors.cpp`.
 */
extern const sf::Color cyan;

/**
 * @brief Represents a blue color.
 * 
 * Defined in `colors.cpp`.
 */
extern const sf::Color blue;

/**
 * @brief Represents a light blue color.
 * 
 * Defined in `colors.cpp`.
 */
extern const sf::Color lightBlue;

/**
 * @brief Represents a dark blue color.
 * 
 * Defined in `colors.cpp`.
 */
extern const sf::Color darkBlue;

/**
 * @brief Represents a pink color.
 * 
 * Defined in `colors.cpp`.
 */
extern const sf::Color pink;

/**
 * @brief Retrieves a vector of predefined cell colors.
 *
 * This function provides a vector containing all the predefined colors
 * used for rendering the cells in the Tetris game.
 *
 * @return std::vector<sf::Color> A vector of colors.
 */
std::vector<sf::Color> GetCellColors();

