#include "include/controllers/gamecontroller.hpp"
#include <QtCore/qdebug.h>

GameController::GameController(int rows, int cols, int mines) : QObject(nullptr), m_rows(rows), m_cols(cols), m_mines(mines), m_firstClick(false), m_timer(new QTimer(this)), m_seconds(0) {
    m_board.initializeBoard(m_rows, m_cols, m_mines);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &GameController::onTimerTick);
}

const CellModel& GameController::getCellState(int row, int col) const {
    return m_board.getCell(row, col);
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
        startTimer();
        emit gameStateChanged(GameState::Playing);
    }
    m_board.revealCell(row, col);
    if (m_board.checkWinCondition()) {
        qDebug() << "Game Won";
        stopTimer();
        emit gameWon();
        emit gameStateChanged(GameState::Won);
    }
    else if (m_board.checkLossCondition()) {
        qDebug() << "Game Lost";
        stopTimer();
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
    resetTimer();
    qDebug() << "Mine count updated to " << m_mines << " by restarting the game";
    emit mineCounterUpdated(m_mines);
    emit gameStateChanged(GameState::NotStarted);
    qDebug() << "Board Updated by restarting the game";
    emit boardUpdated();
    m_firstClick = false;
}

void GameController::handleDifficultyChange(int rows, int cols, int mines) {
    m_rows = rows;
    m_cols = cols;
    m_mines = mines;
    m_board.newGame(rows, cols, mines);

    qDebug() << "Timer updated by changing the difficulty";
    resetTimer();
    qDebug() << "Mine count updated to " << m_mines << " by changing the difficulty";
    emit mineCounterUpdated(m_mines);
    emit gameStateChanged(GameState::NotStarted);
    qDebug() << "Board Updated by changing the difficulty";
    emit boardUpdated();
    m_firstClick = false;
}

void GameController::startTimer() {
    if (!m_timer->isActive()) m_timer->start();
}

void GameController::stopTimer() {
    if (m_timer->isActive()) m_timer->stop();
}

void GameController::resetTimer() {
    stopTimer();
    m_seconds = 0;
    emit timerUpdated(0);
}

void GameController::onTimerTick() {
    ++m_seconds;
    emit timerUpdated(m_seconds);
}

