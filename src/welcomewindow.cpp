#include "../headers/welcomewindow.hpp"

WelcomeWindow::WelcomeWindow(QWidget *parent) : QWidget(parent), beginner(nullptr),  intermediate(nullptr), expert(nullptr) {
    setUI();
    setConnections();
}


void WelcomeWindow::setUI() {
    QFile styleFile(":/qss/welcome.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(styleFile.readAll());
    }


    beginner = new QPushButton("Beginner (9x9, 10 mines)", this);
    intermediate = new QPushButton("Intermediate (16x16, 40 mines)",this);
    expert = new QPushButton("Expert (16x30, 99 mines)",this);
    howToPlay = new QPushButton("How to Play", this);
    about = new QPushButton("About", this);
    title = new QLabel("MINESWEEPER", this);
    QLabel* dif = new QLabel("SELECT DIFFICULTY", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(title, 0, Qt::AlignHCenter);
    layout->addWidget(dif, 0, Qt::AlignHCenter);
    layout->addSpacing(15);
    layout->addWidget(beginner, 0, Qt::AlignHCenter);
    layout->addWidget(intermediate, 0, Qt::AlignHCenter);
    layout->addWidget(expert, 0, Qt::AlignHCenter);
    layout->addSpacing(20);
    layout->addWidget(howToPlay, 0, Qt::AlignHCenter);
    layout->addWidget(about, 0, Qt::AlignHCenter);
    layout->addStretch();
    title->setObjectName("titleLabel");
    title->setAlignment(Qt::AlignCenter);
    dif->setObjectName("difLabel");
    dif->setAlignment(Qt::AlignCenter);

    beginner->setMinimumWidth(300);
    intermediate->setMinimumWidth(300);
    expert->setMinimumWidth(300);
    howToPlay->setMinimumWidth(300);
    about->setMinimumWidth(300);
    beginner->setMaximumWidth(400);
    intermediate->setMaximumWidth(400);
    expert->setMaximumWidth(400);
    howToPlay->setMaximumWidth(400);
    about->setMaximumWidth(400);
    beginner->setMinimumHeight(60);
    intermediate->setMinimumHeight(60);
    expert->setMinimumHeight(60);
    howToPlay->setMinimumHeight(60);
    about->setMinimumHeight(60);

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
