#include "server_acceptor.h"

Acceptor::Acceptor(const char* port, Monitor& monitor):
        listener_skt(port), connection_status(true), monitor(monitor), players() {}

void Acceptor::run() {
    try {
        while (connection_status) {
            Socket skt_player = this->listener_skt.accept();
            ServerPlayer* player = new ServerPlayer(std::move(skt_player));
            monitor.add_player_queue(&player->get_message_queue());
            player->start();
            players.push_back(player);
            clean_disconnected_players();
        }
        clear_all_players();
    } catch (const std::exception& err) {
        if (connection_status) {
            std::cerr << "Error occurred running the acceptor: " << err.what() << "\n";
        }
        connection_status = false;
        clear_all_players();
    }
}

void Acceptor::clean_disconnected_players() {
    this->players.remove_if([](ServerPlayer* player) {
        if (!player->is_alive()) {
            player->stop_threads();
            player->join_threads();
            delete player;
            return true;
        }
        return false;
    });
}


void Acceptor::clear_all_players() {
    for (auto* player: this->players) {
        player->stop_threads();
        player->join_threads();
        delete player;
    }
    this->players.clear();
    monitor.clean_all_queues();
}


void Acceptor::stop() {
    this->connection_status = false;
    listener_skt.shutdown(2);
    listener_skt.close();
}
