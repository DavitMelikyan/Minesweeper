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
#include <QFile>

enum class GameState { Playing, Won, Lost };

class StatusPanel : public QWidget {
    Q_OBJECT
private:
    QLCDNumber* mineCounter;
    QPushButton* restart;
    QLCDNumber* timerCounter;
    QLabel* diffLabel;
    int mines = 0;

    void setUI();
    void setConnections();
signals:
    void restartRequested();
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
    QMenu* helpMenu;
    QPushButton* backToMenu;
    QMenu* menu;
    QAction* startNewGame;
    QAction* changeGameDiff;
    QAction* exitGame;
    QAction* helpAbout;
    int m_rows;
    int m_cols;
    int m_mines;

    void setUI();
    void createStatusPanel();
    void setConnections();
    void setWindowSize();
signals:
    void backRequested();
private slots:
    void newGame();
    void changeDifficulty();
    void exitApp();
public:
    MainWindow(int rows, int cols, int mines, QWidget* parent = nullptr);
};
#endif // MAINWINDOW_HPP
