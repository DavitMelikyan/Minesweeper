#include "../include/headers.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeWindow welcome;
    welcome.show();
    MainWindow *game = nullptr;
    QObject::connect(&welcome, &WelcomeWindow::difficultySelected,[&](int rows, int cols, int mines) {
        game = new MainWindow(rows, cols, mines);

        QObject::connect(game, &MainWindow::backRequested,[&](){
            welcome.show();
            game->hide();
            delete game;
        });
        game->show();
        welcome.close();
    });
    return a.exec();
}
