#include "server_protocol.h"

#include <iostream>
#include <utility>
#include <vector>

#include <netinet/in.h>


// private methods

Socket ServerProtocol::accept_connection() { return server_skt.accept(); }

// public methods
std::vector<ActionType> ServerProtocol::receive_message(bool* connection_status) {
    bool was_closed = false;
    std::vector<enum ActionType> actions;
    while (not was_closed) {
        uint8_t serialized_action;
        int cant_bytes_recv =
                this->server_skt.recvall(&serialized_action, sizeof(uint8_t), &was_closed);
        if (cant_bytes_recv <= 0) {
            if (was_closed) {
                *connection_status = false;
            }
            break;
        }
        if (serialized_action == ActionType::NOP) {
            break;
        }

        actions.push_back(static_cast<ActionType>(serialized_action));
    }
    return actions;
}


void ServerProtocol::send_performed_actions(std::vector<uint8_t>& performed_actions) {
    bool was_closed = false;
    uint16_t size = static_cast<uint16_t>(performed_actions.size());
    size = htons(size);
    this->server_skt.sendall(&size, sizeof(uint16_t), &was_closed);
    if (was_closed) {
        return;
    }
    was_closed = false;
    this->server_skt.sendall(performed_actions.data(), performed_actions.size(), &was_closed);
    if (was_closed) {
        return;
    }
}


ServerProtocol::ServerProtocol(const std::string& port):
        server_port(port), server_skt(port.c_str()) {}

void ServerProtocol::initialize_socket() {
    Socket client_skt = this->accept_connection();
    server_skt = std::move(client_skt);
}
