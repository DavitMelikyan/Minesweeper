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
#include "welcomewindow.hpp"

enum class GameState { Playing, Won, Lost };

class StatusPanel : public QWidget {
    Q_OBJECT
private:
    QLCDNumber* mineCounter;
    QPushButton* restart;
    QLCDNumber* timerCounter;
    QLabel* diffLabel;
    int mines;

    void setUI();
    void setConnections();
public:
    StatusPanel(QWidget* parent = nullptr);
    void setFaceState(GameState state);
    void changeDiff(const QString& diff);
    void updateMineCount(int mcount);
    void updateTimer(int nseconds);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    StatusPanel* statusPanel;
    QMenuBar* menuBar;
    QPushButton* backToMenu;
    QMenu* menu;
    QAction* startNewGame;
    QAction* changeGameDiff;
    QAction* exitGame;
    int m_rows;
    int m_cols;
    int m_mines;

    void setUI();
    void createStatusPanel();
    void setConnections();
signals:
    void backRequested();
private slots:
    void newGame();
    void changeDifficulty();
    void exit();
public:
    MainWindow(int rows, int cols, int mines, QWidget* parent = nullptr);
};
#endif // MAINWINDOW_HPP
