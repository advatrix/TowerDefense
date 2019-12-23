#include "gamewindow.h"
#include "ui_gamewindow.h"


#include <QGridLayout>
#include <QLabel>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}


void GameWindow::startGame() {
    game = new TD::GameManager(this->levelName);

    QGridLayout* grid = new QGridLayout;


    for (int i = 0; i < game->getCells().size(); i++) {
        for (int j = 0; j < game->getCells()[0].size(); j++)
        {
            grid->addWidget(new QLabel("A", this), i, j);

        }
    }

    setLayout(grid);

}
