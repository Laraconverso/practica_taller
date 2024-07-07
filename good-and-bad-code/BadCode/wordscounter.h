#ifndef __WORDSCOUNTER_H__
#define __WORDSCOUNTER_H__

#include <string>
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
public: 
    Wordscounter();

    // Retorna la cantidad de palabras procesadas
    size_t get_words();

    // Procesa el contenido de text_file, contando sus palabras. Pos: si el archivo no se puede abrir devuelve -1 si lo puede abrir devuelve 0
    void process(std::istream& text_file);

    // Compara el caracter leído c contra DELIM_WORDS y define el nuevo estado.
    void set_next_state( char c);
};

#endif
