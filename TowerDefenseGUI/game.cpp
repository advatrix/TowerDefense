#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    configureLayout();
    map->create();
    gridLayout->addWidget(map, 0, 0);
}

Game::~Game()
{
    delete ui;
}


void Game::configureLayout() {
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);

    setLayout(gridLayout);
}

void Game::configureInterfaces() {
    interfaceOnRight = new InterfaceOnRight();
    gridLayout->addWidget(interfaceOnRight, 0, 1);


    interfaceOnBottom = new InterfaceOnBottom();
    gridLayout->addWidget(interfaceOnBottom, 1, 0, 1, 2);
}

void Game::setAllConnects() {
    interfaceOnRight->setAllConnects();
}

void update() {
    interfaceOnBottom->update();
}

