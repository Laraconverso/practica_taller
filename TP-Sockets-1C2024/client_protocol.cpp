#include "client_protocol.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include <netinet/in.h>
#include <string.h>

#include "common_liberror.h"

// public methods

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname):
        hostname(hostname), servname(servname), client_skt(hostname.c_str(), servname.c_str()) {}


void ClientProtocol::send_processed_msj(const std::vector<ActionType>& msj) {
    bool was_closed = false;
    int cant_bytes = this->client_skt.sendall(msj.data(), msj.size(), &was_closed);
    if ((cant_bytes < 0) || (was_closed)) {
        throw LibError(errno, "No se pudo enviar el mensaje desde el client");
    }
}

std::vector<uint8_t> ClientProtocol::receive_server_msj() {
    bool was_closed = false;
    uint16_t size;
    int recv_bytes = this->client_skt.recvall(&size, sizeof(uint16_t), &was_closed);
    if (recv_bytes <= 0 || was_closed) {
        throw LibError(errno, "No se pudo recibir el mensaje con los bytes desde el client");
    }
    size = ntohs(size);
    was_closed = false;
    std::vector<uint8_t> buff(size);
    this->client_skt.recvall(buff.data(), size, &was_closed);
    return buff;
}
