#include "server_player_sender.h"


ServerPlayerSender::ServerPlayerSender(ServerProtocol& protocol, Queue<Msj>& player_queue):
        protocol(protocol), is_alive(true), msjs_to_send(player_queue) {}

void ServerPlayerSender::run() {
    while (this->is_alive) {
        try {
            Msj msj_to_send = msjs_to_send.pop();
            this->protocol.send_msj(msj_to_send);
        } catch (const std::exception& err) {
            if (this->is_alive) {
                std::cerr << "Error occurred running the sender: " << err.what() << "\n";
            }
            this->is_alive = false;
        }
    }
}

bool ServerPlayerSender::alive_status() { return this->is_alive; }

void ServerPlayerSender::kill() {
    this->is_alive = false;
    this->msjs_to_send.close();
}
