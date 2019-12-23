#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGridLayout>

#include "map.h"
#include "interfaceonbottom.h"
#include "interfaceonright.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    QGridLayout* gridLayout = new QGridLayout();
    Map* map = new Map();
    InterfaceOnRight* interfaceOnRight;
    InterfaceOnBottom* interfaceOnBottom;

    void configureInterfaces();
    void setAllConnects();

    void update();

private:
    Ui::Game *ui;
    unsigned int level;

    void configureLayout();

};

#endif // GAME_H
