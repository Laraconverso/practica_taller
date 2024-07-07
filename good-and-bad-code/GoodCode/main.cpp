#include <string>
#include <iostream>
#include <fstream>
#include "wordscounter.h"

#define SUCCESS 0
#define ERROR 1
#define FILE_ARG argv[1]

int main(int argc, char* argv[]) {
    /// Wordscounter pasa a estar en el stack 
    /// (no habia necesidad de instanciarlo en el heap).
    Wordscounter counter;
    if (argc > 1) {
        /// Inicializamos la instancia de ifstream en el scope que lo usa 
        /// Como con Wordscounter, se alloca la instancia en el stack. 
        /// Internamente, ifstream se encarga de abrir el archivo.
        std::ifstream input(FILE_ARG);
        if (!input) {
            return ERROR;
        }
        counter.process(input);
        /// Al irse de scope, el destructor de ifstream libera los recursos 
        /// std::ifstream y toda la stdlib C++>=11 es RAII
    } else {
        counter.process(std::cin);
    }
    size_t words = counter.get_words();
    std::cout << words << std::endl;
    return SUCCESS;
}
