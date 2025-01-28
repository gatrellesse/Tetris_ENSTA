#include "WindowManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <filesystem>


/**
 * @class WindowManager
 * @brief Manages the main game window and user interface elements such as menus and buttons.
 */

/**
 * @brief Constructs a new WindowManager instance.
 * 
 * @param cell_size The size of each cell in pixels.
 * @param window_w The width of the window in cells.
 * @param window_h The height of the window in cells.
 */
WindowManager::WindowManager(int cell_size, int window_w, int window_h):
    cell_size(cell_size), window_w(window_w), window_h(window_h)
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(cell_size * window_w, cell_size * window_h), "TrelleTetris");
}

/**
 * @brief Destructor for the WindowManager class.
 */
WindowManager::~WindowManager()
{
}

/**
 * @brief Retrieves the main game window.
 * 
 * @return A shared pointer to the SFML render window.
 */
std::shared_ptr<sf::RenderWindow> WindowManager::getWindow() const {
    return window;
}

/**
 * @brief Centers text within a rectangle shape.
 * 
 * @param text The text to center.
 * @param button The rectangle shape to center the text within.
 */
void centerText(sf::Text& text, const sf::RectangleShape& button) {
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::Vector2f buttonSize = button.getSize();
    sf::Vector2f buttonPos = button.getPosition();

    // Set origin to the center of the text
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);
    
    // Set position to the center of the button
    text.setPosition(buttonPos.x + buttonSize.x / 2.0f, 
                     buttonPos.y + buttonSize.y / 2.0f);
};

/**
 * @brief Displays the lobby menu and handles user interactions.
 * 
 * @return An integer indicating the selected action: 1 (start game), 2 (match), or 0 (exit).
 */
