#ifndef BOARDWIDGET_HPP
#define BOARDWIDGET_HPP

#include <QWidget>
#include <QGridLayout>
#include <vector>
#include "include/cell.hpp"

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    BoardWidget(int rows, int cols, QWidget* parent = nullptr);

    void createGrid(int rows, int cols);
    CellButton* cellAt(int row, int col) const;
private slots:
    void handleLeftClick(int row, int col);
    void handleRightClick(int row, int col);
private:
    std::vector<std::vector<CellButton*>> m_cells;
    int m_rows;
    int m_cols;
    QGridLayout* layout;

    void testCellsWithNumbers();
    void testCellsWithStates();
};

#endif // BOARDWIDGET_HPP
