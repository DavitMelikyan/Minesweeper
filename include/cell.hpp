#ifndef CELL_HPP
#define CELL_HPP

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QStyle>

enum class CellState { Covered, Flagged, RevealedEmpty, RevealedNumber, RevealedMine, RevealedWrongFlag };

class CellButton : public QPushButton
{
    Q_OBJECT
public:
    CellButton(int row, int col, QWidget* parent = nullptr);
    int row() const;
    int col() const;
    void mousePressEvent(QMouseEvent* event) override;
    void setState(CellState st, int number = 0);
signals:
    void leftClicked(int row, int col);
    void rightClicked(int row, int col);
private:
    int m_row;
    int m_col;

};

#endif // CELL_HPP
