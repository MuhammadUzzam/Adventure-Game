#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Player {
public:
    int coins;
    int lives;
    QVector<QString> party;

    Player() : coins(10), lives(3) {}
    void addCoins(int);
    void loseCoins(int);
    void loseLife();
    void gainLife();
    bool hasWarrior();
    void addToParty(QString);
    bool checkWinCondition();
    bool checkLoseCondition();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnVillage_clicked();
    void on_btnTavern_clicked();
    void on_btnForest_clicked();
    void on_btnMountains_clicked();
    void on_btnTreasure_clicked();

private:
    Ui::MainWindow *ui;
    Player player;
    void updateStats();
    void logEvent(const QString &, const QString &);
    void checkGameOver();
    void setBackground(const QString &imagePath);

};
#endif // MAINWINDOW_H
