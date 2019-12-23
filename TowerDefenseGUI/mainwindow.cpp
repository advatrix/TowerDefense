#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Tower Defense"));
    createStartMenuInterior();
    aboutWindow = nullptr;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createStartMenuInterior() {

}

void MainWindow::on_quitButton_clicked()
{
    this->close();
}

void MainWindow::on_aboutButton_clicked()
{
    aboutWindow = new About(this);
    aboutWindow->show();

}

void MainWindow::on_startButton_clicked()
{
    startOptionsWindow = new class::startOptionsWindow(this);
    startOptionsWindow->show();
}
