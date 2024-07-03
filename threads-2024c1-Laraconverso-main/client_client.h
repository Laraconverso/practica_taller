#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <string>

#include "client_protocol.h"
#include "common_actions.h"

class Client {
private:
    ClientProtocol clientProtocol;

    /*
     * Imprime los mensajes
     */
    void print_msj(const Msj& msj);

public:
    /*
     * Constructor del cliente
     */
    explicit Client(const std::string& hostname, const std::string& servname);

    /*
     * Ejecuto el cliente.
     */
    void execute();

    /*
     * No permito que se hagan copias
     */
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
};

#endif  // CLIENT_CLIENT_H
