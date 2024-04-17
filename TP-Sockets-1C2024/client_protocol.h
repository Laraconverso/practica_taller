#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>

#include "common_actions.h"
#include "common_socket.h"

class ClientProtocol {
private:
    const std::string hostname;
    const std::string servname;
    Socket client_skt;

public:
    /*
     * Constructor del protocolo del lado del cliente.
     * Recibe la ip o host y el puerto o servicio a donde conectar.
     */
    explicit ClientProtocol(const std::string& hostname, const std::string& servname);

    /*
     * Envia el mensaje (la cadena de bytes) al server.
     */
    void send_processed_msj(const std::vector<enum ActionType>& msj);

    /*
     * Recibe el mensaje enviado desde el server
     */
    std::vector<uint8_t> receive_server_msj();

    /*
     * No permito que se hagan copias
     */
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    /*
     * Permito mover objetos (move semantics)
     */
    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;
};

#endif  // CLIENT_PROTOCOL_H
