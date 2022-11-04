#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

#include "message.hpp"

int main(int argc, char ** argv) {
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " hostname port" << std::endl;
        return EXIT_FAILURE;
    }

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;

    try {
        serverAddress.sin_port = htons(std::stoi(argv[2]));
    } catch (std::exception &) {
        std::cerr << "Bad port given" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        struct hostent * addr = gethostbyname(argv[1]);
        memcpy(&serverAddress.sin_addr.s_addr, addr->h_addr, addr->h_length);
    } catch (...) {
        std::cerr << "Bad hostname given" << std::endl;
        exit(EXIT_FAILURE);
    }

    while (connect(socketfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) != 0);

    Message msg;
    int status = 0;

    while (msg.getType() != disconnect && status != -1) {
        std::string inputBuffer;

        status = msg.receive(socketfd);

        if (status > 0) {
            switch (msg.getType()) {
            case echo:
                std::cout << msg.getContent() << std::endl;
                break;

            case opponentturn:
                std::cout << "Your opponent is playing" << std::endl;
                break;

            case yourturn:
                std::cout << "It's your turn. Choose a cell to play: " << std::flush;
                std::cin >> inputBuffer;
                msg.setContent(inputBuffer.c_str());
                msg.send(socketfd);
                break;

            default:
                break;
            }
        }
    }

    close(socketfd);

    return EXIT_SUCCESS;
}