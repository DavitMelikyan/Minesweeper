#ifndef BOARDMODEL_HPP
#define BOARDMODEL_HPP

#include "cellmodel.hpp"
#include <vector>
#include <random>
#include <queue>

enum class GameState { NotStarted, Playing, Won, Lost };

class BoardModel {
private:
    std::vector<std::vector<CellModel>> m_cells;
    int m_rows;
    int m_cols;
    int m_mines;
    GameState m_state;
    int frow;
    int fcol;
    int placedMines;
    bool minesPlaced;
    const int dx[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
    const int dy[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
    int revealedCells;
    int flaggedCells;
    bool mineRevealed;
public:
    BoardModel();

    void initializeBoard(int rows, int cols, int mineCount);
    CellModel& getCell(int row, int col);
    int getRows() const;
    int getCols() const;
    int getMineCount() const;
    bool isValidPosition(int row, int col) const;
    void setGameState(GameState state);
    GameState getGameState() const;

    void placeMines(int excludeRow, int excludeCol);
    int getPlacedMineCount() const;
    bool isFirstClick() const;
    void calculateAdjacentCounts();
    void revealCell(int row, int col);
    int getRevealedCount() const;

    bool toggleFlag(int row, int col);
    int getRemainingMineCount() const;
    int getFlaggedCount() const;
    bool isCellFlagged(int row, int col) const;

    bool checkWinCondition() const;
    bool checkLossCondition() const;
    void revealAllMines();
    bool isGameOver() const;

    void resetGame();
    void newGame(int rows, int cols, int mineCount);
};

#endif // BOARDMODEL_HPP
