#include "server_protocol.h"

#include <iostream>

#include <netinet/in.h>

ServerProtocol::ServerProtocol(Socket& player_skt):
        server_skt(std::move(player_skt)), was_closed(false) {}

uint8_t ServerProtocol::read_msj() {
    uint8_t recv_msj;
    this->server_skt.recvall(&recv_msj, sizeof(uint8_t), &was_closed);
    if (was_closed) {
        return 0;
    }
    return recv_msj;
}


// formato de mensaje  0x06 <enemies alive cnt> <enemies dead cnt> <type event>
/*
 * 0x06 (un byte); <enemies alive cnt> (2 bytes s/signo big endian) <enemies dead cnt> (2 bytes
 * s/signo big endian) <type event> (un byte indicando 0x04 o 0x05)
 * Ej: 06 0004 0001 04
 */
void ServerProtocol::send_msj(Msj& msj) {
    if (was_closed) {
        return;
    }
    Msj msj_to_send;
    msj_to_send.message = msj.message;
    msj_to_send.enemies_alive = htons(msj.enemies_alive);
    msj_to_send.enemies_dead = htons(msj.enemies_dead);
    msj_to_send.action_type = msj.action_type;
    this->server_skt.sendall(&msj_to_send, sizeof(Msj), &was_closed);
}
