#pragma once
#include <SFML/Graphics/Color.hpp>
#include <vector>


/**
 * @file Colors.h
 * @brief Provides a collection of color definitions and utility functions.
 */

extern const sf::Color darkGrey;
extern const sf::Color green;
extern const sf::Color red;
extern const sf::Color orange;
extern const sf::Color yellow;
extern const sf::Color purple;
extern const sf::Color cyan;
extern const sf::Color blue;
extern const sf::Color lightBlue;
extern const sf::Color darkBlue;
extern const sf::Color pink;

/**
 * @brief Retrieves a vector of cell colors used in the game.
 * @return A vector containing predefined SFML colors.
 */
std::vector<sf::Color> GetCellColors();

