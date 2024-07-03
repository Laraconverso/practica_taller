#include "client_protocol.h"

#include <netinet/in.h>

#include "common_liberror.h"

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname):
        hostname(hostname), servname(servname), client_skt(hostname.c_str(), servname.c_str()) {}


void ClientProtocol::enviar_msj_ataque() {
    bool was_closed = false;
    std::uint8_t mensaje_ataque = ActionType::ATAQUE_CLIENTE;
    this->client_skt.sendall(&mensaje_ataque, sizeof(uint8_t), &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo enviar el mensaje 'Atacar' desde el client.\n");
    }
}


// formato de mensaje
// 0x06 <enemies alive cnt> <enemies dead cnt> <type event>
/*
 * 0x06 (un byte); <enemies alive cnt> (2 bytes s/signo big endian) <enemies dead cnt> (2 bytes
 * s/signo big endian) <type event> (un byte indicando 0x04 o 0x05)
 */
Msj ClientProtocol::read_msj() {
    Msj read_msj;
    bool was_closed = false;
    this->client_skt.recvall(&read_msj, sizeof(Msj), &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo recibir el msj.\n");
    }
    Msj msj;
    msj.message = read_msj.message;
    msj.enemies_alive = ntohs(read_msj.enemies_alive);
    msj.enemies_dead = ntohs(read_msj.enemies_dead);
    msj.action_type = read_msj.action_type;
    return msj;
}
