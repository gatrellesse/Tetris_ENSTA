#include "Score.h"

/**
 * @brief Constructs a Score object.
 * 
 * Initializes the game level, total points, and speed factor to their default values.
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
 * @brief Calculates the points based on the number of lines cleaned.
 * 
 * Updates the total points and level of the player. Adjusts the speed factor
 * for faster piece drops as the level increases.
 * 
 * @param nLinesCleaned The number of lines cleared in a single move.
 */
void Score::calculatePoints(int nLinesCleaned){
    int p = 0; // New points
    if(nLinesCleaned == 1) p = 40;
    else if (nLinesCleaned == 2) p = 100;
    else if (nLinesCleaned == 3) p = 300;
    else if (nLinesCleaned == 4) p = 1200;
    
    totalPoints += p * (level + 1);  // Multiply points by the current level + 1
    if (p != 0) level += 1; // Increment level if points were added

    // Adjust speed factor based on the level
    if (level > 2 && level < 15) speedFactor = 0.6;
    else if (level >= 15) speedFactor = 0.4;

};

/**
 * @brief Retrieves the current speed factor.
 * 
 * The speed factor determines the delay between piece drops, where smaller
 * values indicate faster drops.
 * 
 * @return float The current speed factor.
 */
float Score::getSpeedFactor() const{
    return speedFactor;
}

/**
 * @brief Retrieves the player's current score.
 * 
 * @return int The total points accumulated by the player.
 */
int Score::getScore() const{
    return totalPoints;
}

/**
 * @brief Retrieves the player's current level.
 * 
 * @return int The current game level.
 */
int Score::getLevel() const{
    return level;
}