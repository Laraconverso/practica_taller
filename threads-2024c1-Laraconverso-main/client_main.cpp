#include <exception>
#include <fstream>
#include <iostream>

#include "client_client.h"
#define ERROR 1;
#define SUCCESS 0;


int main(int argc, char* argv[]) {
    try {
        if (argc < 1) {
            std::cerr << "Bad program call. Expected " << argv[0] << " <hostname> <servicename> \n";
            return ERROR;
        }
        std::string hostname = std::string(argv[1]);
        std::string servname = std::string(argv[2]);
        Client client(hostname, servname);
        client.execute();
        return SUCCESS;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return ERROR;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return ERROR;
    }
}
