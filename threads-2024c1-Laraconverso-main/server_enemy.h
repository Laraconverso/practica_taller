#ifndef SERVER_ENEMY_H
#define SERVER_ENEMY_H

#include <atomic>

#define REVIVAL_ITERATION 5;

class Enemy {
private:
    bool living_status;
    std::atomic<std::size_t> iterations;

public:
    /*
     * Constructor del enemigo, inicializa booleano living_status en true.
     */
    Enemy();

    /*
     * Revive el enemigo (booleano a true)
     */
    bool try_revive();

    /*
     * Mata el enemigo (booleano a false)
     */
    bool kill();

    /*
     * Getter del booleano living_status
     */
    bool is_alive() const;

    /*
     * No permito que se hagan copias
     */
    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;
};

#endif  // SERVER_ENEMY_H
