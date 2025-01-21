#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::TcpListener listener;
    sf::Socket::Status status = listener.listen(53000);
    if (status != sf::Socket::Done) {
        std::cerr << "Error binding the listener to the port\n";
        return 1;
    }
    std::cout << "Server is listening on port 53000...\n";

    sf::TcpSocket client1, client2;
    std::cout << "Waiting for two players to connect...\n";
    
    if (listener.accept(client1) != sf::Socket::Done) {
        std::cerr << "Error accepting player 1\n";
        return 1;
    }
    std::cout << "Player 1 connected!\n";

    if (listener.accept(client2) != sf::Socket::Done) {
        std::cerr << "Error accepting player 2\n";
        return 1;
    }
    std::cout << "Player 2 connected!\n";

    // Example: Send a start game message to both clients
    std::string startMessage = "Start";
    client1.send(startMessage.c_str(), startMessage.size() + 1);
    client2.send(startMessage.c_str(), startMessage.size() + 1);

    // Main game loop would go here, handling game state and communication

    return 0;
}
