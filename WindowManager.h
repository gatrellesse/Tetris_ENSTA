#include <memory>
#include <SFML/Graphics.hpp>
#pragma once

/**
 * @class WindowManager
 * @brief Manages the main game window and various game menus (Lobby, Match, Pause, Endgame).
 * 
 * The WindowManager class handles the creation and rendering of the game window, as well as
 * the display and functionality of different game menus.
 */
class WindowManager
{
public:
    /**
     * @brief Constructs a WindowManager object.
     * 
     * Initializes the game window with the specified cell size, width, and height.
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
     * @brief Retrieves the shared pointer to the game window.
     * 
     * @return std::shared_ptr<sf::RenderWindow> A shared pointer to the current game window.
     */
    virtual std::shared_ptr<sf::RenderWindow> getWindow() const;

    /**
     * @brief Displays the lobby menu.
     * 
     * This menu allows the user to start the game, play a match, or exit the game.
     * 
     * @return int Returns 1 to start the game, 2 to play a match, or 0 to exit.
     */
    int LobbyWindow();

    /**
     * @brief Displays the match mode menu.
     * 
     * This menu allows the user to create a server, find a server, or return to the lobby.
     * 
     * @return int Returns 1 to create a server, 0 to find a server, or 2 to return to the lobby.
     */
    int MatchWindow();

    /**
     * @brief Displays the pause menu.
     * 
     * This menu provides options to continue the game, restart the game, or exit.
     * 
     * @return int Returns 1 to continue, 2 to restart, or 0 to exit.
     */
    int PauseWindow();

    /**
     * @brief Displays the endgame menu.
     * 
     * This menu is shown when the game ends, providing options to restart the game or exit.
     * 
     * @return int Returns 1 to restart the game, or 0 to exit.
     */
    int EndGameWindow();
    
protected:
    int cell_size; /**< The size of each cell in pixels. */
    int window_w; /**< The width of the window in cells. */
    int window_h; /**< The height of the window in cells. */
    std::shared_ptr<sf::RenderWindow> window; /**< Shared pointer to the SFML game window. */

};

