#include "client_client.h"

#include <iostream>

#include "common_actions.h"

Client::Client(const std::string& hostname, const std::string& servname):
        clientProtocol(hostname, servname) {}


void Client::print_msj(const Msj& msj) {
    if (msj.action_type == ActionType::ENEMIGO_MUERTO) {
        std::cout << "Un enemigo ha muerto. " << msj.enemies_alive << " vivo(s) y "
                  << msj.enemies_dead << " muerto(s).\n";
    } else if (msj.action_type == ActionType::ENEMIGO_REVIVE) {
        std::cout << "Un enemigo ha revivido. " << msj.enemies_alive << " vivo(s) y "
                  << msj.enemies_dead << " muerto(s).\n";
    }
}


void Client::execute() {
    std::string command;
    while (std::cin >> command) {
        if (command == ATACAR) {
            this->clientProtocol.enviar_msj_ataque();
        } else if (command == LEER) {
            int cant_mensajes;
            std::cin >> cant_mensajes;
            for (int i = 0; i < cant_mensajes; ++i) {
                Msj msj = this->clientProtocol.read_msj();
                print_msj(msj);
            }
        } else if (command == SALIR) {
            break;
        }
    }
}
