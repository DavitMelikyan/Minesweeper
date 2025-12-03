#include "../include/headers.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeWindow welcome;
    welcome.show();
    QObject::connect(&welcome, &WelcomeWindow::difficultySelected,[&](int rows, int cols, int mines) {
        MainWindow *game = new MainWindow(rows, cols, mines);
        game->show();
        welcome.close();
    });
    return a.exec();
}
