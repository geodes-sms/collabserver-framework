#include "collabclient/Client.h"

#include <cstdlib>
#include <iostream>

#define LOG std::cout << "[LOG]:[" << __TIME__ << "]: "

#define SERVER_IP       "localhost"
#define SERVER_PORT     4242


int main(int argc, char** argv) {
    collab::Client client;
    LOG << "Start example\n";
    LOG << "Connecting to server (" << SERVER_IP << ":" << SERVER_PORT << ")\n";
    bool success = client.connect(SERVER_IP, SERVER_PORT);
    if(success && client.isConnected()) {
        LOG << "Successfully connected\n";
    }
    else {
        LOG << "Unable to connect\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


