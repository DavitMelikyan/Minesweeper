#include "include/boardmodel.hpp"

BoardModel::BoardModel() : m_state(GameState::NotStarted), frow(-1), fcol(-1), placedMines(0), minesPlaced(false), revealedCells(0), flaggedCells(0), mineRevealed(false) {}


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
    revealedCells = 0;
    flaggedCells = 0;
    mineRevealed = false;
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
    int minesToPlace = std::min(m_mines, m_rows * m_cols - 1);
    while (count < minesToPlace) {
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
    calculateAdjacentCounts();
}

int BoardModel::getPlacedMineCount() const {
    return placedMines;
}

bool BoardModel::isFirstClick() const {
    return !minesPlaced;
}

void BoardModel::calculateAdjacentCounts() {
    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            if (m_cells[r][c].hasMine()) continue;
            int count = 0;
            for (int i = 0; i < 8; ++i) {
                int ri = r + dx[i];
                int ci = c + dy[i];
                if (!isValidPosition(ri, ci)) continue;
                if (m_cells[ri][ci].hasMine()) ++count;
            }
            m_cells[r][c].setAdjacentMines(count);
        }
    }
}

void BoardModel::revealCell(int row, int col) {
    if (isGameOver()) return;
    if (!isValidPosition(row, col)) return;
    if (m_cells[row][col].isRevealed() || m_cells[row][col].isFlagged()) return;
    if (isFirstClick()) {
        placeMines(row, col);
        m_state = GameState::Playing;
    }
    m_cells[row][col].setRevealed(true);
    ++revealedCells;
    if (m_cells[row][col].hasMine()) {
        m_state = GameState::Lost;
        mineRevealed = true;
        revealAllMines();
        return;
    } else if (m_cells[row][col].adjacentMines() > 0) {
        if (checkWinCondition()) m_state = GameState::Won;
        return;
    } else {
        std::queue<std::pair<int, int>> q;
        q.push({row, col});
        std::vector<std::vector<bool>> queued (m_rows, std::vector<bool>(m_cols, false));
        queued[row][col] = true;
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            m_cells[r][c].setRevealed(true);
            if (m_cells[r][c].adjacentMines() == 0) {
                for (int i = 0; i < 8; ++i) {
                    int ri = r + dx[i];
                    int ci = c + dy[i];
                    if (!isValidPosition(ri, ci) || m_cells[ri][ci].isFlagged() || m_cells[ri][ci].isRevealed()) continue;
                    m_cells[ri][ci].setRevealed(true);
                    ++revealedCells;

                    if (m_cells[ri][ci].adjacentMines() > 0) continue;

                    if (!queued[ri][ci]) {
                        queued[ri][ci] = true;
                        q.push({ri,ci});
                    }
                }
            }
        }
        if (checkWinCondition()) m_state = GameState::Won;
    }
}

int BoardModel::getRevealedCount() const {
    return revealedCells;
}

bool BoardModel::toggleFlag(int row, int col) {
    if (isGameOver()) return false;
    if (!isValidPosition(row, col)) return false;
    if (m_cells[row][col].isRevealed()) return false;
    if (m_cells[row][col].isFlagged()) {
        m_cells[row][col].setFlagged(false);
        --flaggedCells;
    } else {
        m_cells[row][col].setFlagged(true);
        ++flaggedCells;
    }
    return true;
}

int BoardModel::getRemainingMineCount() const {
    return m_mines - flaggedCells;
}

int BoardModel::getFlaggedCount() const {
    return flaggedCells;
}

bool BoardModel::isCellFlagged(int row, int col) const {
    if (!isValidPosition(row, col)) return false;
    return m_cells[row][col].isFlagged();
}

bool BoardModel::checkWinCondition() const {
    return m_rows * m_cols - m_mines == revealedCells;
}

bool BoardModel::checkLossCondition() const {
    return mineRevealed;
}

void BoardModel::revealAllMines() {
    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            if (m_cells[r][c].hasMine() && !m_cells[r][c].isFlagged()) m_cells[r][c].setRevealed(true);
            else if (!m_cells[r][c].hasMine() && m_cells[r][c].isFlagged()) m_cells[r][c].setRevealed(true);
        }
    }
}

bool BoardModel::isGameOver() const {
    return (m_state == GameState::Won || m_state == GameState::Lost);
}
