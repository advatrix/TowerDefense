#include "levelchoicewindow.h"
#include "ui_levelchoicewindow.h"
#include "gamewindow.h"

#include <experimental/filesystem>
#include <QListWidget>
#include <QListWidgetItem>


levelChoiceWindow::levelChoiceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::levelChoiceWindow)
{
    ui->setupUi(this);
    // list = new QListView(this);








}

levelChoiceWindow::~levelChoiceWindow()
{
    delete ui;
}



void levelChoiceWindow::on_loadButton_clicked()
{
    GameWindow* gameWindow = new GameWindow;

    std::string rawText = ui->lineEdit->text().toLocal8Bit().data();


    gameWindow->setLevelName(1);
    gameWindow->show();
    gameWindow->startGame();
}
