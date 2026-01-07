#include "include/windows/welcomewindow.hpp"

WelcomeWindow::WelcomeWindow(QWidget *parent) : QWidget(parent), beginner(nullptr),  intermediate(nullptr), expert(nullptr) {
    setWindowIcon(QIcon(":/icons/gameicon.png"));
    setObjectName("GameWindow");
    setUI();
    setConnections();
}


void WelcomeWindow::setUI() {
    beginner = new QPushButton("Beginner (9x9, 10 mines)", this);
    intermediate = new QPushButton("Intermediate (16x16, 40 mines)",this);
    expert = new QPushButton("Expert (16x30, 99 mines)",this);
    howToPlay = new QPushButton("How to Play", this);
    about = new QPushButton("About", this);
    title = new QLabel("MINESWEEPER", this);
    dif = new QLabel("SELECT DIFFICULTY", this);

    title->setObjectName("titleLabel");
    title->setAlignment(Qt::AlignCenter);
    dif->setObjectName("difLabel");
    dif->setAlignment(Qt::AlignCenter);

    beginner->setProperty("difficulty", true);
    intermediate->setProperty("difficulty", true);
    expert->setProperty("difficulty", true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setSpacing(18);

    layout->addStretch(1);
    layout->addWidget(title);
    layout->addWidget(dif);
    layout->addSpacing(8);

    layout->addWidget(beginner);
    layout->addWidget(intermediate);
    layout->addWidget(expert);

    layout->addSpacing(20);
    layout->addWidget(howToPlay);
    layout->addWidget(about);
    layout->addStretch(2);

    QList<QPushButton*> buttons = { beginner, intermediate, expert, howToPlay, about };
    for (auto btn : buttons) {
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btn->setMinimumHeight(50);
        btn->setMinimumWidth(220);
    }

    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    dif->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    title->setMinimumHeight(48);
    dif->setMinimumHeight(32);

    setMinimumSize(480, 360);
    setWindowTitle("Minesweeper");
}



void WelcomeWindow::setConnections() {
    connect(beginner, &QPushButton::clicked, [this]() {
        emit difficultySelected(9, 9, 10);
    });

    connect(intermediate, &QPushButton::clicked, this, [this]() {
        emit difficultySelected(16, 16, 40);
    });

    connect(expert, &QPushButton::clicked, this, [this]() {
        emit difficultySelected(16, 30, 99);
    });

    connect(howToPlay, &QPushButton::clicked, this, []() {
        QMessageBox::information(nullptr, "How to Play","Reveal all cells without hitting mines.\nLeft-click to reveal cell.\nRight-click to place flags.");
    });

    connect(about, &QPushButton::clicked, this, []() {
        QMessageBox::information(nullptr, "About", "Minesweeper Project\nCreated by Davit Melikyan");
    });
}
