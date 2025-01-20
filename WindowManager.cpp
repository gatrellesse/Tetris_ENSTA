#include "WindowManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
using namespace std;

WindowManager::WindowManager(int cell_size, int window_w, int window_h):
    cell_size(cell_size), window_w(window_w), window_h(window_h)
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(cell_size * window_w, cell_size * window_h), "TrelleTetris");
}

WindowManager::~WindowManager()
{
}

std::shared_ptr<sf::RenderWindow> WindowManager::getWindow() const {
    return window;
}

int WindowManager::LobbyWindow()
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // Substitua pelo caminho para sua fonte
        std::cout << "Erro ao carregar a fonte!" << std::endl;
    }

    // Título do lobby
    sf::Text title("Lobby", font, 50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 50); // Ajustado para centralizar

    // Botão "Iniciar Jogo"
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(200, 200); // Ajustado para a nova tela
    startButton.setOutlineThickness(1);
    startButton.setOutlineColor(sf::Color::White);

    sf::Text startText("Start Trelletetris", font, 20);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(225, 215); // Ajustado para centralizar no botão

    // Botão "Sair"
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(200, 300); // Ajustado para a nova tela
    exitButton.setOutlineThickness(1);
    exitButton.setOutlineColor(sf::Color::White);

    sf::Text exitText("Exit", font, 20);
    exitText.setFillColor(sf::Color::Black);
    exitText.setPosition(275, 315); // Ajustado para centralizar no botão
    
    
     while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // Detecção de clique nos botões
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Iniciar Jogo clicado!" << std::endl;
                    return 1;
                } else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Sair clicado!" << std::endl;
                    window->close();
                    return 0;
                }
            }
        }

        // Desenho na janela
        window->clear(sf::Color::Blue); // Fundo azul
        window->draw(title);
        window->draw(startButton);
        window->draw(startText);
        window->draw(exitButton);
        window->draw(exitText);
        window->display();
    }
}

int WindowManager::EndGameWindow(){
    
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // Substitua pelo caminho para sua fonte
        std::cout << "Erro ao carregar a fonte!" << std::endl;
    }

    //Title endgame
    sf::Text title("ENDGAME", font, 50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 50); // Ajustado para centralizar

    // Restart button
    sf::RectangleShape restartButton(sf::Vector2f(200, 50));
    restartButton.setFillColor(sf::Color::Green);
    restartButton.setPosition(200, 200); // Ajustado para a nova tela
    restartButton.setOutlineThickness(1);
    restartButton.setOutlineColor(sf::Color::White);

    sf::Text restartText("Restart Game", font, 20);
    restartText.setFillColor(sf::Color::Black);
    restartText.setPosition(225, 215); // Ajustado para centralizar no botão

    // Botão "Sair"
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(200, 300); // Ajustado para a nova tela
    exitButton.setOutlineThickness(1);
    exitButton.setOutlineColor(sf::Color::White);

    sf::Text exitText("Exit", font, 20);
    exitText.setFillColor(sf::Color::Black);
    exitText.setPosition(275, 315); // Ajustado para centralizar no botão
    
    
     while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // Detecção de clique nos botões
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Iniciar Jogo clicado!" << std::endl;
                    return 1;
                } else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Sair clicado!" << std::endl;
                    window->close();
                    return 0;
                }
            }
        }
        sf::RectangleShape rect(sf::Vector2f(600, 600));
        rect.setFillColor(sf::Color(128, 128, 128, 15)); // Semi-transparent gray
        window->draw(rect);

        window->draw(title);
        window->draw(restartButton);
        window->draw(restartText);
        window->draw(exitButton);
        window->draw(exitText);
        window->display();
    }
}