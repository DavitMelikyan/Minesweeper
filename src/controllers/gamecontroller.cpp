#include "include/controllers/gamecontroller.hpp"

GameController::GameController(int rows, int cols, int mines) : QObject(nullptr), m_rows(rows), m_cols(cols), m_mines(mines) {
    m_board.initializeBoard(m_rows, m_cols, m_mines);
}

GameState GameController::getGameState() const {
    return m_board.getGameState();
}

void GameController::handleCellLeftClick(int row, int col) {
    m_board.revealCell(row, col);
    if (m_board.checkWinCondition()) {
        emit gameWon();
        emit gameStateChanged(GameState::Won);
    }
    else if (m_board.checkLossCondition()) {
        emit gameLost();
        emit gameStateChanged(GameState::Lost);
    }
    emit boardUpdated();
    emit cellUpdated(row, col);
}

void GameController::handleCellRightClick(int row, int col) {
    m_board.toggleFlag(row, col);
    if (m_board.checkWinCondition()) {
        emit gameWon();
        emit gameStateChanged(GameState::Won);
    }
    else if (m_board.checkLossCondition()) {
        emit gameLost();
        emit gameStateChanged(GameState::Lost);
    }
    emit boardUpdated();
    emit cellUpdated(row, col);
}

void GameController::handleRestart() {
    m_board.newGame(m_rows, m_cols, m_mines);
    emit timerUpdated(0);
    emit mineCounterUpdated(m_mines);
    emit gameStateChanged(GameState::NotStarted);
    emit boardUpdated();
}

void GameController::handleDifficultyChange(int rows, int cols, int mines) {
    if (m_rows != rows || m_cols != cols) {
        m_rows = rows;
        m_cols = cols;
        m_board.initializeBoard(rows, cols, mines);
    }
    m_mines = mines;
    emit timerUpdated(0);
    emit mineCounterUpdated(m_mines);
    emit gameStateChanged(GameState::NotStarted);
    emit boardUpdated();
}
