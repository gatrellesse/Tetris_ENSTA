#include <memory>
#include <SFML/Graphics.hpp>
#pragma once
#include <iostream>
using namespace std;

/**
 * @class WindowManager
 * @brief Manages the main game window and user interface elements such as menus and buttons.
 */
class WindowManager
{
public:
    /**
     * @brief Constructs a new WindowManager instance.
     * 
     * @param cell_size The size of each cell in pixels (default is 30).
     * @param window_w The width of the window in cells (default is 20).
     * @param window_h The height of the window in cells (default is 20).
     */
    explicit WindowManager(int cell_size = 30, int window_w = 20, int window_h = 20);

    /**
     * @brief Destructor for the WindowManager class.
     */
    virtual ~WindowManager();

    /**
     * @brief Retrieves the main game window.
     * 
     * @return A shared pointer to the SFML render window.
     */
    virtual std::shared_ptr<sf::RenderWindow> getWindow() const;

    /**
     * @brief Displays the lobby menu and handles user interactions.
     * 
     * Allows the user to start a game, join a match, or exit the application.
     * 
     * @return An integer indicating the user's choice:
     * - 1: Start game.
     * - 2: Join a match.
     * - 0: Exit the application.
     */
    int LobbyWindow();

    /**
     * @brief Displays the "Match" menu for multiplayer setup.
     * 
     * Allows the user to create a server, find a server, or return to the lobby.
     * 
     * @return An integer indicating the user's choice:
     * - 1: Create server.
     * - 0: Find server.
     * - 2: Return to the lobby.
     */
    int MatchWindow();

    /**
     * @brief Displays the pause menu and handles user interactions.
     * 
     * Provides options to continue the game, restart, return to the lobby, or exit the application.
     * 
     * @return An integer indicating the user's choice:
     * - 1: Continue the game.
     * - 2: Restart the game.
     * - 3: Return to the lobby.
     * - 0: Exit the application.
     */
    int PauseWindow();

    /**
     * @brief Displays the endgame menu and handles user interactions.
     * 
     * Provides options to restart the game, return to the lobby, or exit the application. 
     * Also displays the scores and rankings of players in a multiplayer match.
     * 
     * @param gameMode The current game mode (e.g., "Single", "Match").
     * @param numberOpponents The total number of opponents in the game.
     * @param numberGamesOver The number of players who have finished the game.
     * @param gameFinished Indicates whether the game has ended.
     * @param scores A vector containing the scores of all players.
     * @param ranking A vector containing the rankings of all players.
     * 
     * @return An integer indicating the user's choice:
     * - 1: Restart game.
     * - 2: Return to the lobby.
     * - 0: Exit the application.
     */
    int EndGameWindow(string gameMode, int numberOpponents, int numberGamesOver, bool gameFinished, std::vector<int> scores, std::vector<int> ranking);
    
    /**
     * @brief Resizes the game window to the specified dimensions.
     * 
     * @param newWidth The new width of the window in pixels.
     * @param newHeight The new height of the window in pixels.
     */
    void resizeWindow(unsigned int newWidth, unsigned int newHeight);
   
protected:
    int cell_size; /**< The size of each cell in pixels. */
    int window_w; /**< The width of the window in cells. */
    int window_h; /**< The height of the window in cells. */
    std::shared_ptr<sf::RenderWindow> window; /**< Shared pointer to the SFML render window. */

};

