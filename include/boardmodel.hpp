#ifndef BOARDMODEL_HPP
#define BOARDMODEL_HPP

#include "cellmodel.hpp"
#include <vector>
#include <random>

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
};

#endif // BOARDMODEL_HPP
