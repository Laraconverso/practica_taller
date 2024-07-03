#ifndef COMMON_ACTIONS_H
#define COMMON_ACTIONS_H

#include <cstdint>

// comandos del cliente
#define ATACAR "Atacar"
#define LEER "Leer"
#define SALIR "Salir"
#define C_QUIT "q"

#include <stdlib.h>

// acciones
enum ActionType {
    ATAQUE_CLIENTE = 0x03,
    MSJ_SERVER = 0x06,
    ENEMIGO_MUERTO = 0x04,
    ENEMIGO_REVIVE = 0x05,
    NULO = 0x11
};

// estructura del mensaje
struct Msj {
    std::uint8_t message;
    std::uint16_t enemies_alive;
    std::uint16_t enemies_dead;
    std::uint8_t action_type;
} __attribute__((packed));

#endif  // COMMON_ACTIONS_H
