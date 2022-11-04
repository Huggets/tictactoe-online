#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#include "message.hpp"

#include "game.hpp"

int main(int argc, char ** argv) {
    int localfd;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientAdressLen = sizeof(clientAddress);

    Game game;

    localfd = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(10678);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(localfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(localfd, 5);

    while (true) {
        Message msg;
        msg.setType(echo);
        msg.setContent("You are connected!");
        int player1, player2;

        std::cout << "Waiting for players..." << std::endl;

        player1 = accept(localfd, (struct sockaddr *)&clientAddress, &clientAdressLen);
        game.initPlayer1(player1);
        std::cout << "Player 1 connected." << std::endl;
        msg.send(player1);

        player2 = accept(localfd, (struct sockaddr *)&clientAddress, &clientAdressLen);
        game.initPlayer2(player2);
        std::cout << "Player 2 connected.\nGame started!" << std::endl;
        msg.send(player2);

        game.start();

        std::cout << "Game ended. Disconnecting players..." << std::endl;
        game.disconnectPlayers();
    }

    close(localfd);

    return 0;
}