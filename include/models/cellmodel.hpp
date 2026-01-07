#ifndef CELLMODEL_HPP
#define CELLMODEL_HPP

class CellModel {
private:
    bool m_hasMine;
    int m_adjacentMines;
    bool m_isRevealed;
    bool m_isFlagged;
public:
    CellModel();
    bool hasMine() const;
    int adjacentMines() const;
    bool isRevealed() const;
    bool isFlagged() const;
    void setMine(bool b);
    void setAdjacentMines(int mines);
    void setRevealed(bool b);
    void setFlagged(bool b);
};

#endif // CELLMODEL_HPP
