#include "include/windows/mainwindow.hpp"

MainWindow::MainWindow(int rows, int cols, int mines, QWidget* parent)
    : QMainWindow(parent), m_rows(rows), m_cols(cols), m_mines(mines), fClick(false)
{
    setWindowIcon(QIcon(":/icons/gameicon.png"));
    setObjectName("GameWindow");
    setUI();
    setConnections();
    setWindowSize();
}


void MainWindow::setUI() {
    menuBar = new QMenuBar(this);
    menu = new QMenu("Game", this);
    startNewGame = menu->addAction("New Game");
    changeGameDiff = menu->addAction("Change Difficulty");
    exitGame = menu->addAction("Close the game");


    helpMenu = new QMenu("Help", this);
    helpAbout = helpMenu->addAction("Info about game");

    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);


    menuBar->addMenu(menu);
    menuBar->addMenu(helpMenu);
    createStatusPanel();
    layout->addWidget(statusPanel);

    board = new BoardWidget(m_rows, m_cols, this);
    board->setEnabled(true);
    layout->addWidget(board, 1);

    setMenuBar(menuBar);

    QHBoxLayout* bckLayout = new QHBoxLayout();
    backToMenu = new QPushButton("Back to Menu", this);
    backToMenu->setMinimumHeight(40);
    backToMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bckLayout->addStretch();
    bckLayout->addWidget(backToMenu);
    bckLayout->addStretch();


    layout->addLayout(bckLayout);
    layout->addStretch();
    setCentralWidget(central);
    setWindowTitle("Minesweeper");
}


void MainWindow::createStatusPanel() {
    statusPanel = new StatusPanel(this);

    if (m_rows == 9) statusPanel->changeDiff("Beginner");
    else if (m_rows == 16 && m_cols == 16) statusPanel->changeDiff("Intermediate");
    else statusPanel->changeDiff("Expert");

    statusPanel->updateMineCount(m_mines);
}

void MainWindow::setConnections() {
    connect(startNewGame, &QAction::triggered, this, &MainWindow::newGame);
    connect(changeGameDiff, &QAction::triggered, this, &MainWindow::changeDifficulty);
    connect(exitGame, &QAction::triggered, this, &MainWindow::exitApp);


    connect(backToMenu, &QPushButton::clicked, [this]() {
        emit backRequested();
    });

    connect(helpAbout, &QAction::triggered, []() {
        QMessageBox::information(nullptr, "How to Play","Reveal all cells without hitting mines.\nLeft-click to reveal cell.\nRight-click to place flags.");
    });

    connect(statusPanel, &StatusPanel::restartRequested, this, &MainWindow::newGame);


    connect(board, &BoardWidget::leftClicked, this, &MainWindow::handleLeftClick);
    connect(board, &BoardWidget::rightClicked, this, &MainWindow::handleRightClick);
}

void MainWindow::setWindowSize() {
    if (m_rows == 9 && m_cols == 9) setMinimumSize(380, 420);
    else if (m_rows == 16 && m_cols == 16) setMinimumSize(560, 650);
    else setMinimumSize(880, 700);
}

void MainWindow::changeDifficulty() {
    QStringList difficulties = { "Beginner", "Intermediate", "Expert" };
    bool ok;
    QString diff = QInputDialog::getItem(this, "Select Difficulty","Difficulty:", difficulties, 0, false, &ok);
    if (!ok || diff.isEmpty()) return;

    if (diff == "Beginner") {
        m_rows = 9;
        m_cols = 9;
        m_mines = 10;
    } else if (diff == "Intermediate") {
        m_rows = 16;
        m_cols = 16;
        m_mines = 40;
    } else if (diff == "Expert") {
        m_rows = 16;
        m_cols = 30;
        m_mines = 99;
    }

    statusPanel->changeDiff(diff);
    board->createGrid(m_rows, m_cols);

    setWindowSize();
    newGame();
}

void MainWindow::exitApp() {
    qApp->quit();
}

void MainWindow::newGame() {
    statusPanel->setFaceState(GameState::Playing);
    statusPanel->resetTimer();
    statusPanel->stopTimer();
    statusPanel->updateMineCount(m_mines);
    fClick = false;
}

void MainWindow::handleLeftClick(int row, int col) {
    if (!fClick) {
        fClick = true;
        statusPanel->startTimer();
    }
}
void MainWindow::handleRightClick(int row, int col) {
    if (!fClick) {
        fClick = true;
        statusPanel->startTimer();
    }
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
    timer = new QTimer(this);
    timer->setInterval(1000);

    mineCounter->setSegmentStyle(QLCDNumber::Flat);
    timerCounter->setSegmentStyle(QLCDNumber::Flat);
    mineCounter->display("000");
    timerCounter->display("000");
    restart->setMinimumSize(55, 40);

    mineCounter->setObjectName("mineCounter");
    timerCounter->setObjectName("timerCounter");
    restart->setObjectName("restartButton");
    diffLabel->setObjectName("diffLabel");

    mineCounter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    timerCounter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    restart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    diffLabel->setMinimumWidth(80);
    diffLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);


    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    layout->addWidget(mineCounter, 2);
    layout->addStretch(1);
    layout->addWidget(restart, 2);
    layout->addStretch(1);
    layout->addWidget(timerCounter, 2);
    layout->addWidget(diffLabel, 1);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void StatusPanel::setConnections() {
    connect(restart, &QPushButton::clicked, [this]() {
        emit restartRequested();
    });
    connect(timer, &QTimer::timeout, this, &StatusPanel::updateTimer);
}

void StatusPanel::changeDiff(const QString& diff) {
    diffLabel->setText(diff);
    if (diff == "Beginner") mines = 10;
    else if (diff == "Intermediate") mines = 40;
    else mines = 99;

    mineCounter->display(QString("%1").arg(mines, 3, 10, QLatin1Char('0')));
}

void StatusPanel::setFaceState(GameState state) {
    if (state == GameState::Playing) {
        restart->setText("😊");
        restart->setProperty("state", "playing");
    }
    else if (state == GameState::Won) {
        restart->setText("😎");
        restart->setProperty("state", "won");
    }
    else {
        restart->setText("💀");
        restart->setProperty("state", "lost");
    }

    restart->style()->unpolish(restart);
    restart->style()->polish(restart);
    restart->update();
}

void StatusPanel::updateMineCount(int mcount) {
    mineCounter->display(QString("%1").arg(mcount, 3, 10, QLatin1Char('0')));
}

void StatusPanel::updateTimer() {
    timerCounter->display(QString("%1").arg(m_seconds++, 3, 10, QLatin1Char('0')));
}

void StatusPanel::startTimer() {
    m_seconds = 0;
    timer->start();
}

void StatusPanel::stopTimer() {
    timer->stop();
}

void StatusPanel::resetTimer() {
    m_seconds = 0;
    updateTimer();
}
