#include "Score.h"

/**
 * @class Score
 * @brief Manages the player's score, level, and speed factor in the game.
 */

/**
 * @brief Constructs a new Score instance.
 * 
 * Initializes the level, total points, and speed factor to their default values.
 */
Score::Score()
{
    level = 0;
    totalPoints = 0;
    speedFactor = 1.0;
}

/**
 * @brief Destructor for the Score class.
 */
Score::~Score()
{

}

/**
 * @brief Calculates the player's points based on the number of lines cleaned.
 * 
 * Updates the total points and adjusts the level and speed factor accordingly.
 * 
 * @param nLinesCleaned The number of lines cleaned in a single move.
 */
void Score::calculatePoints(int nLinesCleaned){
    int p = 0; //new points
    if(nLinesCleaned == 1) p = 40;
    else if (nLinesCleaned == 2) p = 100;
    else if (nLinesCleaned == 3) p = 300;
    else if (nLinesCleaned == 4) p = 1200;
    
    totalPoints += p * (level + 1);
    if (p != 0) level += 1;
    if (level > 2 && level < 15) speedFactor = 0.5;
    else if (level >= 15) speedFactor = 0.25;

};

/**
 * @brief Retrieves the current speed factor of the game.
 * 
 * The speed factor determines how fast the pieces fall based on the player's level.
 * 
 * @return The current speed factor.
 */
float Score::getSpeedFactor() const{
    return speedFactor;
}

/**
 * @brief Retrieves the player's total score.
 * 
 * @return The total points earned by the player.
 */
int Score::getScore() const{
    return totalPoints;
}

/**
 * @brief Retrieves the player's current level.
 * 
 * @return The current level of the player.
 */
int Score::getLevel() const{
    return level;
}