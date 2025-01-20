#include "colors.h"
#include <SFML/Graphics.hpp> 

// Define colors using the correct sf::Color constructor
const sf::Color darkGrey(26, 31, 40, 255);
const sf::Color green(47, 230, 23, 255);
const sf::Color red(232, 18, 18, 255);
const sf::Color orange(226, 116, 17, 255);
const sf::Color yellow(237, 234, 4, 255);
const sf::Color purple(166, 0, 247, 255);
const sf::Color cyan(21, 204, 209, 255);
const sf::Color blue(13, 64, 216, 255);
const sf::Color lightBlue(59, 85, 162, 255);
const sf::Color darkBlue(44, 44, 127, 255);
const sf::Color pink(255, 105, 180, 255);  // RGB values for pink


// Function to return a vector of the defined colors
std::vector<sf::Color> GetCellColors()
{
    return {blue, green, red, orange, yellow, purple, pink};
}

