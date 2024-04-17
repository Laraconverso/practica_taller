#include "server_game_logic.h"

#include <utility>
#include <vector>


// private


std::string ServerGameLogic::combo_checker(std::string& msj) {
    std::string uppercut = "JUMP JUMP HIT";
    std::string sidekick = "HIT DUCK LEFT";
    std::string highkick = "LEFT RIGHT JUMP HIT";
    size_t pos;
    if ((pos = msj.find(uppercut)) != std::string::npos) {
        msj.replace(pos, uppercut.length(), UPPERCUT_W);
        this->cant_actions -= 2;
    } else if ((pos = msj.find(sidekick)) != std::string::npos) {
        msj.replace(pos, sidekick.length(), SIDEKICK_W);
        this->cant_actions -= 2;
    } else if ((pos = msj.find(highkick)) != std::string::npos) {
        msj.replace(pos, highkick.length(), HIGHKICK_W);
        this->cant_actions -= 3;
    }
    return msj;
}

std::string ServerGameLogic::unserialize_msj(const std::vector<ActionType>& vector) {
    std::string result;
    for (ActionType byte: vector) {
        switch (byte) {
            case ActionType::JUMP:
                result.append(JUMP_W);
                this->cant_actions++;
                break;
            case ActionType::RIGHT:
                result.append(RIGHT_W);
                this->cant_actions++;
                break;
            case ActionType::LEFT:
                result.append(LEFT_W);
                this->cant_actions++;
                break;
            case ActionType::DUCK:
                result.append(DUCK_W);
                this->cant_actions++;
                break;
            case ActionType::HIT:
                result.append(HIT_W);
                this->cant_actions++;
                break;
            default:
                break;
        }
        result.append(" ");
    }
    result.erase(result.find_last_of(" "));
    return result;
}

/*
 * Transforma a ascii el vector de acciones escritas en bytes
 */
std::vector<uint8_t> ServerGameLogic::message_parser(const std::string& clean_string) {
    std::vector<uint8_t> ascii_message(clean_string.begin(), clean_string.end());
    return ascii_message;
}

// public

size_t ServerGameLogic::get_cant_actions() const { return this->cant_actions; }

ServerGameLogic::ServerGameLogic(): cant_actions(0) {}
