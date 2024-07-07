#include "wordscounter.h"

#include <fstream>
#include <string>

#include <string.h>

#define DELIM_WORDS " ,.;:\n"


Wordscounter::Wordscounter(): words(0), state(WordscounterState::STATE_WAITING) {}

size_t Wordscounter::get_words() { return this->words; }

void Wordscounter::process(std::istream& text_file) {
    do {
        char c = text_file.get();
        next_state(c);
    } while (state != STATE_DONE);
}

void Wordscounter::next_state(char c) {
    if (state == STATE_WAITING) {
        if (c == EOF) {
            state = STATE_DONE;
        } else if (strchr(DELIM_WORDS, c) == NULL) {
            state = STATE_WORKING;
        }
    } else if (state == STATE_WORKING) {
        if (c == EOF) {
            state = STATE_DONE;
            words++;
        } else if (strchr(DELIM_WORDS, c) != NULL) {
            words++;
            state = STATE_WAITING;
        }
    }
}
