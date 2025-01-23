#pragma once

/**
 * @class Score
 * @brief Manages the scoring, level progression, and speed adjustments for the Tetris game.
 *
 * The Score class tracks the player's current level, total points, and adjusts the game speed
 * based on the player's progression.
 */
class Score
{
public:
    /**
     * @brief Constructs a Score object.
     * 
     * Initializes the level, total points, and speed factor to their default values.
     */
    explicit Score();

    /**
     * @brief Destructor for the Score class.
     */
    ~Score();

    /**
     * @brief Calculates points based on the number of lines cleaned.
     * 
     * Updates the player's total points and level. Adjusts the speed factor based on the level
     * for increased difficulty as the game progresses.
     * 
     * @param nLinesCleaned The number of lines cleared in a single move.
     */
    void calculatePoints(int nLinesCleaned);

    /**
     * @brief Retrieves the current speed factor.
     * 
     * The speed factor determines the delay between piece drops. Lower values
     * represent faster drops, making the game more challenging at higher levels.
     * 
     * @return float The current speed factor.
     */
    float getSpeedFactor () const;

    /**
     * @brief Retrieves the player's current score.
     * 
     * @return int The total points accumulated by the player.
     */
    int getScore () const;

    /**
     * @brief Retrieves the player's current level.
     * 
     * @return int The current game level.
     */
    int getLevel() const;

private:
    int level; /**< The player's current game level. */
    int totalPoints; /**< The total points accumulated by the player. */
    float speedFactor; /**< The factor controlling the game's speed (lower is faster). */
};
