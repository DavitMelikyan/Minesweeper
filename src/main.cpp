#include "../include/gamecontroller.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameController::instance();
    return a.exec();
}
