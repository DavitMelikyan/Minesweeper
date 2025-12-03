#include "../include/mainwindow.hpp"

MainWindow::MainWindow(int rows, int cols, int mines, QWidget* parent)
    : QMainWindow(parent), m_rows(rows), m_cols(cols), m_mines(mines)
{
    setUI();
    setConnections();
}


void MainWindow::setUI() {
    menuBar = new QMenuBar(this);
    menu = new QMenu("Game", this);
    startNewGame = menu->addAction("New Game");
    changeGameDiff = menu->addAction("Change Difficulty");
    exitGame = menu->addAction("Exit");

    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);


    menuBar->addMenu(menu);
    createStatusPanel();
    layout->addWidget(statusPanel);

    QHBoxLayout* bckLayout = new QHBoxLayout(central);
    backToMenu = new QPushButton("Back to Menu", this);
    backToMenu->setMinimumHeight(40);
    bckLayout->addWidget(backToMenu);

    layout->addLayout(bckLayout);
    layout->addStretch();
    setCentralWidget(central);
    setWindowTitle("Minesweeper");
    setMinimumSize(400, 300);
}


void MainWindow::createStatusPanel() {
    statusPanel = new StatusPanel(this);

    if (m_rows == 9) statusPanel->changeDiff("Beginner");
    else if (m_rows == 16 && m_cols == 16) statusPanel->changeDiff("Intermediate");
    else statusPanel->changeDiff("Expert");
}

void MainWindow::setConnections() {
    connect(startNewGame, &QAction::triggered, [this](){
        newGame();
    });

    connect(changeGameDiff, &QAction::triggered, [this](){
        changeDifficulty();
    });

    connect(exitGame, &QAction::triggered, [this](){
        exit();
    });

    connect(backToMenu, &QPushButton::clicked, [this]() {
        this->hide();
    });
}

void MainWindow::restartGame() {
    statusPanel->updateTimer(0);
    statusPanel->updateMineCount(m_mines);
    statusPanel->setFaceState(GameState::Playing);
}

void MainWindow::changeDifficulty() {

}

void MainWindow::exit() {

}

void MainWindow::newGame() {

}

// StatusPanel Class

StatusPanel::StatusPanel(QWidget* parent) : QWidget(parent) {
    setUI();
    setConnections();
}

void StatusPanel::setUI() {
    mineCounter = new QLCDNumber(3, this);
    timerCounter = new QLCDNumber(3, this);
    restart = new QPushButton("😊", this);
    diffLabel = new QLabel("Beginner", this);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(mineCounter);
    layout->addWidget(timerCounter);
    layout->addWidget(restart);
    layout->addWidget(diffLabel);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    mineCounter->setSegmentStyle(QLCDNumber::Flat);
    mineCounter->display(0);
    timerCounter->setSegmentStyle(QLCDNumber::Flat);
    timerCounter->display(0);
    restart->setMinimumSize(40, 40);
}

void StatusPanel::setConnections() {

}

void StatusPanel::changeDiff(const QString& diff) {
    diffLabel->setText(diff);
}

void StatusPanel::setFaceState(GameState state) {
    if (state == GameState::Playing) restart->setText("😊");
    else if (state == GameState::Won) restart->setText("😎");
    else diffLabel->setText("Lost");
}

void StatusPanel::updateMineCount(int mcount) {
    mineCounter->display(mcount);
}

void StatusPanel::updateTimer(int nseconds) {
    timerCounter->display(nseconds);
}
