#pragma once

/**
 * @class Score
 * @brief Manages the player's score, level progression, and game speed adjustments.
 */
class Score
{
public:
    /**
     * @brief Constructs a new Score instance.
     * 
     * Initializes the level, total points, and speed factor to their default values.
     */
    explicit Score();

    /**
     * @brief Destructor for the Score class.
     */
    ~Score();

    /**
     * @brief Calculates the player's points based on the number of lines cleared.
     * 
     * Updates the total points, adjusts the level, and modifies the speed factor dynamically.
     * 
     * @param nLinesCleaned The number of lines cleared in a single move.
     */
    void calculatePoints(int nLinesCleaned);

    /**
     * @brief Retrieves the current speed factor of the game.
     * 
     * The speed factor determines how fast pieces fall, based on the player's level.
     * 
     * @return The current speed factor.
     */
    float getSpeedFactor () const;
    
    /**
     * @brief Retrieves the player's total score.
     * 
     * @return The total points earned by the player.
     */
    int getScore () const;

    /**
     * @brief Retrieves the player's current level.
     * 
     * @return The current level of the player.
     */
    int getLevel() const;

private:
    int level;  /**< The player's current level. */
    int totalPoints; /**< The player's total points. */
    float speedFactor; /**< The speed factor determining the fall speed of pieces. */
};
