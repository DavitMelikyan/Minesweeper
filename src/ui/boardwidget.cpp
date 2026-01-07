#include "include/ui/boardwidget.hpp"

BoardWidget::BoardWidget(int rows, int cols, QWidget* parent) : QWidget(parent), m_rows(rows), m_cols(cols) {
    layout = new QGridLayout(this);
    createGrid(rows, cols);
    setLayout(layout);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    // testCellsWithNumbers();
    // testCellsWithStates();
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

// Debug functions

void BoardWidget::testCellsWithNumbers() {
    int testNumbers[] = {1, 2, 3, 4, 5, 6, 7, 8};

    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            m_cells[r][c]->setState(CellState::RevealedNumber, testNumbers[c % 8]);
        }
    }
}

void BoardWidget::testCellsWithStates() {
    CellState testStates[] = {
        CellState::Covered, CellState::Flagged, CellState::RevealedEmpty,
        CellState::RevealedNumber, CellState::RevealedMine, CellState::RevealedWrongFlag
    };

    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            m_cells[r][c]->setState(testStates[c % 6]);
        }
    }
}

