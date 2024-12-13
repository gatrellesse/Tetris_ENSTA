#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Cria a janela com resolução 300x600 pixels
    sf::RenderWindow window(sf::VideoMode(300, 600), "SFML works!");

    // Limita a taxa de quadros a 60 FPS (opcional)
    window.setFramerateLimit(60);

    // Verifica se a janela foi criada corretamente
    if (!window.isOpen())
    {
        std::cerr << "Erro ao criar janela!" << std::endl;
        return -1;
    }

    // Cria objetos de texto e fonte
    sf::Text text;
    sf::Font font;

    // Carrega a fonte a partir de um arquivo
    if (!font.loadFromFile("Arial.ttf")) // Substitua pelo caminho correto para sua fonte
    {
        std::cerr << "Erro ao carregar a fonte!" << std::endl;
        return -1;
    }

    // Define a fonte para o texto
    text.setFont(font);

    // Define a string a ser exibida
    text.setString("Vai tomar no cu, Davy");

    // Define o tamanho dos caracteres
    text.setCharacterSize(24); // em pixels, não em pontos!

    // Define a cor do texto
    text.setFillColor(sf::Color::Red);

    // Define o estilo do texto
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Define a posição do texto na janela
    text.setPosition(30.f, 100.f);

    // Loop principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Fecha a janela se o evento for de fechamento
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Limpa a janela com a cor preta
        window.clear();

        // Desenha o texto na janela
        window.draw(text);

        // Exibe o conteúdo desenhado na janela
        window.display();
    }

    return 0;
}
