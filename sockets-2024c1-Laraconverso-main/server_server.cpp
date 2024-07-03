#include "server_server.h"

#include <iostream>
#include <string>
#include <vector>

// private

std::vector<uint8_t> Server::process_msj(const std::vector<ActionType>& actions) {
    std::string msj = gameLogic.unserialize_msj(actions);
    std::string actions_clean = gameLogic.combo_checker(msj);
    std::vector<uint8_t> processed_line = gameLogic.message_parser(actions_clean);
    return processed_line;
}

// public
Server::Server(const std::string& port): serverProtocol(port), gameLogic() {}


void Server::execute() {
    serverProtocol.initialize_socket();
    bool active_connection = true;
    while (active_connection) {
        std::vector<ActionType> actions_bytes = serverProtocol.receive_message(&active_connection);
        if (!active_connection)
            break;
        std::vector<uint8_t> processed_message = process_msj(actions_bytes);
        serverProtocol.send_performed_actions(processed_message);
    }
    std::cout << "Actions: " << gameLogic.get_cant_actions() << "\n";
}
