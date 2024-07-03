#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H

#include <atomic>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "common_socket.h"
#include "common_thread.h"
#include "server_game.h"
#include "server_monitor.h"
#include "server_player.h"


class Acceptor: public Thread {
private:
    Socket listener_skt;
    std::atomic<bool> connection_status;
    Monitor& monitor;
    std::list<ServerPlayer*> players;

public:
    /*
     * Constructor del thread aceptador
     */
    explicit Acceptor(const char* port, Monitor& monitor);

    /*
     * Corre el hilo, inicializa la partida y acepta a los jugadores.
     */
    void run() override;

    /*
     * Termina la ejecucion del hilo
     */
    void stop() override;


    /*
     * Borra los jugadores
     */
    void clear_all_players();

    void clean_disconnected_players();


    /*
     * No permito que se hagan copias
     */
    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;
};


#endif  // SERVER_ACCEPTOR_H
