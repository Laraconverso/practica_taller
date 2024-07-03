#include "server_player_receiver.h"

#include "server_game_unique_queue.h"

ServerPlayerReceiver::ServerPlayerReceiver(ServerProtocol& protocol):
        protocol(protocol), is_alive(true) {}

ActionType ServerPlayerReceiver::process_command(const uint8_t& msj) {
    switch (msj) {
        case ActionType::ATAQUE_CLIENTE:
            return ActionType::ATAQUE_CLIENTE;
        default:
            return ActionType::NULO;
    }
}

void ServerPlayerReceiver::run() {
    try {
        while (is_alive) {
            uint8_t msj = this->protocol.read_msj();
            ActionType action = process_command(msj);
            if (action != ActionType::NULO) {
                UniqueQueue::add_command(action);
            }
        }
    } catch (const std::exception& err) {
        if (this->is_alive) {
            std::cerr << "Error ocurred running the receiver: " << err.what() << "\n";
        }
        this->is_alive = false;
    }
}

bool ServerPlayerReceiver::alive_status() { return this->is_alive; }

void ServerPlayerReceiver::kill() { is_alive = false; }
