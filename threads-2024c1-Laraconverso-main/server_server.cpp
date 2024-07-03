#include "server_server.h"

#include "common_actions.h"
#include "server_acceptor.h"


Server::Server(const char* port): port(port) {}

void Server::execute() {
    Monitor monitor;
    Acceptor acceptor(this->port, monitor);
    std::string line = "";
    acceptor.start();
    Game game(monitor);
    game.start();
    do {
        std::getline(std::cin, line);
    } while (line != C_QUIT);
    game.stop();
    game.join();
    acceptor.stop();
    acceptor.join();
}
