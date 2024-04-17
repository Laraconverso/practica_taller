#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <string>
#include <vector>

#include "client_protocol.h"

class Client {
private:
    ClientProtocol clientProtocol;

    /*
     * Convierte el vector de ascii a string
     */
    void revert_ascii(const std::vector<uint8_t>& msj);

    /*
     * Cada palabra se asocia a un valor de 1 byte sin signo.
     * retorna una cadena de bytes, cada uno 1 byte sin signo, agregandole un NOP al final.
     */
    std::vector<enum ActionType> serialize_msj(const std::string& msj);

public:
    /*
     * Constructor del Client
     */
    explicit Client(const std::string& hostname, const std::string& servname);

    /*
     * Ejecuta el Client
     */
    void execute(const std::string& message);

    /*
     * No permito que se hagan copias
     */
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    /*
     * Permito mover objetos (move semantics)
     */
    Client(Client&&) = default;
    Client& operator=(Client&&) = default;
};

#endif  // CLIENT_CLIENT_H
