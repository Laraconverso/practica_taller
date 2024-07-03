
#include <exception>
#include <iostream>

#include "server_server.h"

#define ERROR 1;
#define SUCCESS 0;

int main(int argc, char* argv[]) {
    try {
        if (argc == 2) {
            std::string port = std::string(argv[1]);
            Server server(port);
            server.execute();
            return SUCCESS;
        } else {
            std::cerr << "Bad program call. Expected " << argv[0] << "<port>\n";
            return ERROR;
        }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return ERROR;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return ERROR;
    }
}
