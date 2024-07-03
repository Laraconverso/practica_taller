#include "server_game.h"

Game::Game(Monitor& monitor):
        monitor(monitor), is_running(true), enemies(5), enemies_alive(5), enemies_dead(0) {}


void Game::print_msj(const Msj& msj) {
    if (msj.action_type == ActionType::ENEMIGO_MUERTO) {
        std::cout << "Un enemigo ha muerto. " << msj.enemies_alive << " vivo(s) y "
                  << msj.enemies_dead << " muerto(s).\n";
    } else if (msj.action_type == ActionType::ENEMIGO_REVIVE) {
        std::cout << "Un enemigo ha revivido. " << msj.enemies_alive << " vivo(s) y "
                  << msj.enemies_dead << " muerto(s).\n";
    }
}

void Game::msj_manager(ActionType& actionType) {
    Msj msj = generate_msj(actionType);
    print_msj(msj);
    this->monitor.broadcast(msj);
}


bool Game::attack_enemies() {
    if (this->enemies_alive > 0) {
        auto enemy_iterator = std::find_if(this->enemies.begin(), this->enemies.end(),
                                           [](const Enemy& enemy) { return enemy.is_alive(); });
        if (enemy_iterator != enemies.end()) {
            enemy_iterator->kill();
            this->enemies_alive--;
            this->enemies_dead++;
            return true;
        }
    }
    return false;
}


bool Game::revive_enemies() {
    bool enemy_revived = false;
    for (Enemy& enemy: enemies) {
        if (!enemy.is_alive()) {
            bool success = enemy.try_revive();
            if (success) {
                this->enemies_dead--;
                this->enemies_alive++;
                enemy_revived = true;
            }
        }
    }
    return enemy_revived;
}

ActionType Game::execute_command(ActionType& command) {
    if (command == ActionType::ATAQUE_CLIENTE) {
        bool exc_success = attack_enemies();
        if (exc_success) {
            return ActionType::ENEMIGO_MUERTO;
        }
    } else if (command == ActionType::ENEMIGO_REVIVE) {
        bool exc_success = revive_enemies();
        if (exc_success) {
            return ActionType::ENEMIGO_REVIVE;
        }
    }
    return ActionType::NULO;
}

Msj Game::generate_msj(const ActionType& action_done) {
    Msj final_msj;
    final_msj.message = ActionType::MSJ_SERVER;
    final_msj.enemies_alive = this->enemies_alive;
    final_msj.enemies_dead = this->enemies_dead;
    final_msj.action_type = action_done;
    return final_msj;
}

void Game::run() {
    try {
        while (is_running) {
            ActionType command;
            bool read_successful = UniqueQueue::read_command(command);
            if (read_successful) {
                ActionType executed_command = execute_command(command);
                if (executed_command != ActionType::NULO) {
                    msj_manager(executed_command);
                }
            }
            ActionType msj_revive = ActionType::ENEMIGO_REVIVE;
            ActionType revived = execute_command(msj_revive);
            if (revived != ActionType::NULO) {
                msj_manager(revived);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
        }
    } catch (const std::exception& err) {
        is_running = false;
        std::cerr << "Something went wrong running the game. Exception: " << err.what() << "\n";
    }
}


void Game::stop() { this->is_running = false; }
