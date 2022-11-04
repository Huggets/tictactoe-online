#ifndef GAME_HPP
#define GAME_HPP

#include "message.hpp"

#include "grid.hpp"

class Player {
public:
    int getFileDescriptor() const;
    void setFileDescriptor(int fd);

    Cell getCellType() const;
    void setCellType(Cell type);

private:
    int m_fd; // The file descriptor
    Cell m_celltype;
};

class Game {
public:
    void initPlayer1(int fd);
    void initPlayer2(int fd);
    void disconnectPlayers();
    void start();

private:
    Player m_player1;
    Player m_player2;
    Grid m_grid;
    Message m_msg;

    void play(Player& player, Player & opponent);
    void showGrid();
};

#endif // GAME_HPP