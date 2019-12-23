#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "../../TowerDefenseLib/TowerDefenseStaticLib/TowerDefenseLib.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    inline void setLevelName(unsigned int name) { levelName = name; }

    void startGame();

private:
    Ui::GameWindow *ui;
    unsigned int levelName;
    TD::GameManager* game;
};

#endif // GAMEWINDOW_H
