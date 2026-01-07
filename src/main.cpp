#include "../include/gamewindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow::instance();
    return a.exec();
}
