#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
    if (status != sf::Socket::Done) {
        std::cerr << "Error connecting to the server\n";
        return 1;
    }
    std::cout << "Connected to the server!\n";

    char buffer[1024];
    std::size_t received;
    if (socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Done) {
        std::cerr << "Error receiving data from the server\n";
        return 1;
    }
    std::cout << "Server says: " << buffer << std::endl;

    // Main game loop would go here, sending and receiving game data

    return 0;
}
