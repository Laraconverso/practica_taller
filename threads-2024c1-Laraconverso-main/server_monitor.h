#ifndef SERVER_MONITOR_H
#define SERVER_MONITOR_H

#include <list>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "common_actions.h"
#include "common_queue.h"

// Contiene una lista de clientes
class Monitor {
private:
    std::mutex monitor_mutex;
    std::list<Queue<struct Msj>*> msj_queue;

public:
    /*
     * Constructor del monitor
     */
    Monitor();

    /*
     * Agrego  un jugador a la queue
     */
    void add_player_queue(Queue<struct Msj>* player_queue);

    /*
     * Envio el mismo msj a todos los jugadores de la queue
     */
    void broadcast(const Msj& msj);

    // ~Monitor();

    void clean_all_queues();

    /*
     * Permito mover objetos
     */
    Monitor(Monitor&&) = default;
    Monitor& operator=(Monitor&&) = default;

    /*
     * No permito que se hagan copias
     */
    Monitor(const Monitor&) = delete;
    Monitor& operator=(const Monitor&) = delete;
};

#endif  // SERVER_MONITOR_H
