#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <string>
#include <vector>

#include "server_game_logic.h"
#include "server_protocol.h"

class Server {
private:
    ServerProtocol serverProtocol;
    ServerGameLogic gameLogic;

    /*
     * Resuelve el stream de inputs enviado por el cliente.
     */
    std::vector<uint8_t> process_msj(const std::vector<enum ActionType>& actions);


public:
    /*
     * Constructor del server
     */
    explicit Server(const std::string& port);

    /*
     * Ejecuta el server
     */
    void execute();

    /*
     * No permito que se hagan copias
     */
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    /*
     * Permito mover objetos (move semantics)
     */
    Server(Server&&) = default;
    Server& operator=(Server&&) = default;
};

#endif  // SERVER_SERVER_H
