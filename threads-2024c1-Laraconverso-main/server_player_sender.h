#ifndef SERVER_PLAYER_SENDER_H
#define SERVER_PLAYER_SENDER_H

#include <atomic>

#include "common_actions.h"
#include "common_queue.h"
#include "common_thread.h"
#include "server_protocol.h"

class ServerPlayerSender: public Thread {
private:
    ServerProtocol& protocol;
    std::atomic<bool> is_alive;
    Queue<struct Msj>& msjs_to_send;

public:
    /*
     * Constructor del hilo sender, envia los msjs desde su propia queue hasta el cliente.
     */
    explicit ServerPlayerSender(ServerProtocol& protocol, Queue<struct Msj>& player_queue);

    /*
     * Corre el hilo, lee de su propia queue para mandar al cliente.
     */
    void run() override;

    /*
     * Detiene la ejecucion del hilo.
     */
    void kill();

    bool alive_status();

    /*
     * No permito que se hagan copias
     */
    ServerPlayerSender(const ServerPlayerSender&) = delete;
    ServerPlayerSender& operator=(const ServerPlayerSender&) = delete;
};

#endif  // SERVER_PLAYER_SENDER_H
