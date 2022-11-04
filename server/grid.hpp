#ifndef GRID_HPP
#define GRID_HPP

#include <string>

enum Cell {
    blank, x, o
};

enum Status {
    undefined, win, draw
};

class Grid {
public:
    static std::string cellToString(Cell cell);

    Cell getCell(int index) const;
    void setCell(int index, Cell content);

    Status win() const;

    void reset();

    std::string toString() const;

private:
    Cell m_cells[9] = {};
};

#endif // GRID_HPP