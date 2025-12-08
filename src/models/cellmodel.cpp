#include "include/cellmodel.hpp"

CellModel::CellModel() : m_hasMine(false), m_adjacentMines(0), m_isRevealed(false), m_isFlagged(false) { }

bool CellModel::hasMine() const {
    return m_hasMine;
}

int CellModel::adjacentMines() const {
    return m_adjacentMines;
}

bool CellModel::isRevealed() const {
    return m_isRevealed;
}

bool CellModel::isFlagged() const {
    return m_isFlagged;
}

void CellModel::setMine(bool b) {
    m_hasMine = b;
}

void CellModel::setAdjacentMines(int mines) {
    m_adjacentMines = mines;
}

void CellModel::setRevealed(bool b) {
    m_isRevealed = b;
}

void CellModel::setFlagged(bool b) {
    m_isFlagged = b;
}
