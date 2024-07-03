#include "server_game_unique_queue.h"

std::mutex UniqueQueue::mutex;
Queue<enum ActionType> UniqueQueue::command_queue;


void UniqueQueue::add_command(ActionType& command) {
    std::unique_lock<std::mutex> lock(mutex);
    command_queue.try_push(command);
}

bool UniqueQueue::read_command(ActionType& command) {
    std::unique_lock<std::mutex> lock(mutex);
    bool successful = command_queue.try_pop(command);
    return successful;
}
