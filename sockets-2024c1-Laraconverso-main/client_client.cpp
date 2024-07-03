#include "client_client.h"

#include <fstream>
#include <iostream>
#include <sstream>


// private
void Client::revert_ascii(const std::vector<uint8_t>& msj) {
    std::string actions(msj.begin(), msj.end());
    std::cout << actions << "\n";
    return;
}

std::vector<ActionType> Client::serialize_msj(const std::string& message) {
    std::vector<ActionType> result;
    std::istringstream iss(message);
    std::string word;
    while (iss >> word) {
        if (word == JUMP_W) {
            result.push_back(ActionType::JUMP);
        } else if (word == RIGHT_W) {
            result.push_back(ActionType::RIGHT);
        } else if (word == LEFT_W) {
            result.push_back(ActionType::LEFT);
        } else if (word == DUCK_W) {
            result.push_back(ActionType::DUCK);
        } else if (word == HIT_W) {
            result.push_back(ActionType::HIT);
        }
    }
    result.push_back(ActionType::NOP);
    return result;
}

// public
Client::Client(const std::string& hostname, const std::string& servname):
        clientProtocol(hostname, servname) {}

void Client::execute(const std::string& msj) {
    std::vector<ActionType> bytes = serialize_msj(msj);
    this->clientProtocol.send_processed_msj(bytes);
    std::vector<uint8_t> received_msj = this->clientProtocol.receive_server_msj();
    revert_ascii(received_msj);
}
