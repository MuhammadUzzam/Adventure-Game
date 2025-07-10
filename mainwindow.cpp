#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <ctime>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->logArea->setStyleSheet("color: white; background-color: rgba(0, 0, 0, 150); font-family: Consolas;");
    srand(time(0));
    ui->logArea->setReadOnly(true);
    updateStats();
}

void MainWindow::setBackground(const QString &imagePath) {
    QString style = QString("QMainWindow { background-image: url(%1); background-repeat: no-repeat; background-position: center; }").arg(imagePath);
    this->setStyleSheet(style);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void Player::addCoins(int amount) { coins += amount; }
void Player::loseCoins(int amount) { coins = std::max(0, coins - amount); }
void Player::loseLife() { lives--; }
void Player::gainLife() { lives++; }
bool Player::hasWarrior() { return party.contains("Warrior"); }
void Player::addToParty(QString name) {
    if (!hasWarrior()) party.append(name);
}
bool Player::checkWinCondition() { return coins >= 50 && hasWarrior(); }
bool Player::checkLoseCondition() { return lives <= 0; }

void MainWindow::updateStats() {
    ui->labelStats->setText("Coins: " + QString::number(player.coins) +
                            " | Lives: " + QString::number(player.lives) +
                            " | Party: " + (player.hasWarrior() ? "Warrior" : "None"));
}

void MainWindow::logEvent(const QString &location, const QString &decision) {
    QString line = "Location: " + location + " | Action: " + decision +
                   " | Coins: " + QString::number(player.coins) +
                   " | Lives: " + QString::number(player.lives);
    ui->logArea->append(line);

    QFile file("game_log.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << line << "\n";
        file.close();
    }
}

void MainWindow::checkGameOver() {
    if (player.checkLoseCondition()) {
        QMessageBox::critical(this, "Game Over", "You lost all lives!");
        qApp->quit();
    } else if (player.checkWinCondition()) {
        QMessageBox::information(this, "Victory!", "You won the game!");
        qApp->quit();
    }
}

void MainWindow::on_btnVillage_clicked()
{
    setBackground("E:/27-04-2025/UZZAM WORK/Summer Activity/Activity 6 qt/AdventureGameQt/images/village.jpg");
    ui->labelStatus->setText("You are in the Village.");
    logEvent("Village", "Visited");
}


void MainWindow::on_btnTavern_clicked()
{
    setBackground("E:/27-04-2025/UZZAM WORK/Summer Activity/Activity 6 qt/AdventureGameQt/images/tavern.jpg");
    QString msg;
    int cost = rand() % 2 == 0 ? 0 : 10;

    if (player.hasWarrior()) {
        msg = "You already have the Warrior.";
    } else if (player.coins >= cost) {
        player.loseCoins(cost);
        player.addToParty("Warrior");
        msg = "Recruited Warrior for " + QString::number(cost) + " coins.";
    } else {
        msg = "Not enough coins to recruit Warrior.";
    }

    ui->labelStatus->setText(msg);
    logEvent("Tavern", msg);
    updateStats();
    checkGameOver();
}


void MainWindow::on_btnForest_clicked()
{
    setBackground("E:/27-04-2025/UZZAM WORK/Summer Activity/Activity 6 qt/AdventureGameQt/images/forest.jpg");
    int result = rand() % 2;
    QString msg;
    if (result == 0) {
        player.addCoins(20);
        msg = "Found 20 coins in a chest!";
    } else {
        player.loseLife();
        msg = "Trap! Lost a life.";
    }

    ui->labelStatus->setText(msg);
    logEvent("Forest", msg);
    updateStats();
    checkGameOver();
}


void MainWindow::on_btnMountains_clicked()
{
    setBackground("E:/27-04-2025/UZZAM WORK/Summer Activity/Activity 6 qt/AdventureGameQt/images/mountains.jpg");
    int result = rand() % 2;
    QString msg;
    if (result == 0) {
        player.loseLife();
        msg = "Rain! Slipped and lost a life.";
    } else {
        player.addCoins(20);
        msg = "Sunny! Found 20 coins.";
    }

    ui->labelStatus->setText(msg);
    logEvent("Mountains", msg);
    updateStats();
    checkGameOver();
}


void MainWindow::on_btnTreasure_clicked()
{
    setBackground("E:/27-04-2025/UZZAM WORK/Summer Activity/Activity 6 qt/AdventureGameQt/images/treasure.jpg");
    QString msg;
    if (player.checkWinCondition()) {
        msg = "You Win!";
    } else {
        msg = "You need 50 coins and the Warrior!";
    }
    ui->labelStatus->setText(msg);
    logEvent("Treasure Room", msg);
    updateStats();
    checkGameOver();
}

