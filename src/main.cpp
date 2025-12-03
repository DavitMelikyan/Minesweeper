#include "../headers/headers.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeWindow welcome;
    welcome.show();
    MainWindow w;
    w.show();
    return a.exec();
}
