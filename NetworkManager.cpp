#include "NetworkManager.h"


NetworkManager::NetworkManager(int portUser, int waitingfor):
        port(portUser), nClients(waitingfor){
    clients.reserve(nClients);
    for (int i = 0; i < nClients; ++i) {
            clients.push_back(std::make_unique<sf::TcpSocket>());
        }
}

NetworkManager::~NetworkManager()
{
}


int NetworkManager::statusServer(){
    sf::Socket::Status status = listener.listen(port);
    if (status != sf::Socket::Done) {
        std::cout << "Error binding the listener to the port" << std::endl;
        return 0;
    }
    else{
        std::cout << "Server is listening on port:" << port << std::endl; ; 
        return 1;
    }
}

int NetworkManager::connectClients(string serverIP){
    {
        int flagfail = 0;
        for (int i = 0; i < clients.size(); ++i) {
            if (clients[i]->connect(serverIP, port) != sf::Socket::Done) {
                std::cout << "Error connecting client " << i + 1 << " to server" << std::endl;
                flagfail = 1;
            } else {
                std::cout << "Client " << i + 1 << " connected to server!" << std::endl;
            }
        }
        if(flagfail) return 0;
        return 1;

    }
}

void NetworkManager::sendMessage(){
    for (size_t i = 0; i < clients.size(); ++i) {
            std::string message = "Hello from Server to Client " + std::to_string(i + 1);
            clients[i]->send(message.c_str(), message.size() + 1);
        }
        
}

