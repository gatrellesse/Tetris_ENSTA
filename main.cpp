#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

int main()
{
    // Configuração do jogo
    const int cell_size = 30;
    const int cols = 10;
    const int lin = 20;

    // Matriz representando as células do jogo
    std::vector<std::vector<unsigned char>> matrix(cols, std::vector<unsigned char>(lin, 0));
    
    // Matriz para todas as peças
    using Matrix4x4 = std::vector<std::vector<int>>;
    //{I, O, T, L, J, Z, S}
    // Vetor para armazenar as peças
    std::vector<Matrix4x4> matrixPieces;

    // Adicionando a peça 'I' ao vetor de peças
    Matrix4x4 pieceI = {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    matrixPieces.push_back(pieceI);

    Matrix4x4 pieceO = {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    matrixPieces.push_back(pieceO);

    Matrix4x4 pieceT = {
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    matrixPieces.push_back(pieceT);

    Matrix4x4 pieceL = {
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    matrixPieces.push_back(pieceL);

    Matrix4x4 pieceJ = {
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    matrixPieces.push_back(pieceJ);

    Matrix4x4 pieceZ = {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    matrixPieces.push_back(pieceZ);

    Matrix4x4 pieceS = {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    matrixPieces.push_back(pieceS);
    Matrix4x4 testPiece = matrixPieces[0];
    // Criação da janela
    sf::RenderWindow window(sf::VideoMode(cell_size * cols, cell_size * lin), "Tetris");
    int cx = 0;
    int cy = 0;
    sf::Clock clock; // Timer to control delay
    sf::Clock clockFall; // Timer to control FALLdelay 
    float delay = 0.2f; // Delay in seconds (200 ms)

    while (window.isOpen())
    {   
        float delayFall = delay;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        if(clock.getElapsedTime().asSeconds() > delay) //Evitar q a peça vá mt rapido
        { 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                --cx;  
                clock.restart(); // Reset timer
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                ++cx;   
                clock.restart(); // Reset timer
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                ++cy;   
                clock.restart(); // Reset timer
            }

        }
        if(clockFall.getElapsedTime().asSeconds() > delayFall) //Evitar q a peça vá mt rapido
        { 
            if(cy < lin*cell_size)
                {
                ++cy; 
                clockFall.restart();}
        }
        //     // Verifica se um botão do mouse foi pressionado
        //     if (event.type == sf::Event::MouseButtonPressed)
        //     {
        //         if (event.mouseButton.button == sf::Mouse::Left)
        //         {
        //             // Calcula as coordenadas da célula clicada
        //             unsigned char cell_x = event.mouseButton.x / cell_size;
        //             unsigned char cell_y = event.mouseButton.y / cell_size;

        //             // Verifica se as coordenadas estão dentro dos limites
        //             if (cell_x < cols && cell_y < lin)
        //             {
        //                 // Alterna o valor da célula entre 0 e 1
        //                 matrix[cell_x][cell_y] = 1 - matrix[cell_x][cell_y];
        //             }
        //         }
        //     }
        // }

        // Limpa a janela
        window.clear();

        // Draw the cells
        for (int x = 0; x < cols; ++x)
        {
            for (int y = 0; y < lin; ++y)
            {
                sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                cell.setPosition(x * cell_size, y * cell_size);

                if (matrix[x][y] == 1)
                    cell.setFillColor(sf::Color::Green);
                else
                    cell.setFillColor(sf::Color::Black);

                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::White);

                window.draw(cell);
            }
        }
        for(int x = 0; x < 4; ++x){
            for(int y = 0; y < 4; ++y){
                sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                cell.setPosition(cell_size * (x + cx), cell_size*(y + cy));

                if (matrixPieces[0][x][y] == 1)
                    cell.setFillColor(sf::Color::Green);
                else
                    cell.setFillColor(sf::Color::Black);

                cell.setOutlineThickness(1);

                window.draw(cell);
        }
        }
        
        // Exibe o conteúdo desenhado
        window.display();
    }

    return 0;
}
