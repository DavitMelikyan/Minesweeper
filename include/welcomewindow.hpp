#ifndef WELCOMEWINDOW_HPP
#define WELCOMEWINDOW_HPP

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QFile>
#include <QMessageBox>

class WelcomeWindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton* beginner;
    QPushButton* intermediate;
    QPushButton* expert;
    QPushButton *howToPlay;
    QPushButton *about;
    QLabel* title;
    QLabel* dif;

    void setUI();
    void setConnections();
signals:
    void difficultySelected(int rows, int cols, int mines);
public:
    WelcomeWindow(QWidget *parent = nullptr);
};

#endif // WELCOMEWINDOW_HPP
