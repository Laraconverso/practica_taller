#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include <vector>

#include "common_actions.h"
#include "common_socket.h"

class ServerProtocol {

private:
    const std::string server_port;
    Socket server_skt;

    /*
     * Acepta la conexion del socket
     */
    Socket accept_connection();

public:
    /*
     * Constructor del protocolo del lado del servidor.
     * Recibe el puerto que debe escuchar.
     */
    explicit ServerProtocol(const std::string& port);

    /*
     * Inicializador de la comunicación del servidor con el cliente a traves del socket.
     */
    void initialize_socket();

    /*
     * Procesa el msj del cliente
     */
    std::vector<enum ActionType> receive_message(bool* connection_status);

    /*
     *  Envia un string con las acciones realizadas con el sgte formato:
     *  - 2 bytes sin signo en formato big endian, indicando el largo del string.
     *  - La tira de bytes del string(en ascii), sin contar el terminador de palabra (‘\0’).
     */
    void send_performed_actions(std::vector<uint8_t>& performed_actions);

    /*
     * No permito que se hagan copias
     */
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    /*
     * Permito mover objetos (move semantics)
     */
    ServerProtocol(ServerProtocol&&) = default;
    ServerProtocol& operator=(ServerProtocol&&) = default;
};

#endif  // SERVER_PROTOCOL_H
