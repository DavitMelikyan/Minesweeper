#include "include/windows/gamewindow.hpp"

GameWindow::GameWindow(QWidget* parent) : QWidget(parent) {
    QFile f(":/qss/game.qss");
    if (f.open(QFile::ReadOnly | QFile::Text)) {
        qApp->setStyleSheet(QString::fromUtf8(f.readAll()));
        f.close();
    }
    welcome = new WelcomeWindow;
    welcome->show();
    centerWindow(welcome);
    QObject::connect(welcome, &WelcomeWindow::difficultySelected, this, &GameWindow::startGame);
}

GameWindow::~GameWindow() {
    delete game;
    delete welcome;
}

void GameWindow::centerWindow(QWidget* window) {
    if (!window) return;
    const QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - window->width()) / 2;
    int y = (screenGeometry.height() - window->height()) / 2;
    window->move(x, y);
}

GameWindow& GameWindow::instance() {
    static GameWindow instance;
    return instance;
}

void GameWindow::startGame(int rows, int cols, int mines) {
    game = new MainWindow(rows, cols, mines);
    QObject::connect(game, &MainWindow::backRequested, this, &GameWindow::returnToMenu);

    game->show();
    welcome->close();
    centerWindow(game);
}

void GameWindow::returnToMenu() {
    if (game) {
        delete game;
        game = nullptr;
    }
    welcome->show();
    centerWindow(welcome);
}
