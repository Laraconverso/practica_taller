#ifndef SERVER_GAME_LOGIC_H
#define SERVER_GAME_LOGIC_H

#include <string>
#include <vector>

#include "common_actions.h"

class ServerGameLogic {
private:
    size_t cant_actions;

public:
    ServerGameLogic();

    /*
     * obtendo la cantidad de acciones
     */
    size_t get_cant_actions() const;

    /*
     * Deserializa la acciones recividas desde el client.
     * Transforma el byte en la accion correspondiente.
     */
    std::string unserialize_msj(const std::vector<enum ActionType>& vector);

    /*
     * Transforma a ascii el vector de acciones escritas en bytes
     */
    std::vector<uint8_t> message_parser(const std::string& clean_string);

    /*
     * Evalua el string recivido y chequea si tiene algun combo de acciones.
     */
    std::string combo_checker(std::string& msj);

    /*
     * No permito que se hagan copias
     */
    ServerGameLogic(const ServerGameLogic&) = delete;
    ServerGameLogic& operator=(const ServerGameLogic&) = delete;

    /*
     * Permito mover objetos (move semantics)
     */
    ServerGameLogic(ServerGameLogic&&) = default;
    ServerGameLogic& operator=(ServerGameLogic&&) = default;
};


#endif  // SERVER_GAME_LOGIC_H
