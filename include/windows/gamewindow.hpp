#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "include/windows/mainwindow.hpp"
#include "include/windows/welcomewindow.hpp"

class GameWindow : public QWidget
{
    Q_OBJECT
private:
    WelcomeWindow* welcome;
    MainWindow* game;
    GameWindow(QWidget* parent = nullptr);
    ~GameWindow();
    void centerWindow(QWidget* window);
private slots:
    void startGame(int rows, int cols, int mines);
    void returnToMenu();
public:
    static GameWindow& instance();
};

#endif // GAMEWINDOW_H
