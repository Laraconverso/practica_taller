#include "server_monitor.h"


Monitor::Monitor() {}

void Monitor::add_player_queue(Queue<Msj>* player_queue) {
    std::unique_lock<std::mutex> lock(this->monitor_mutex);
    this->msj_queue.push_back(player_queue);
}

void Monitor::broadcast(const Msj& msj) {
    std::unique_lock<std::mutex> lock(this->monitor_mutex);
    for (auto& queue: this->msj_queue) {
        queue->try_push(msj);
    }
}

// Monitor::~Monitor() {}

void Monitor::clean_all_queues() { this->msj_queue.clear(); }
