#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace std;
// Configuração do jogo
const int cell_size = 30;
const int cols = 10;
const int lin = 20;
// Matriz representando o GRID
sf::Color colors[] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue,
                    sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan};

std::vector<std::vector<unsigned char>> matrixGrid(cols, std::vector<unsigned char>(lin, 0));
bool verify_Collision(const std::vector<std::vector<int>>& testPiece, int cx, int cy, const std::vector<std::vector<unsigned char>>& matrix) {
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            if (testPiece[x][y] == 1) {
                int limx = x + cx;
                int limy = y + cy + 1; //SE EU TIRAR ESSE 1,A COLISAO VERTICAL PARA DE FUNCIONAR
                if (limx < 0 || limx >= cols ||  limy  >= lin) {
                    return true;  // Collision with ground/walls detected
                }
                if( matrixGrid[limx][limy] != 0){
                    return true;  //Collision with other pieces detected
                }
            }
        }
    }
    return false;  // No collision
}
using Matrix4x4 = std::vector<std::vector<int>>;
Matrix4x4 rotate(const Matrix4x4& matrix) {
    Matrix4x4 result(4, std::vector<int>(4, 0)); // Inicializa uma matriz 4x4 preenchida com zeros

    int len = 0;
    for (int x = 0; x < 4; x++) 
        for (int y = 0; y < 4; y++)
            if (matrix[x][y]) 
                len = max(max(x, y) + 1, len); //Verifica se é de 2/3/4
    
    int rot[4][4] = { 0 };
    for (int x = 0; x < len; x++) 
        for (int y = 0; y < len; y++)
            if (matrix[x][y]) 
                rot[len - 1 - y][x] = 1;

    for (int x = 0; x < 4; x++) 
        for (int y = 0; y < 4; y++)
            result[x][y] = rot[x][y];

    return result;
}


int main(){
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
    Matrix4x4 testPiece = matrixPieces[rand() % 7]; //escolhe uma peça aleatória
    // Criação da janela
    sf::RenderWindow window(sf::VideoMode(cell_size * cols, cell_size * lin), "Tetris");
    
    
    int cx = cols/2 - 1; int cy = 0;
    sf::Clock clock; // Timer to control delay
    sf::Clock clockFall; // Timer to control FALLdelay 
    float delay = 0.2f; // Delay in seconds 
    float delayFall = delay*2;
    bool flag_up = 0;
    while (window.isOpen())
    {   
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Evitar q a peça vá mt rapido
        if(clock.getElapsedTime().asSeconds() > delay){ 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                --cx; 
                if(verify_Collision(testPiece, cx, cy, matrixGrid))
                ++cx;
                clock.restart(); // Reset timer
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                ++cx;   
                if(verify_Collision(testPiece, cx, cy, matrixGrid))
                --cx;
                clock.restart(); // Reset timer
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                ++cy;   
                if(verify_Collision(testPiece, cx, cy, matrixGrid))
                --cy;
                clock.restart(); // Reset timer
            }
            else if (flag_up == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                flag_up = 1;
                Matrix4x4 rotatedPiece = rotate(testPiece); // Rotação temporária
                if (!verify_Collision(rotatedPiece, cx, cy, matrixGrid))
                    testPiece = rotatedPiece; // Aplica a rotação apenas se não houver colisão
                clock.restart(); // Reset timer
            }
            else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    flag_up = 0;

        }
        //Evitar q a peça vá mt rapido
        if(clockFall.getElapsedTime().asSeconds() > delayFall) { 
            // The only if statement check here is concerning the piece trespassing the ground
            if(verify_Collision(testPiece, cx, cy, matrixGrid) == false){
                cy++; 
                clockFall.restart();
            }
            else{
                for (int x = 0; x < 4; ++x) {
                    for (int y = 0; y < 4; ++y) {
                        if (testPiece[x][y] == 1) {
                            matrixGrid[cx + x][cy + y] = 1;//Register the piece(memory)
                        } 
                    }
                }
                cx = cols/2 - 1; 
                cy = 0;
                Matrix4x4 newPiece = matrixPieces[rand() % 7]; //escolhe uma peça aleatória
                testPiece = newPiece;
                clockFall.restart();
            }
        }
        window.clear();

        //Draw the cells
        for (int y = 0; y < lin; ++y){
            for (int x = 0; x < cols; ++x){
                sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                cell.setPosition(x * cell_size, y * cell_size);
                if(matrixGrid[x][y] == 1) cell.setFillColor(sf::Color::Green);
                else cell.setFillColor(sf::Color::Black);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::White);
                window.draw(cell);
            }
        }
        //Check fill lines
        for (int y = lin - 1; y > 0; y--){
            int soma = 0;
            for (int x = 0; x < cols; x++){
                if(!matrixGrid[y][x]) break;
                soma++;
            }
            if(soma == cols){
                matrixGrid[y] = std::vector<unsigned char>(cols, 0);
                for(int k = y; k > 0; --k){
                    matrixGrid[k] = matrixGrid[k-1];
                }
                matrixGrid[0] = std::vector<unsigned char>(cols, 0); // Linha do topo vira zero
                ++y; // Verifica novamente a mesma linha (agora contém a próxima linha acima)
            }
        }

        //Draw current piece
        for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                if (testPiece[x][y] == 1) {
                    sf::RectangleShape cell(sf::Vector2f(cell_size - 2, cell_size - 2));
                    cell.setPosition(cell_size * (x + cx), cell_size * (y + cy));
                    cell.setFillColor(sf::Color::Green);
                    cell.setOutlineThickness(1);
                    cell.setOutlineColor(sf::Color::White);
                    window.draw(cell);
                }
            }
        }
        
        
        // Exibe o conteúdo desenhado
        window.display();
    }

    return 0;
}
