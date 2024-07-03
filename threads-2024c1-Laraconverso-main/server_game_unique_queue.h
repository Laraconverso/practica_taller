#ifndef SERVER_GAME_UNIQUE_QUEUE_H
#define SERVER_GAME_UNIQUE_QUEUE_H

#include <mutex>

#include "common_actions.h"
#include "common_queue.h"

class UniqueQueue {
private:
    static std::mutex mutex;
    static Queue<enum ActionType> command_queue;

public:
    /*
     * Agrega un comando a la queue
     */
    static void add_command(enum ActionType& command);

    /*
     * lee un comando de la queue
     */
    static bool read_command(enum ActionType& command);

    /*
     * Permito mover objetos
     */
    UniqueQueue(UniqueQueue&&) = default;
    UniqueQueue& operator=(UniqueQueue&&) = default;

    /*
     * No permito que se hagan copias
     */
    UniqueQueue(const UniqueQueue&) = delete;
    UniqueQueue& operator=(const UniqueQueue&) = delete;
};

#endif  // SERVER_GAME_UNIQUE_QUEUE_H
