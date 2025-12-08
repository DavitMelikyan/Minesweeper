#include "include/boardmodel.hpp"

BoardModel::BoardModel() : m_state(GameState::NotStarted) {}


void BoardModel::initializeBoard(int rows, int cols, int mineCount) {
    if (rows <= 0 || cols <= 0) return;
    m_cells.clear();
    m_rows = rows;
    m_cols = cols;
    m_mines = mineCount;
    m_state = GameState::NotStarted;
    m_cells.resize(rows);
    for (int r = 0; r < m_rows; ++r) m_cells[r].resize(cols);
}

CellModel& BoardModel::getCell(int row, int col) {
    if (!isValidPosition(row, col)) throw std::out_of_range("Invalid cell");
    return m_cells[row][col];
}

int BoardModel::getRows() const {
    return m_rows;
}

int BoardModel::getCols() const {
    return m_cols;
}

int BoardModel::getMineCount() const {
    return m_mines;
}

bool BoardModel::isValidPosition(int row, int col) const {
    return (row >= 0 && col >= 0 && row < m_rows && col < m_cols);
}

void BoardModel::setGameState(GameState state) {
    m_state = state;
}

GameState BoardModel::getGameState() const {
    return m_state;
}
