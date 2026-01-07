#include "include/controllers/gamecontroller.hpp"
#include <QtCore/qdebug.h>

GameController::GameController(int rows, int cols, int mines) : QObject(nullptr), m_rows(rows), m_cols(cols), m_mines(mines), m_firstClick(false) {
    m_board.initializeBoard(m_rows, m_cols, m_mines);
}

bool GameController::getCellRevealed(int row, int col) const {
    return m_board.getCell(row, col).isRevealed();
}

int GameController::getCellNumber(int row, int col) const {
    return m_board.getCell(row, col).adjacentMines();
}

GameState GameController::getGameState() const {
    return m_board.getGameState();
}

void GameController::handleCellLeftClick(int row, int col) {
    if (m_board.isGameOver()) return;
    if (!m_board.isValidPosition(row, col)) return;
    if (!m_firstClick) {
        m_board.placeMines(row, col);
        m_firstClick = true;
    }
    m_board.revealCell(row, col);
    if (m_board.checkWinCondition()) {
        qDebug() << "Game Won";
        emit gameWon();
        emit gameStateChanged(GameState::Won);
    }
    else if (m_board.checkLossCondition()) {
        qDebug() << "Game Lost";
        emit gameLost();
        emit gameStateChanged(GameState::Lost);
    }
    qDebug() << "Board Updated by left click";
    emit boardUpdated();
    qDebug() << "Cell at " << row << ", " << col << " updated";
    emit cellUpdated(row, col);
}

void GameController::handleCellRightClick(int row, int col) {
    if (m_board.isGameOver()) return;
    if (!m_board.isValidPosition(row, col)) return;
    m_board.toggleFlag(row, col);
    qDebug() << "Board Updated by right click";
    emit boardUpdated();
    qDebug() << "Cell at " << row << ", " << col << " updated";
    emit cellUpdated(row, col);
    qDebug() << "Mine count updated to " << m_board.getRemainingMineCount();
    emit mineCounterUpdated(m_board.getRemainingMineCount());
}

void GameController::handleRestart() {
    m_board.newGame(m_rows, m_cols, m_mines);
    qDebug() << "Timer updated by restarting the game";
    emit timerUpdated(0);
    qDebug() << "Mine count updated to " << m_mines << " by restarting the game";
    emit mineCounterUpdated(m_mines);
    emit gameStateChanged(GameState::NotStarted);
    qDebug() << "Board Updated by restarting the game";
    emit boardUpdated();
    m_firstClick = false;
}

void GameController::handleDifficultyChange(int rows, int cols, int mines) {
    if (m_rows != rows || m_cols != cols) {
        m_rows = rows;
        m_cols = cols;
        m_board.newGame(rows, cols, mines);
    }
    m_mines = mines;
    qDebug() << "Timer updated by changing the difficulty";
    emit timerUpdated(0);
    qDebug() << "Mine count updated to " << m_mines << " by changing the difficulty";
    emit mineCounterUpdated(m_mines);
    emit gameStateChanged(GameState::NotStarted);
    qDebug() << "Board Updated by changing the difficulty";
    emit boardUpdated();
    m_firstClick = false;
}
