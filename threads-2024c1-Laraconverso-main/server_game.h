#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "common_queue.h"
#include "common_thread.h"
#include "server_enemy.h"
#include "server_game_unique_queue.h"
#include "server_monitor.h"

#define SLEEP_TIME 200

class Game: public Thread {
private:
    Monitor& monitor;
    bool is_running;
    std::vector<Enemy> enemies;
    std::uint16_t enemies_alive;
    std::uint16_t enemies_dead;


    /*
     * Simula una iteracion
     */
    bool iterate();

    /*
     * Recorre la lista de enmigos y ataca el primero vivo.
     */
    bool attack_enemies();

    /*
     * Recorre la lista de enemigos y revive al primero muerto.
     */
    bool revive_enemies();

    //    /*
    //     * Lee de la unica queue del game
    //     */
    //    enum ActionType read_command();

    /*
     * Ejecuta un comando y retorna el valor de la accion ejecutada
     */
    enum ActionType execute_command(ActionType& command);

    /*
     * Genera un mensaje dados los datos que recibe.
     */
    struct Msj generate_msj(const ActionType& actionType);

    /*
     * Imprime el msj desde el lado del servidor
     */
    void print_msj(const Msj& msj);

    void msj_manager(ActionType& actionType);

public:
    /*
     * Constructor de una Partida
     */
    explicit Game(Monitor& monitor);


    /*
     * Corre la logica del juego ( el gameloop)
     */
    void run() override;


    /*
     * Finaliza la partida
     */
    void stop() override;


    /*
     * No permito que se hagan copias
     */
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};

#endif  // SERVER_GAME_H
