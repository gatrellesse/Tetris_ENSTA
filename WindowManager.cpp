#include "WindowManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
using namespace std;

/**
 * @brief Constructs a WindowManager object.
 * 
 * Initializes the game window with the specified cell size, width, and height.
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
 * @brief Retrieves the current window instance.
 * 
 * @return std::shared_ptr<sf::RenderWindow> A shared pointer to the current game window.
 */
std::shared_ptr<sf::RenderWindow> WindowManager::getWindow() const {
    return window;
}

/**
 * @brief Centers text within a button.
 * 
 * Aligns the position of the text to the center of the given button.
 * 
 * @param text A reference to the SFML Text object to be centered.
 * @param button A reference to the SFML RectangleShape representing the button.
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
 * @brief Displays the lobby window.
 * 
 * This method renders the main menu with options to start the game, play a match, or exit.
 * It waits for user input and returns a value based on the user's selection.
 * 
 * @return int Returns 1 if the user starts the game, 2 for match mode, or 0 to exit.
 */
int WindowManager::LobbyWindow()
{
    // Load the texture for the sprite
    sf::Texture texture;
    if (!texture.loadFromFile("lobbyScreen.png")) { // Replace with your image path
        std::cout << "Erro ao carregar a imagem!" << std::endl;
    }

    // Create a sprite and set the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0, 0); // Adjust position as needed

    // Load the music
    sf::Music music;
    if (!music.openFromFile("musicLobby.ogg")) { // Replace with your music file path
        std::cout << "Erro ao carregar a música!" << std::endl;
    }
    // Play the music
    music.setLoop(true);  // Loop the music
    music.play();

    // Load font for text
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // Replace with the path to your font
        std::cout << "Erro ao carregar a fonte!" << std::endl;
    }

    // Title configuration
    sf::RectangleShape guideBox(sf::Vector2f(cell_size * 20, cell_size * 6));
    guideBox.setFillColor(sf::Color(128, 128, 128, 0));
    guideBox.setPosition(0, 0); // Adjusted for the new screen
    
    sf::Text title("TETRIS", font, 50);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Blue);
    title.setOutlineThickness(5);
    centerText(title, guideBox);

    // "Start" button
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

    sf::Text matchText("Match Game", font, 20);
    matchText.setFillColor(sf::Color::Black);
    centerText(matchText, matchButton);

    // "Settings" button
    sf::RectangleShape settingsButton(sf::Vector2f(200, 50));
    settingsButton.setFillColor(sf::Color(128, 128, 128, 255));
    settingsButton.setPosition(200, 400); // Ajustado para estar abaixo dos outros botões
    settingsButton.setOutlineThickness(5);
    settingsButton.setOutlineColor(sf::Color::White);

    sf::Text settingsText("Settings", font, 20);
    settingsText.setFillColor(sf::Color::Black);
    centerText(settingsText, settingsButton);


    // "Exit" button
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color(128, 128, 128, 255));
    exitButton.setPosition(200, 500); // Adjusted for the new screen
    exitButton.setOutlineThickness(5);
    exitButton.setOutlineColor(sf::Color::White);

    sf::Text exitText("Exit", font, 20);
    exitText.setFillColor(sf::Color::Black);
    centerText(exitText, exitButton);
    
    // Main loop for the lobby window
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // Detect button clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Iniciar Jogo clicado!" << std::endl;
                    return 1;
                    }
                    else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Sair clicado!" << std::endl;
                    window->close();
                    return 0;
                    } 
                 else if (matchButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Match clicado!" << std::endl;
                    return 2;
                    }
                else if (settingsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // Detecção de clique no botão Settings
                    std::cout << "Settings clicado!" << std::endl;
                    return 3; // Retorne um valor exclusivo para identificar o botão Settings
                    }
                
            }
        }

        // Render the lobby elements
        window->clear(); // Blue background
        window->draw(sprite);
        window->draw(title);
        window->draw(startButton);
        window->draw(startText);
        window->draw(matchButton);
        window->draw(matchText);
        window->draw(settingsButton); 
        window->draw(settingsText);
        window->draw(exitButton);
        window->draw(exitText);
        window->display();
    }
    return 0;
}

