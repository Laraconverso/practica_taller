#include "server_player.h"

ServerPlayer::ServerPlayer(Socket&& skt):
        player_skt(std::move(skt)),
        msj_queue(),
        serverProtocol(this->player_skt),
        receiver(this->serverProtocol),
        sender(this->serverProtocol, this->msj_queue) {}

void ServerPlayer::start() {
    this->receiver.start();
    this->sender.start();
}

void ServerPlayer::stop_threads() {
    this->receiver.kill();
    this->sender.kill();
}

bool ServerPlayer::is_alive() { return receiver.alive_status() and sender.alive_status(); }

void ServerPlayer::join_threads() {
    this->receiver.join();
    this->sender.join();
}

Queue<Msj>& ServerPlayer::get_message_queue() { return this->msj_queue; }
