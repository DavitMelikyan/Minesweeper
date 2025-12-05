#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <QWidget>
#include "mainwindow.hpp"
#include "welcomewindow.hpp"

class GameController : public QWidget
{
    Q_OBJECT
private:
    WelcomeWindow* welcome;
    MainWindow* game;
    GameController(QWidget* parent = nullptr);
    ~GameController();
    void centerWindow(QWidget* window);
private slots:
    void startGame(int rows, int cols, int mines);
    void returnToMenu();
public:
    static GameController& instance();
};

#endif // GAMECONTROLLER_HPP
