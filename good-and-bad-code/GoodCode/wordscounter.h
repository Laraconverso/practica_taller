#ifndef __WORDSCOUNTER_H__
#define __WORDSCOUNTER_H__

#include <fstream>

enum WordscounterState {
    STATE_WAITING_WORD,
    STATE_IN_WORD,
    STATE_FINISHED
};

// Tipo Wordscounter: procesa cantidad de palabras dentro de un archivo.
class Wordscounter {
private:
    size_t words;
    WordscounterState current_state;
    /// Notar como ahora este metodo es privado
    void set_next_state(char c);
public:
    Wordscounter();

    // Retorna la cantidad de palabras procesadas
    /// const correctness
    size_t get_words() const;
    void process(std::istream& text_file);

    ~Wordscounter() = default;
};
#endif
