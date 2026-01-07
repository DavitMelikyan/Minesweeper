#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <QObject>
#include <QTimer>
#include "include/models/boardmodel.hpp"

class GameController : public QObject
{
    Q_OBJECT
private:
    BoardModel m_board;
    int m_rows;
    int m_cols;
    int m_mines;
    bool m_firstClick;
    QTimer* m_timer;
    int m_seconds = 0;
public:
    explicit GameController(int rows, int cols, int mines);
    const CellModel& getCellState(int row, int col) const;
    int getCellNumber(int row, int col) const;
    GameState getGameState() const;
    void startTimer();
    void stopTimer();
    void resetTimer();
signals:
    void boardUpdated();
    void cellUpdated(int row, int col);
    void gameWon();
    void gameLost();
    void timerUpdated(int seconds);
    void mineCounterUpdated(int remaining);
    void gameStateChanged(GameState state);
public slots:
    void handleCellLeftClick(int row, int col);
    void handleCellRightClick(int row, int col);
    void handleRestart();
    void handleDifficultyChange(int rows, int cols, int mines);
    void onTimerTick();
};

#endif // GAMECONTROLLER_HPP
