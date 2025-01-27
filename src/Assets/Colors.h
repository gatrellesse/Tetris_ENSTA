#pragma once
#include <SFML/Graphics/Color.hpp>
#include <vector>
//extern serve pra falar q vai ser definido em outro lugar
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

std::vector<sf::Color> GetCellColors();

