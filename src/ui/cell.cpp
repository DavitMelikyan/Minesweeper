#include "include/ui/cell.hpp"

CellButton::CellButton(int row, int col, QWidget* parent) : QPushButton(parent), m_row(row), m_col(col) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setState(CellState::Covered);
    m_state = CellState::Covered;
}


int CellButton::row() const {
    return m_row;
}

int CellButton::col() const {
    return m_col;
}

CellState CellButton::getState() const {
    return m_state;
}

void CellButton::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) emit leftClicked(m_row, m_col);
    else if (event->button() == Qt::RightButton) emit rightClicked(m_row, m_col);
    QPushButton::mousePressEvent(event);
}

void CellButton::setState(CellState st, int number) {
    setText("");
    if (st == CellState::Covered) setProperty("cellState", "covered");
    else if (st == CellState::Flagged) {
        setProperty("cellState", "flagged");
        setText(QString::fromUtf8("🚩"));
    }
    else if (st == CellState::RevealedEmpty) {
        setProperty("cellState", "revealedEmpty");
        setText("");
    }
    else if (st == CellState::RevealedNumber) {
        setProperty("cellState", "revealedNumber");
        setProperty("number", QString::number(number));
        setText(QString::number(number));
    }
    else if (st == CellState::RevealedMine) {
        setProperty("cellState", "revealedMine");
        setText(QString::fromUtf8("💣"));
    }
    else if (st == CellState::RevealedWrongFlag) {
        setProperty("cellState", "revealedWrongFlag");
        setText(QString::fromUtf8("🚩✖"));
    }

    m_state = st;
    style()->unpolish(this);
    style()->polish(this);
    update();
}
