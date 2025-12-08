#include "include/boardmodel.hpp"

BoardModel::BoardModel() : m_state(GameState::NotStarted), frow(-1), fcol(-1), placedMines(0), minesPlaced(false) {}


void BoardModel::initializeBoard(int rows, int cols, int mineCount) {
    if (rows <= 0 || cols <= 0) return;
    m_cells.clear();
    m_rows = rows;
    m_cols = cols;
    m_mines = mineCount;
    m_state = GameState::NotStarted;
    m_cells.resize(rows);
    for (int r = 0; r < m_rows; ++r) m_cells[r].resize(cols);
    placedMines = 0;
    frow = -1;
    fcol = -1;
    minesPlaced = false;
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

void BoardModel::placeMines(int excludeRow, int excludeCol) {
    if (!isFirstClick()) return;
    int count = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rRow(0, m_rows - 1);
    std::uniform_int_distribution<int> rCol(0, m_cols - 1);
    if (m_mines > m_rows * m_cols - 1) m_mines = m_rows * m_cols - 1;
    while (count < m_mines) {
        int i = rRow(gen);
        int j = rCol(gen);
        if (i == excludeRow && j == excludeCol) continue;
        if (m_cells[i][j].hasMine()) continue;
        m_cells[i][j].setMine(true);
        ++count;
    }
    placedMines = count;
    frow = excludeRow;
    fcol = excludeCol;
    minesPlaced = true;
}

int BoardModel::getPlacedMineCount() const {
    return placedMines;
}

bool BoardModel::isFirstClick() const {
    return !minesPlaced;
}
