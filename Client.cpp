#include "Client.h"
#include "Colors.h"
#include "PacketsMap.cpp"
#include <chrono>
#include <thread>

Client::Client(int myPort, string myIP): IP(myIP), currentPort(myPort)
{
    connected = false;
    nGamesOver = 0;
    timeout = 60;
    cout<<"Client instance created" << endl;
}

Client::~Client()
{

}
void Client::connect(){
    auto startTime = std::chrono::steady_clock::now();
    while(!connected){
        auto elapsed = std::chrono::steady_clock::now() - startTime;
        if(socket.connect(IP, currentPort) != sf::Socket::Done){
            cout << "Client failed to connect to server-->Retrying" << endl;
        }
        else{
            connected = true;
            break;
        }
        if(std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() > timeout){
            return;
        }
    }
    cout << "Client connected to server" << endl;
    // 1 packet sent by the server
    sf::Packet idPacket;
    if(socket.receive(idPacket) != sf::Socket::Done){
        cout << "Failed to get ID froms server" << endl;
        connected = false;
        return;
    }
    idPacket >> id;
    cout << "Client started with ID " << id << endl;

    // 2 packet sent by the server
    sf::Packet nOpponentsPacket;
    if(socket.receive(nOpponentsPacket) != sf::Socket::Done){
        cout << "Failed to get number of opponents froms server" << endl;
        connected = false;
        return;
    }
    nOpponentsPacket >> nOpponents;
    //Iniate a empty grid for the client connection
    for(int i = 0; i < nOpponents; i++) { 
       gridCollection.emplace_back(10, std::vector<unsigned char>(20, 0));
    }


    cout << "Client competing with  " << id << " players"<<endl;
    // Start the network communication thread
    // This allows the client to keep receiving and sending data
    //    without pertubating the thread of the game per say
    std::thread dataPacketsThread(&Client::connectedLoop, this);
    dataPacketsThread.detach(); // Detach the thread to run independently

}

void Client::connectedLoop() {
    while (connected) {
        sf::Packet dataPack;
        if (socket.receive(dataPack) != sf::Socket::Done) {
            std::cout << "Failed to receive data from server" << std::endl;
            connected = false;
            break;
        }
        
        int type;
        dataPack >> type;
        handlePacket(type, dataPack); // Handle packet based on its type
    }
}



void Client::handlePacket(int type, sf::Packet& packet) {
     switch (type) {
        case PACKET_TYPE_GAMEOVER:// Handle when someone has lost
            nGamesOver++;
            break;
        case PACKET_TYPE_START: // Handle game start packet
            gameStarted = true;
            break;
        case PACKET_TYPE_FINISHGAME: // Handle when everyone has lost
            gameFinished = true;
            std::cout << "Game finished" << std::endl;
            break;
        case PACKET_TYPE_GRID:
            int updateID, numChanges;
            //cout << "Cliente recebeu grid de inimigo"<<endl;
            packet >> updateID >> numChanges;
            //cout<<"ID changed: " << updateID<<  " Changed cells: " << numChanges << endl;
            for (int i = 0; i < numChanges; ++i) {
                int x, y;
                unsigned char value;
                packet >> x >> y >> value;
                //cout << "x : " << x << " y: " << y  <<endl;
                gridCollection[updateID][x][y] = value; // Apply changes
        }
        default:
            std::cout << "Unknown packet type received: " << type << std::endl;
    }
}


void Client::sendMessage(sf::Packet packet){
    if(socket.send(packet) != sf::Socket::Done){
        cout << "Failed to send pack from client " << endl;
    }
}

void Client::sendGameOver(){
    sf::Packet gameOverPack;
    gameOverPack << (int)PACKET_TYPE_GAMEOVER;
    if(socket.send(gameOverPack) != sf::Socket::Done){
        cout << "Failed to send pack from client " << endl;
    }
}

void Client::sendGrid(const std::vector<std::tuple<int, int, unsigned char>>& changedCells) {
    if (changedCells.empty()) return; // Skip sending if nothing changed
    sf::Packet gridPack;
    gridPack << (int)PACKET_TYPE_GRID <<id << (int)changedCells.size();
    //cout<<"ID changed: " << id<<  " Changed cells: " << (int)changedCells.size() << endl;
    for (const auto& cell : changedCells) {
        gridPack << std::get<0>(cell) << std::get<1>(cell) << std::get<2>(cell);
        //cout << "x : " <<std ::get<0>(cell)  << " y: " << std::get<1>(cell)  <<endl;
    }

    if (socket.send(gridPack) != sf::Socket::Done) {
        std::cout << "Failed to send grid update." << std::endl;
    }
}



void Client::setGameOver(){
    gameFinished = true;
}

void Client::disconnect(){
    if (connected) {
        socket.disconnect(); // Disconnect from the server
        connected = false;
        std::cout << "Client disconnected from the server." << std::endl;
    }
    sf::Packet disconnectPack;
    
}
int Client::getNumberOpponents() const{
    return nOpponents;
}

int Client::getNumberGamesOver() const{
    return nGamesOver;
}

int Client::getID() const{
    return id;
}

bool Client::isConnected(){
    return connected;
}

bool Client::isGameStarted(){
    return gameStarted;
}

bool Client::isGameFinished() {
    return gameFinished;
}

void Client::drawEnemies(sf::RenderWindow *window) {
    int rows = 20;
    int cols = 10;
    int cell_size = 14;  // Half of the main grid cell size
    int cell_size_original = 30;
    int spacing_x = 35;  // Small gap between enemy grids

    // Positioning starts from the rightmost part of the window
    int baseX = cell_size_original * 20 + spacing_x;  // Start at 600px where enemy grids should be drawn
    int baseY = (rows*cell_size_original - 2*(rows*cell_size + spacing_x))/2;                // Align enemy grids at the top

    int countingTwo = 0;
    int offset = 0;

    for (int k = 0; k < nOpponents; ++k) {
        if (k == id) continue;  // Skip the current player's grid

        int startX = baseX;
        int startY = baseY + ((offset % 2) * (rows * cell_size + spacing_x));  // Offset for vertical stacking

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                sf::RectangleShape cell(sf::Vector2f(cell_size - 0.8, cell_size - 0.8));
                cell.setPosition(startX + x * cell_size, startY + y * cell_size);

                if (gridCollection[k][x][y]) {
                    sf::Color color = GetCellColors()[gridCollection[k][x][y] - 1];
                    cell.setFillColor(color);
                } else {
                    cell.setFillColor(sf::Color::Black);
                }

                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::White);
                window->draw(cell);
            }
        }

        ++countingTwo;
        ++offset;  // Move to the next enemy grid

        // After two grids, adjust the baseX for the next pair
        if (countingTwo == 2) {
            countingTwo = 0;
            baseX = startX + (cols * cell_size) + spacing_x;  // Update baseX based on the furthermost right cell
            baseY = (rows*cell_size_original - 2*(rows*cell_size + spacing_x))/2;    
        }
    }
}
