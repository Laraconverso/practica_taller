#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <utility>

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
     * Envia a traves del socket la accion Atacar. en el formato correspondiente.
     */
    void enviar_msj_ataque();

    /*
     * Realiza la accion Leer <n>
     */
    Msj read_msj();


    /*
     * No permito que se hagan copias
     */
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;
};


#endif  // CLIENT_PROTOCOL_H
