#include "grid.hpp"

std::string Grid::cellToString(Cell cell) {
    if (cell == x) return "X";
    else if (cell == o) return "O";
    else return " ";
}

std::string Grid::toString() const {
    return cellToString(m_cells[0]) + "|" + cellToString(m_cells[1]) + "|" + cellToString(m_cells[2]) + "\t1|2|3\n"
        + cellToString(m_cells[3]) + "|" + cellToString(m_cells[4]) + "|" + cellToString(m_cells[5]) + "\t4|5|6\n"
        + cellToString(m_cells[6]) + "|" + cellToString(m_cells[7]) + "|" + cellToString(m_cells[8]) + "\t7|8|9\n";
}

Cell Grid::getCell(int index) const {
    return m_cells[index];
}

void Grid::setCell(int index, Cell content) {
    m_cells[index] = content;
}

Status Grid::win() const {
    if (
        (m_cells[0] == m_cells[1] && m_cells[0] == m_cells[2] && m_cells[0] != blank) ||
        (m_cells[3] == m_cells[4] && m_cells[3] == m_cells[5] && m_cells[3] != blank) ||
        (m_cells[6] == m_cells[7] && m_cells[6] == m_cells[8] && m_cells[6] != blank) ||

        (m_cells[0] == m_cells[3] && m_cells[0] == m_cells[6] && m_cells[0] != blank) ||
        (m_cells[1] == m_cells[4] && m_cells[1] == m_cells[7] && m_cells[1] != blank) ||
        (m_cells[2] == m_cells[5] && m_cells[2] == m_cells[8] && m_cells[2] != blank) ||

        (m_cells[0] == m_cells[4] && m_cells[0] == m_cells[8] && m_cells[0] != blank) ||
        (m_cells[2] == m_cells[4] && m_cells[2] == m_cells[6] && m_cells[2] != blank)
        ) {

        return Status::win;

    } else if (m_cells[0] != blank && m_cells[1] != blank && m_cells[2] != blank &&
        m_cells[3] != blank && m_cells[4] != blank && m_cells[5] != blank &&
        m_cells[6] != blank && m_cells[7] != blank && m_cells[8] != blank) {

        return draw;

    } else {
        return undefined;
    }
}

void Grid::reset() {
    for (int i = 0; i != 9; ++i) {
        m_cells[i] = blank;
    }
}