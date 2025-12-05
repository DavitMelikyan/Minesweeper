#include "../include/cell.hpp"

CellButton::CellButton(int row, int col, QWidget* parent) : QPushButton(parent), m_row(row), m_col(col) {
    setFixedSize(30, 30);
    setStyleSheet("background-color: #C0C0C0;");
}


int CellButton::row() const {
    return m_row;
}

int CellButton::col() const {
    return m_col;
}

void CellButton::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) emit leftClicked(m_row, m_col);
    else if (event->button() == Qt::RightButton) emit rightClicked(m_row, m_col);
    QPushButton::mousePressEvent(event);
}
