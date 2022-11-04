#include "game.hpp"
#include <unistd.h>

int Player::getFileDescriptor() const {
    return m_fd;
}

void Player::setFileDescriptor(int fd) {
    m_fd = fd;
}

Cell Player::getCellType() const {
    return m_celltype;
}

void Player::setCellType(Cell type) {
    m_celltype = type;
}

void Game::initPlayer1(int fd) {
    m_player1.setFileDescriptor(fd);
    m_player1.setCellType(x);
}

void Game::initPlayer2(int fd) {
    m_player2.setFileDescriptor(fd);
    m_player2.setCellType(o);
}

void Game::disconnectPlayers() {
    m_msg.setType(disconnect);
    m_msg.send(m_player1.getFileDescriptor());
    m_msg.send(m_player2.getFileDescriptor());
    close(m_player1.getFileDescriptor());
    close(m_player2.getFileDescriptor());
}

void Game::start() {
    Player * player = &m_player1;
    Player * opponent = &m_player2;
    Player * tmp;

    std::string str;
    m_msg.setType(echo);
    str = "You are the " + Grid::cellToString(m_player1.getCellType()) + ".\n";
    m_msg.setContent(str.c_str());
    m_msg.send(m_player1.getFileDescriptor());
    str = "You are the " + Grid::cellToString(m_player2.getCellType()) + ".\n";
    m_msg.setContent(str.c_str());
    m_msg.send(m_player2.getFileDescriptor());

    showGrid();

    Status gameStatus = undefined;
    while (gameStatus == undefined) {
        play(*player, *opponent);
        showGrid();

        gameStatus = m_grid.win();

        if (gameStatus == draw) {
            m_msg.setType(echo);
            m_msg.setContent("Draw ! No one won...");
            m_msg.send(m_player1.getFileDescriptor());
            m_msg.send(m_player2.getFileDescriptor());
        } else if (gameStatus == win) {
            m_msg.setType(echo);
            m_msg.setContent("You win!");
            m_msg.send(player->getFileDescriptor());
            m_msg.setContent("You loose!");
            m_msg.send(opponent->getFileDescriptor());
        }

        tmp = player;
        player = opponent;
        opponent = tmp;
    }

    m_grid.reset();
}

void Game::showGrid() {
    m_msg.setType(echo);
    m_msg.setContent(m_grid.toString().c_str());
    m_msg.send(m_player1.getFileDescriptor());
    m_msg.send(m_player2.getFileDescriptor());
}

void Game::play(Player & player, Player & opponent) {
    m_msg.setType(opponentturn);
    m_msg.send(opponent.getFileDescriptor());
    m_msg.setType(yourturn);
    m_msg.send(player.getFileDescriptor());

    bool incorrectMove = true;
    while (incorrectMove) {
        bool retry = false;

        m_msg.receive(player.getFileDescriptor());
        std::string input{ m_msg.getContent() };

        try {
            int cellIndex = std::stoi(input) - 1;
            if ((cellIndex < 0 || cellIndex > 8) || m_grid.getCell(cellIndex) != blank) {
                retry = true;
            } else {
                m_grid.setCell(cellIndex, player.getCellType());
                incorrectMove = false;
            }
        } catch (std::exception &) {
            retry = true;
        }

        if (retry) {
            m_msg.setType(echo);
            m_msg.setContent("Your input is incorrect");
            m_msg.send(player.getFileDescriptor());
            m_msg.setType(yourturn);
            m_msg.send(player.getFileDescriptor());
        }
    }
}