/**
 * @brief Displays the match mode window.
 * 
 * This method renders the match mode menu, where the player can choose to create a server,
 * find a server, or return to the lobby. It waits for user input and returns a value
 * based on the user's selection.
 * 
 * @return int Returns 1 if the user chooses to create a server, 0 to find a server, or 2 to return to the lobby.
 */
int WindowManager::MatchWindow(){
    // Load the texture for the sprite
    sf::Texture texture;
    if (!texture.loadFromFile("lobbyScreen.png")) { // Replace with your image path
        std::cout << "Erro ao carregar a imagem!" << std::endl;
    }

    // Create a sprite and set the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0, 0); // Adjust position as needed

    // Load the music
    sf::Music music;
    if (!music.openFromFile("musicLobby.ogg")) { // Replace with your music file path
        std::cout << "Erro ao carregar a música!" << std::endl;
    }
    // Play the music
    music.setLoop(true);  // Loop the music
    music.play();

    // Load font for text
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // Replace with the path to your font
        std::cout << "Erro ao carregar a fonte!" << std::endl;
    }

    // Title configuration
    sf::RectangleShape guideBox(sf::Vector2f(cell_size * 20, cell_size * 6));
    guideBox.setFillColor(sf::Color(128, 128, 128, 0));
    guideBox.setPosition(0, 0); // Adjusted for the new screen
    
    sf::Text title("MATCH GAME", font, 50);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Yellow);
    title.setOutlineThickness(5);
    centerText(title, guideBox);

    // "Create Server" button
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

    // Return to "Lobby" button
    sf::RectangleShape lobbyButton(sf::Vector2f(200, 50));
    lobbyButton.setFillColor(sf::Color(128, 128, 128, 255));
    lobbyButton.setPosition(200, 400); // Adjusted for the new screen
    lobbyButton.setOutlineThickness(5);
    lobbyButton.setOutlineColor(sf::Color::White);

    sf::Text lobbyText("Lobby", font, 20);
    lobbyText.setFillColor(sf::Color::Black);
    centerText(lobbyText, lobbyButton);

    // Main loop for the match window
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // Detect button clicks
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
 * @brief Displays the endgame window.
 * 
 * This method shows the game-over screen with options to restart the game
 * or exit. It waits for user input and returns a value based on the user's selection.
 * 
 * @return int Returns 1 if the user restarts the game, or 0 to exit.
 */
int WindowManager::EndGameWindow(){
    // Load the font for text rendering
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // Replace with the path to your font
        std::cout << "Erro ao carregar a fonte!" << std::endl;
    }

    // Title "ENDGAME"
    sf::Text title("ENDGAME", font, 50);
    title.setFillColor(sf::Color::White); /**< White text color for the title. */
    title.setPosition(200, 50); /**< Centered title position. */

    // "Restart Game" button
    sf::RectangleShape restartButton(sf::Vector2f(200, 50)); 
    restartButton.setFillColor(sf::Color(128, 128, 128, 255)); /**< Gray background color for the button. */
    restartButton.setPosition(200, 200);  /**< Button position on the screen. */
    restartButton.setOutlineThickness(5); /**< Button outline thickness. */
    restartButton.setOutlineColor(sf::Color::White); /**< Button outline color. */

    sf::Text restartText("Restart Game", font, 20);
    restartText.setFillColor(sf::Color::Black); /**< Black text color for the button label. */
    centerText(restartText, restartButton); /**< Centers the text within the button. */
    

    // "Exit" button configuration 
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color(128, 128, 128, 255)); /**< Gray background color for the button. */
    exitButton.setPosition(200, 300); /**< Button position on the screen. */
    exitButton.setOutlineThickness(5); /**< Button outline thickness. */
    exitButton.setOutlineColor(sf::Color::White); /**< Button outline color. */

    sf::Text exitText("Exit", font, 20); /**< Black text color for the button label. */
    exitText.setFillColor(sf::Color::Black); /**< Centers the text within the button. */
    centerText(exitText, exitButton);
    
    // Main loop for the endgame window
    while (window->isOpen()) {
        sf::Event event;

        // Poll events for the window
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close(); /**< Close the window if the "Close" button is pressed. */
            }

            // Detect button clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Iniciar Jogo clicado!" << std::endl;
                    return 1; /**< Return 1 for "Restart Game". */
                } else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Sair clicado!" << std::endl;
                    window->close();
                    return 0; /**< Return 0 for "Exit". */
                }
            }
        }

        // Draw a semi-transparent gray overlay
        sf::RectangleShape rect(sf::Vector2f(600, 600));
        rect.setFillColor(sf::Color(128, 128, 128, 15)); /**< Semi-transparent gray. */
        window->draw(rect);

        // Draw all elements on the screen
        window->draw(title);
        window->draw(restartButton);
        window->draw(restartText);
        window->draw(exitButton);
        window->draw(exitText);
        window->display(); /**< Display the rendered frame. */
    }
    return 0;
}

