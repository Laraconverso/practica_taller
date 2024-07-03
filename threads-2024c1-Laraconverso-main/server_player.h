#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include <utility>

#include "common_actions.h"
#include "common_queue.h"
#include "common_socket.h"
#include "server_monitor.h"
#include "server_player_receiver.h"
#include "server_player_sender.h"
#include "server_protocol.h"

class ServerPlayer {
private:
    Socket player_skt;
    Queue<Msj> msj_queue;
    ServerProtocol serverProtocol;
    ServerPlayerReceiver receiver;
    ServerPlayerSender sender;


public:
    /*
     * Constructor
     */
    explicit ServerPlayer(Socket&& skt);

    /*
     * Pone a correr el hilo recibidor y el que envia
     */
    void start();

    /*
     * Detiene la ejecuccion de ambos hilos
     */
    void stop_threads();

    /*
     * Termina la ejecucion de ambos thread el sender y el receiver
     */
    void join_threads();

    bool is_alive();


    /*
     * Retorna una referencia de la queue del player
     */
    Queue<Msj>& get_message_queue();

    /*
     * No permito que se hagan copias
     */
    ServerPlayer(const ServerPlayer&) = delete;
    ServerPlayer& operator=(const ServerPlayer&) = delete;
};

#endif  // SERVER_PLAYER_H
