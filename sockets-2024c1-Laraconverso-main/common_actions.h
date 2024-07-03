#ifndef COMMON_ACTIONS_H
#define COMMON_ACTIONS_H
#define ERROR 1;
#define SUCCESS 0;

// Utilizo _w dado que defino como constante la palabra
#define NOP_W "NOP"
#define JUMP_W "JUMP"
#define RIGHT_W "RIGHT"
#define LEFT_W "LEFT"
#define DUCK_W "DUCK"
#define HIT_W "HIT"
#define UPPERCUT_W "UPPERCUT"
#define SIDEKICK_W "SIDEKICK"
#define HIGHKICK_W "HIGHKICK"

enum ActionType : uint8_t { NOP, JUMP, RIGHT, LEFT, DUCK, HIT, UPPERCUT, SIDEKICK, HIGHKICK };

#endif  // COMMON_ACTIONS_H
