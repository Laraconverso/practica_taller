#ifndef SERVER_PLAYER_RECEIVER_H
#define SERVER_PLAYER_RECEIVER_H

#include <atomic>

#include "common_thread.h"
#include "server_protocol.h"

class ServerPlayerReceiver: public Thread {
private:
    ServerProtocol& protocol;
    std::atomic<bool> is_alive;

    /*
     * Procesa los comandos recibidos
     */
    enum ActionType process_command(const uint8_t& msj);

public:
    /*
     * Constructor del thread que se encarga de recibir los mensajes de los jugadores y agregarlos
     * a la unica queue del gameloop.
     */
    explicit ServerPlayerReceiver(ServerProtocol& protocol);

    /*
     * Funcion principal del hilo, recibe los comandos de los jugadores y los agrega a la queue
     * unica del gameloop.
     */
    void run() override;

    /*
     * Detiene la ejecucion del hilo.
     */
    void kill();

    /*
     * Retorna el estado
     */
    bool alive_status();


    /*
     * No permito que se hagan copias
     */
    ServerPlayerReceiver(const ServerPlayerReceiver&) = delete;
    ServerPlayerReceiver& operator=(const ServerPlayerReceiver&) = delete;
};

#endif  // SERVER_PLAYER_RECEIVER_H
