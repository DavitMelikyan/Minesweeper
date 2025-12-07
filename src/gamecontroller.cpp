#include "../include/gamecontroller.hpp"

GameController::GameController(QWidget* parent) : QWidget(parent) {
    QFile f(":/qss/game.qss");
    if (f.open(QFile::ReadOnly | QFile::Text)) {
        qApp->setStyleSheet(QString::fromUtf8(f.readAll()));
        f.close();
    }
    welcome = new WelcomeWindow;
    welcome->show();
    centerWindow(welcome);
    QObject::connect(welcome, &WelcomeWindow::difficultySelected, this, &GameController::startGame);
}

GameController::~GameController() {
    delete game;
    delete welcome;
}

void GameController::centerWindow(QWidget* window) {
    if (!window) return;
    const QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - window->width()) / 2;
    int y = (screenGeometry.height() - window->height()) / 2;
    window->move(x, y);
}

GameController& GameController::instance() {
    static GameController instance;
    return instance;
}

void GameController::startGame(int rows, int cols, int mines) {
    game = new MainWindow(rows, cols, mines);
    QObject::connect(game, &MainWindow::backRequested, this, &GameController::returnToMenu);

    game->show();
    welcome->close();
    centerWindow(game);
}

void GameController::returnToMenu() {
    if (game) {
        delete game;
        game = nullptr;
    }
    welcome->show();
    centerWindow(welcome);
}
