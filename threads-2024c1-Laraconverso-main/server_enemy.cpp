#include "server_enemy.h"

Enemy::Enemy(): living_status(true), iterations(0) {}

bool Enemy::try_revive() {
    if (iterations == 15 && !is_alive()) {
        this->living_status = true;
        return true;
    }
    iterations++;
    return false;
}

bool Enemy::is_alive() const { return this->living_status; }

bool Enemy::kill() {
    if (is_alive()) {
        this->living_status = false;
        this->iterations = 0;
        return true;
    }
    return false;
}
