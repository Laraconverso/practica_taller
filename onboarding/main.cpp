#include <fstream>
#include <iostream>
#include <string>

#include "wordscounter.h"

#define SUCCESS 0
#define ARGS argv[1]
#define ERROR 1

int main(int argc, char* argv[]) {
    Wordscounter counter;
    if (argc > 1) {
        std::ifstream input(ARGS);
        if (!input) {
            return ERROR;
        }
        counter.process(input);
    } else {
        counter.process(std::cin);
    }
    size_t words = counter.get_words();
    std::cout << words << std::endl;
    return SUCCESS;
}
