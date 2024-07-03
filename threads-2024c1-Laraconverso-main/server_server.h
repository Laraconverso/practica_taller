#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <string>

#include "server_protocol.h"

class Server {
private:
    const char* port;

public:
    /*
     * Constructor del server
     */
    explicit Server(const char* port);

    /*
     * Ejecuta el server, leyendo la entrada estandar hasta que se encuentre con 'q'(C_QUIT)
     */
    void execute();

    /*
     * No permito que se hagan copias
     */
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
};

#endif  // SERVER_SERVER_H