/**
 * @brief Displays the pause window.
 * 
 * This method renders the pause menu with options to continue the game,
 * restart the game, or exit. It waits for user input and returns a value
 * based on the user's selection.
 * 
 * @return int Returns 1 to continue the game, 2 to restart the game, or 0 to exit.
 */
int WindowManager::PauseWindow(){
    // Load the font for rendering text
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {  // Replace with the correct path to your font
        std::cout << "Error loading the font!" << std::endl;
    }
    std::cout<<"Entered pause menu"<<std::endl;;

    // Continue button configuration
    sf::RectangleShape continueButton(sf::Vector2f(200, 30)); 
    continueButton.setFillColor(sf::Color(128, 128, 128, 255)); /**< Gray background for the button. */
    continueButton.setPosition(200, 200); /**< Position of the button. */
    continueButton.setOutlineThickness(5); /**< Thickness of the button outline. */
    continueButton.setOutlineColor(sf::Color::White); /**< Color of the button outline. */

    sf::Text continueText("Continue", font, 15);
    continueText.setFillColor(sf::Color::Black); /**< Black text color. */
    centerText(continueText, continueButton); /**< Centers the text within the button. */

    // Restart button configuration
    sf::RectangleShape restartButton(sf::Vector2f(200, 30));
    restartButton.setFillColor(sf::Color(128, 128, 128, 255)); /**< Gray background for the button. */
    restartButton.setPosition(200, 250); /**< Position of the button. */
    restartButton.setOutlineThickness(5); /**< Thickness of the button outline. */
    restartButton.setOutlineColor(sf::Color::White); /**< Color of the button outline. */

    sf::Text restartText("Restart Game", font, 15);
    restartText.setFillColor(sf::Color::Black); /**< Black text color. */
    centerText(restartText, restartButton); /**< Centers the text within the button. */

    // Exit button configuration
    sf::RectangleShape exitButton(sf::Vector2f(200, 30));
    exitButton.setFillColor(sf::Color(128, 128, 128, 255)); /**< Gray background for the button. */
    exitButton.setPosition(200, 300); /**< Position of the button. */
    exitButton.setOutlineThickness(5); /**< Thickness of the button outline. */
    exitButton.setOutlineColor(sf::Color::White); /**< Color of the button outline. */

    sf::Text exitText("Exit", font, 15);
    exitText.setFillColor(sf::Color::Black); /**< Black text color. */
    centerText(exitText, exitButton); /**< Centers the text within the button. */

    // Main loop for the pause menu
    while (window->isOpen()) {
        sf::Event event;

        // Poll for window events
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close(); /**< Close the window if the "Close" event is triggered. */
            }

            // Detect button clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (continueButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Continuar Jogo clicado!" << std::endl;
                    return 1; /**< Return 1 to continue the game. */
                } else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Sair clicado!" << std::endl;
                    window->close();
                    return 0; /**< Return 0 to exit the game. */
                }
                else if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Restart clicado!" << std::endl;
                    return 2; /**< Return 2 to restart the game. */
                }
            }
        }

        // Draw the semi-transparent gray overlay
        sf::RectangleShape rect(sf::Vector2f(600, 600));
        rect.setFillColor(sf::Color(128, 128, 128, 15)); /**< Semi-transparent gray overlay. */
        window->draw(rect);

        // Draw buttons and their text
        window->draw(continueButton);
        window->draw(continueText);
        window->draw(restartButton);
        window->draw(restartText);
        window->draw(exitButton);
        window->draw(exitText);

        // Display the rendered frame
        window->display();
    }
    return 0;
}