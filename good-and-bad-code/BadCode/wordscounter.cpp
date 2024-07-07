#include "wordscounter.h"
#include <string>
#include <string.h>
#include <fstream>

#define DELIM_WORDS " ,.;:\n"

Wordscounter::Wordscounter() : words(0), current_state(WordscounterState::STATE_WAITING_WORD) {}

size_t Wordscounter::get_words() {
    return this->words;
}

void Wordscounter::process(std::istream& text_file) {
    do {
        char c = text_file.get();
        set_next_state( c);
    } while (current_state != 2);
}

void Wordscounter::set_next_state(char c) {
    if(current_state == 0) {
        if(c == EOF)
        { 
            current_state = STATE_FINISHED;
        } 
        else if (strchr(DELIM_WORDS, c) == NULL) 
            current_state = STATE_IN_WORD;
        
    } else if (current_state== 1){
        if ( c == EOF ) { 
            current_state = STATE_FINISHED;
            words++;
        } else if ( strchr(DELIM_WORDS, c) != NULL) {
            words++;
            current_state = STATE_WAITING_WORD;
        }
    }


}