int WindowManager::LobbyWindow()
{
    // Load the texture for the sprite
    sf::Texture texture;
    if (!texture.loadFromFile("src/Assets/lobbyScreen.png")) { // Replace with your image path
        std::cout << "Error loading image!" << std::endl;
    }

    // Create a sprite and set the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0, 0); // Adjust position as needed

    // Load the music
    sf::Music music;
    if (!music.openFromFile("src/Assets/musicLobby.ogg")) { // Replace with your music file path
        std::cout << "Error loading music!" << std::endl;
    }
    // Play the music
    music.setLoop(true);  // Loop the music
    music.play();

    sf::Font font;
    if (!font.loadFromFile("src/Assets/arial.ttf")) { // Substitua pelo caminho para sua fonte
        std::cout << "Error loading font!" << std::endl;
    }

    //Guide to fix the title
    sf::RectangleShape guideBox(sf::Vector2f(cell_size * 20, cell_size * 6));
    guideBox.setFillColor(sf::Color(128, 128, 128, 0));
    guideBox.setPosition(0, 0); // Adjusted for the new screen
    
    sf::Text title("TETRIS", font, 50);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Blue);
    title.setOutlineThickness(5);
    centerText(title, guideBox);

    // "Start Game" button
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color(128, 128, 128, 255));
    startButton.setPosition(200, 200); // Adjusted for the new screen
    startButton.setOutlineThickness(5);
    startButton.setOutlineColor(sf::Color::White);

    sf::Text startText("Start Trelletetris", font, 20);
    startText.setFillColor(sf::Color::Black);
    centerText(startText, startButton);

    // "Match" button
    sf::RectangleShape matchButton(sf::Vector2f(200, 50));
    matchButton.setFillColor(sf::Color(128, 128, 128, 255));
    matchButton.setPosition(200, 300); // Adjusted for the new screen
    matchButton.setOutlineThickness(5);
    matchButton.setOutlineColor(sf::Color::White);

    sf::Text matchText("Match", font, 20);
    matchText.setFillColor(sf::Color::Black);
    centerText(matchText, matchButton);

    // "Exit" button
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color(128, 128, 128, 255));
    exitButton.setPosition(200, 400); // Adjusted for the new screen
    exitButton.setOutlineThickness(5);
    exitButton.setOutlineColor(sf::Color::White);

    sf::Text exitText("Exit", font, 20);
    exitText.setFillColor(sf::Color::Black);
    centerText(exitText, exitButton);
    
     while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // Button click detection
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Start pressed!" << std::endl;
                    return 1;
                } else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Exit pressed!" << std::endl;
                    window->close();
                    return 0;
                    }
                 else if (matchButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Match pressed!" << std::endl;
                    return 2;
                    }
            }
        }

        // Drawing on the window
        window->clear(); // Blue background
        window->draw(sprite);
        window->draw(title);
        window->draw(startButton);
        window->draw(startText);
        window->draw(matchButton);
        window->draw(matchText);
        window->draw(exitButton);
        window->draw(exitText);
        window->display();
    }
    return 0;
}

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
int WindowManager::MatchWindow(){
    // Load the texture for the sprite
    sf::Texture texture;
    if (!texture.loadFromFile("src/Assets/lobbyScreen.png")) { // Replace with your image path
        std::cout << "Error loading image!" << std::endl;
    }

    // Create a sprite and set the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0, 0); // Adjust position as needed

    // Load the music
    sf::Music music;
    if (!music.openFromFile("src/Assets/musicLobby.ogg")) { // Replace with your music file path
        std::cout << "Error loading music!" << std::endl;
    }
    // Play the music
    music.setLoop(true);  // Loop the music
    music.play();

    sf::Font font;
    if (!font.loadFromFile("src/Assets/arial.ttf")) { // Replace with the path to your source
        std::cout << "Error loading font!" << std::endl;
    }

    //Guide to fix the title
    sf::RectangleShape guideBox(sf::Vector2f(cell_size * 20, cell_size * 6));
    guideBox.setFillColor(sf::Color(128, 128, 128, 0));
    guideBox.setPosition(0, 0); // Adjusted for the new screen
    
    sf::Text title("MATCH GAME", font, 50);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Yellow);
    title.setOutlineThickness(5);
    centerText(title, guideBox);

    // "Create Serve" button
    sf::RectangleShape serverButton(sf::Vector2f(200, 50));
    serverButton.setFillColor(sf::Color(128, 128, 128, 255));
    serverButton.setPosition(200, 200); // Adjusted for the new screen
    serverButton.setOutlineThickness(5);
    serverButton.setOutlineColor(sf::Color::White);

    sf::Text serverText("Create Server", font, 20);
    serverText.setFillColor(sf::Color::Black);
    centerText(serverText, serverButton);

    // "Find Server" button
    sf::RectangleShape clientButton(sf::Vector2f(200, 50));
    clientButton.setFillColor(sf::Color(128, 128, 128, 255));
    clientButton.setPosition(200, 300); // Adjusted for the new screen
    clientButton.setOutlineThickness(5);
    clientButton.setOutlineColor(sf::Color::White);

    sf::Text clientText("Find Server", font, 20);
    clientText.setFillColor(sf::Color::Black);
    centerText(clientText, clientButton);

     // "Exit" button
    sf::RectangleShape lobbyButton(sf::Vector2f(200, 50));
    lobbyButton.setFillColor(sf::Color(128, 128, 128, 255));
    lobbyButton.setPosition(200, 400); // Adjusted for the new screen
    lobbyButton.setOutlineThickness(5);
    lobbyButton.setOutlineColor(sf::Color::White);

    sf::Text lobbyText("Lobby", font, 20);
    lobbyText.setFillColor(sf::Color::Black);
    centerText(lobbyText, lobbyButton);

     while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // Button click detection
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (serverButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Creating server!" << std::endl;
                    return 1;
                } else if (clientButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Looking for server!" << std::endl;
                    return 0;
                    }
                else if (lobbyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Back to the lobby!" << std::endl;
                    return 2;
                }
            }
        }

        // Drawing on the window
        window->clear(); // Blue background
        window->draw(sprite);
        window->draw(title);
        window->draw(serverButton);
        window->draw(serverText);
        window->draw(clientButton);
        window->draw(clientText);
        window->draw(lobbyButton);
        window->draw(lobbyText);

        window->display();
    }
    return 0;

}

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
int WindowManager::EndGameWindow(string gameMode, int numberOpponents, int numberGamesOver, bool gameFinished, std::vector<int> scores, std::vector<int> ranking){
    
    sf::Font font;
    if (!font.loadFromFile("src/Assets/arial.ttf")) { // Replace with the path to your source
        std::cout << "Error loading font!" << std::endl;
    }

    sf::RectangleShape guideBox(sf::Vector2f(cell_size * 20, cell_size * 6));
    guideBox.setFillColor(sf::Color(128, 128, 128, 0));
    guideBox.setPosition(0, 0); // Adjusted for the new screen

    //Title endgame
    sf::Text title("ENDGAME", font, 50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 50); // Adjusted to center
    title.setOutlineThickness(5);
    title.setOutlineColor(sf::Color::Red);
    centerText(title, guideBox);

    // Restart button
    sf::RectangleShape restartButton(sf::Vector2f(200, 30));
    restartButton.setFillColor(sf::Color(128, 128, 128, 255));
    restartButton.setPosition(200, 200); // Adjusted for the new screen
    restartButton.setOutlineThickness(5);
    restartButton.setOutlineColor(sf::Color::White);

    sf::Text restartText("Restart Game", font, 20);
    restartText.setFillColor(sf::Color::Black);
    centerText(restartText, restartButton);
    
    // Lobby button
    sf::RectangleShape lobbyButton(sf::Vector2f(200, 30));
    lobbyButton.setFillColor(sf::Color(128, 128, 128, 255));
    lobbyButton.setPosition(200, 250); // Adjust position
    lobbyButton.setOutlineThickness(5);
    lobbyButton.setOutlineColor(sf::Color::White);

    sf::Text lobbyText("Lobby", font, 15);
    lobbyText.setFillColor(sf::Color::Black);
    centerText(lobbyText, lobbyButton);

    // "Exit" button
    sf::RectangleShape exitButton(sf::Vector2f(200, 30));
    exitButton.setFillColor(sf::Color(128, 128, 128, 255));
    exitButton.setPosition(200, 300); // Adjusted for the new screen
    exitButton.setOutlineThickness(5);
    exitButton.setOutlineColor(sf::Color::White);

    sf::Text exitText("Exit", font, 20);
    exitText.setFillColor(sf::Color::Black);
    centerText(exitText, exitButton);

    // Ranking
    sf::RectangleShape rankingSquare(sf::Vector2f(200, 100));
    rankingSquare.setFillColor(sf::Color(128, 128, 128, 255));
    rankingSquare.setPosition(200, 350); // Adjusted for the new screen
    rankingSquare.setOutlineThickness(5);
    rankingSquare.setOutlineColor(sf::Color::White);
        //Score square guide
    sf::RectangleShape scoreSquare(sf::Vector2f(100,100));
    scoreSquare.setPosition(200,350);
        //Client square guide
    sf::RectangleShape clientSquare(sf::Vector2f(100,100));
    clientSquare.setPosition(300,350);

    ostringstream resultScore;
    ostringstream resultClient;
    resultScore << "Score" <<  "\n";
    resultClient << "  Client ID" <<  "\n";
    for (size_t i = 0; i < scores.size(); ++i) {
        resultScore << scores[scores.size()-i-1]  << "\n";
        resultClient<< ranking[i] << "\n"; // Format: score[i] ranking[i]
    }

    sf::Text scoreText(resultScore.str(), font, 20);
    scoreText.setFillColor(sf::Color::Black);
    centerText(scoreText, scoreSquare);
    sf::Text clientText(resultClient.str(), font, 20);
    clientText.setFillColor(sf::Color::Black);
    centerText(clientText, clientSquare);
    
    // Waiting others players finish
    sf::RectangleShape waitingButton(sf::Vector2f(250, 50));
    waitingButton.setFillColor(sf::Color(128, 128, 128, 255));
    waitingButton.setPosition(200, 200); // Adjusted for the new screen
    waitingButton.setOutlineThickness(5);
    waitingButton.setOutlineColor(sf::Color::White);
    
    string waitingP = "Waiting players to finish: " + to_string(numberGamesOver) + "/" + to_string(numberOpponents);
    sf::Text waitingText(waitingP , font, 20);
    waitingText.setFillColor(sf::Color::Black);
    centerText(waitingText, waitingButton);

    
     while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            // Button click detection
            //Single, match by himself or match with game over for all players
            if ((gameMode == "Single" || numberOpponents == 1 || gameFinished == true ) && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Star pressed!" << std::endl;
                    return 1;
                } else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Exit pressed!" << std::endl;
                    window->close();
                    return 0;
                }else if (lobbyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Lobby pressed!" << std::endl;
                    return 2;
                }
            }
        }

        sf::RectangleShape rect(sf::Vector2f(600, 600));
        rect.setFillColor(sf::Color(128, 128, 128, 15)); // Semi-transparent gray

        window->draw(rect);
        window->draw(title);
        if(gameMode == "Single" || (numberOpponents == 1 && gameFinished == true)){
            window->draw(restartButton);
            window->draw(restartText);
            window->draw(lobbyButton);
            window->draw(lobbyText);
            window->draw(exitButton);
            window->draw(exitText);
            window->draw(rankingSquare);
            window->draw(clientText);
            window->draw(scoreText);
        }
        else if(gameMode == "Match" && gameFinished == true){
            window->draw(lobbyButton);
            window->draw(lobbyText);
            window->draw(exitButton);
            window->draw(exitText);
            window->draw(rankingSquare);
            window->draw(clientText);
            window->draw(scoreText);
        }
        if(gameMode == "Match" && gameFinished == false){
            window->draw(waitingButton);
            window->draw(waitingText);
            window->display();
            break;
        }
        window->display();
    }
    return -1;
}

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
int WindowManager::PauseWindow(){
    sf::Font font;
    if (!font.loadFromFile("src/Assets/arial.ttf")) { // Replace with the path to your source
        std::cout << "Error loading font!" << std::endl;
    }
    std::cout<<"Entrou no pause"<<std::endl;;
    // Continue button
    // Function to centralize text within a rectangle


    // Continue button
    sf::RectangleShape continueButton(sf::Vector2f(200, 30));
    continueButton.setFillColor(sf::Color(128, 128, 128, 255));
    continueButton.setPosition(200, 200); // Adjust position
    continueButton.setOutlineThickness(5);
    continueButton.setOutlineColor(sf::Color::White);

    sf::Text continueText("Continue", font, 15);
    continueText.setFillColor(sf::Color::Black);
    centerText(continueText, continueButton);

    // Restart button
    sf::RectangleShape restartButton(sf::Vector2f(200, 30));
    restartButton.setFillColor(sf::Color(128, 128, 128, 255));
    restartButton.setPosition(200, 250); // Adjust position
    restartButton.setOutlineThickness(5);
    restartButton.setOutlineColor(sf::Color::White);

    sf::Text restartText("Restart", font, 15);
    restartText.setFillColor(sf::Color::Black);
    centerText(restartText, restartButton);

    // Lobby button
    sf::RectangleShape lobbyButton(sf::Vector2f(200, 30));
    lobbyButton.setFillColor(sf::Color(128, 128, 128, 255));
    lobbyButton.setPosition(200, 300); // Adjust position
    lobbyButton.setOutlineThickness(5);
    lobbyButton.setOutlineColor(sf::Color::White);

    sf::Text lobbyText("Lobby", font, 15);
    lobbyText.setFillColor(sf::Color::Black);
    centerText(lobbyText, lobbyButton);

    // Exit button
    sf::RectangleShape exitButton(sf::Vector2f(200, 30));
    exitButton.setFillColor(sf::Color(128, 128, 128, 255));
    exitButton.setPosition(200, 350); // Adjust position
    exitButton.setOutlineThickness(5);
    exitButton.setOutlineColor(sf::Color::White);

    sf::Text exitText("Exit", font, 15);
    exitText.setFillColor(sf::Color::Black);
    centerText(exitText, exitButton);

    
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // Button click detection
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Exit pressed!" << std::endl;
                    window->close();
                    return 0;
                } else if (continueButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Continue pressed!" << std::endl;
                    return 1;
                } else if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Restart pressed!" << std::endl;
                    return 2;
                }
                else if (lobbyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Lobby pressed!" << std::endl;
                    return 3;
                }
            }

        sf::RectangleShape rect(sf::Vector2f(600, 600));
        rect.setFillColor(sf::Color(128, 128, 128, 15)); // Semi-transparent gray
        window->draw(rect);
        window->draw(continueButton);
        window->draw(continueText);
        window->draw(restartButton);
        window->draw(restartText);
        window->draw(exitButton);
        window->draw(exitText);
        window->draw(lobbyButton);
        window->draw(lobbyText);
        window->display();
        }
    }
    return 0;
}

/**
 * @brief Resizes the game window to the specified dimensions.
 * 
 * @param newWidth The new width of the window in pixels.
 * @param newHeight The new height of the window in pixels.
 */
void WindowManager::resizeWindow(unsigned int newWidth, unsigned int newHeight) {
    window->setSize(sf::Vector2u(newWidth, newHeight));
    //std::cout << "Window resized to: " << newWidth << "x" << newHeight << std::endl;
}
