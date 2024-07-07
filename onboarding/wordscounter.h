#ifndef __WORDSCOUNTER_H__
#define __WORDSCOUNTER_H__

#include <fstream>
#include <string>

enum WordscounterState { STATE_WAITING, STATE_WORKING, STATE_DONE };

// Tipo wordscounter_t: procesa cantidad de palabras dentro de un archivo.
class Wordscounter {

private:
    size_t words;
    WordscounterState state;

public:
    Wordscounter();

    // Retorna la cantidad de palabras procesadas
    size_t get_words();

    // Procesa el contenido de text_file, contando sus palabras. Pos: si el archivo no se puede
    // abrir devuelve -1 si lo puede abrir devuelve 0
    void process(std::istream& text_file);

    // Compara el caracter leído c y define el nuevo estado.
    void next_state(char c);
};
#endif
