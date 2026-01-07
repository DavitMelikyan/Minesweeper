#include "include/ui/boardwidget.hpp"

BoardWidget::BoardWidget(GameController* controller, int rows, int cols, QWidget* parent) : QWidget(parent), m_rows(rows), m_cols(cols), m_controller(controller) {
    layout = new QGridLayout(this);
    createGrid(rows, cols);
    setLayout(layout);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
}

void BoardWidget::createGrid(int rows, int cols) {
    for (auto& row : m_cells) {
        for (auto* button : row) {
            if (button) layout->removeWidget(button);
            delete button;
        }
    }

    m_cells.clear();
    m_rows = rows;
    m_cols = cols;
    m_cells.resize(rows);

    for (int r = 0; r < m_rows; ++r) {
        m_cells[r].resize(cols);
        for (int c = 0; c < cols; ++c) {
            CellButton* button = new CellButton(r, c, this);
            layout->addWidget(button, r, c);
            m_cells[r][c] = button;

            connect(button, &CellButton::leftClicked, this, &BoardWidget::handleLeftClick);
            connect(button, &CellButton::rightClicked, this, &BoardWidget::handleRightClick);
        }
    }
}

void BoardWidget::handleLeftClick(int row, int col) {
    qDebug() << "Left click at " << row << "," << col;
    emit leftClicked(row, col);
}

void BoardWidget::handleRightClick(int row, int col) {
    qDebug() << "Right click at " << row << "," << col;
    emit rightClicked(row, col);
}

void BoardWidget::updateCell(int row, int col) {
    CellButton* cell = m_cells[row][col];

    const GameState gameState = m_controller->getGameState();
    const CellModel& cModel = m_controller->getCellState(row, col);

    if (gameState == GameState::Lost) {
        if (cModel.hasMine() && !cModel.isFlagged()) cell->setState(CellState::RevealedMine);
        else if (!cModel.hasMine() && cModel.isFlagged()) cell->setState(CellState::RevealedWrongFlag);
        else if (cModel.isRevealed()) {
            if (m_controller->getCellNumber(row, col) == 0) cell->setState(CellState::RevealedEmpty);
            else cell->setState(CellState::RevealedNumber, m_controller->getCellNumber(row, col));
        }
        else cell->setState(CellState::Covered);
    } else if (!cModel.isRevealed()) {
        if (cModel.isFlagged()) cell->setState(CellState::Flagged);
        else cell->setState(CellState::Covered);
    } else {
        if (m_controller->getCellState(row, col).hasMine()) cell->setState(CellState::RevealedMine);
        else {
            if (m_controller->getCellNumber(row, col) == 0) cell->setState(CellState::RevealedEmpty);
            else cell->setState(CellState::RevealedNumber, m_controller->getCellNumber(row, col));
        }
    }
}

void BoardWidget::refreshBoard() {
    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            updateCell(r, c);
        }
    }
}

