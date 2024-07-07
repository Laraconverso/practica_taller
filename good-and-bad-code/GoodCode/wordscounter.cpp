#include "wordscounter.h"
#include <string>
#include <string_view>
#include <fstream>


/// reemplazo de macros por un tipo propio de C++ con bajo overhead
static bool in_delim_words(char c) {
    /// Aca cambiamos el #define por un construct de mayor nivel
    /// Es tipado y que no agrega overhead considerable
    /// Este pequeño cambio otorga una API de mayor nivel que el header string.h
    /// Aprovechen las herramientas del lenguaje!

    /// https://en.cppreference.com/w/cpp/string/basic_string_view
    /// https://en.cppreference.com/w/cpp/language/constexpr

    static constexpr std::string_view delim_words = " ,.;:\n";
    return delim_words.find(c) != std::string::npos;
}

Wordscounter::Wordscounter()
: words(0), current_state(WordscounterState::STATE_WAITING_WORD) {}

/// Const correctness: sabemos que no vamos a modificar al objeto
/// Agregar const previene que lo modifiquemos inadvertidamente
size_t Wordscounter::get_words() const {
    return this->words;
}

void Wordscounter::process(std::istream& text_file) {
    do {
        char c = text_file.get();
        set_next_state(c);
    } while (current_state != STATE_FINISHED);
}

void Wordscounter::set_next_state(char c) {
    if (current_state == STATE_WAITING_WORD) {
        if (c == EOF) { 
            current_state = STATE_FINISHED;
        } else if (!in_delim_words(c)) {
            current_state = STATE_IN_WORD;
        }
    } else if (current_state == STATE_IN_WORD) {
        if (c == EOF) {
            current_state = STATE_FINISHED;
            ++words;
        } else if (in_delim_words(c)) {
            ++words;
            current_state = STATE_WAITING_WORD;
        }
    }
}

