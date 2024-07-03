#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include <utility>
#include <vector>

#include "common_actions.h"
#include "common_socket.h"

class ServerProtocol {
private:
    Socket server_skt;
    bool was_closed;

public:
    /*
     * Constructor del protocolo del lado del server
     */
    explicit ServerProtocol(Socket& player_skt);

    /*
     * Leector de msj de clientes
     */
    std::uint8_t read_msj();

    /*
     * Envia el mensaje
     */
    void send_msj(Msj& msj);


    /*
     * No permito que se hagan copias
     */
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;
};

#endif  // SERVER_PROTOCOL_H
