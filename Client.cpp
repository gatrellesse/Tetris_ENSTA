#include "Client.h"

Client::Client(int myPort, string myIP): IP(myIP), currentPort(myPort)
{

}

Client::~Client()
{

}

int Client::searchServer(){
    sf::Socket::Status status = socket.connect(IP, currentPort);
    if (status != sf::Socket::Done) {
        std::cout << "Error connecting to the server" << std::endl;
        return 0;
    }
    std::cout << "Connected to the server!" << std::endl;
    return 1;
}
void Client::receiveMessage(){
    char buffer[1024];
    std::size_t received;
    if (socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Done) {
        std::cout << "Error receiving data from the server\n"<< std::endl;
    }
    std::cout << "Server says: " << buffer << std::endl;
}