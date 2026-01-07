#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QLCDNumber>
#include <QMenuBar>
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include "include/ui/boardwidget.hpp"
#include "include/controllers/gamecontroller.hpp"

class StatusPanel : public QWidget {
    Q_OBJECT
private:
    QLCDNumber* mineCounter;
    QPushButton* restart;
    QLCDNumber* timerCounter;
    QLabel* diffLabel;
    QTimer* timer;
    int mines = 0;
    int m_seconds = 0;

    void setUI();
    void setConnections();
signals:
    void restartRequested();
public:
    StatusPanel(QWidget* parent = nullptr);
    void setFaceState(GameState state);
    void changeDiff(const QString& diff);
    void updateMineCount(int mcount);
    void updateTimer();
    void startTimer();
    void resetTimer();
    void stopTimer();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    StatusPanel* statusPanel;
    QMenuBar* menuBar;
    QMenu* helpMenu;
    QPushButton* backToMenu;
    QMenu* menu;
    QAction* startNewGame;
    QAction* changeGameDiff;
    QAction* exitGame;
    QAction* helpAbout;
    BoardWidget* board;
    GameController* gameController;
    int m_rows;
    int m_cols;
    int m_mines;
    bool fClick;

    void setUI();
    void createStatusPanel();
    void setConnections();
    void setWindowSize();
signals:
    void backRequested();
private slots:
    void handleLeftClick(int row, int col);
    void handleRightClick(int row, int col);
    void newGame();
    void changeDifficulty();
    void exitApp();
public:
    MainWindow(int rows, int cols, int mines, QWidget* parent = nullptr);
};
#endif // MAINWINDOW_HPP
