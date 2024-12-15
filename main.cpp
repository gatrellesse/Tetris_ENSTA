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
void rotate(Matrix4x4& matrix) {

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
            matrix[x][y] = rot[x][y];

}
void clean_line(std::vector<std::vector<unsigned char>>& matrixGrid) {
    int target = lin - 1;
    for (int y = lin - 1; y >= 1; --y) {
        if (std::all_of(matrixGrid[y].begin(), matrixGrid[y].end(), [](unsigned char cell) { return cell != 0; })) {
            continue; // Linha cheia, pula sem copiar
        }
        matrixGrid[target--] = matrixGrid[y];
    }
    while (target >= 0) {
        matrixGrid[target--] = std::vector<unsigned char>(cols, 0);
    }
}

int main(){
    //Matrix do tipo de peças
    using Matrix4x4 = std::vector<std::vector<int>>;
    std::vector<Matrix4x4> matrixPieces = {
        {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
        {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // O
        {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // T
        {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}, // L
        {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}}, // J
        {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, // Z
        {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}  // S
    };
    Matrix4x4 testPiece = matrixPieces[4]; //escolhe uma peça aleatória
    // Criação da janela
    sf::RenderWindow window(sf::VideoMode(cell_size * cols, cell_size * lin), "Tetris");
    
    
    int cx = cols/2 - 1; int cy = 0;
    sf::Clock clock; // Timer to control delay
    sf::Clock clockFall; // Timer to control FALLdelay 
    float delay = 0.4f; // Delay in seconds 
    bool flag_up = 0;
    while (window.isOpen())
    {   
        delay = 0.4f;
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
                delay = 0.05f;
                clock.restart(); // Reset timer
            }
            else if (flag_up == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                flag_up = 1;
                rotate(testPiece); // Rotação temporária
                if (verify_Collision(testPiece, cx, cy, matrixGrid))
                    rotate(testPiece);rotate(testPiece);rotate(testPiece);//Desfaz a rotacao q colidiu
                clock.restart(); // Reset timer
            }
            else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    flag_up = 0;

        }
        //Evitar q a peça vá mt rapido
        if(clockFall.getElapsedTime().asSeconds() > delay) { 
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