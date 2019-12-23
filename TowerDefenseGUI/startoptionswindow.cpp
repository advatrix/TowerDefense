#include "startoptionswindow.h"
#include "ui_startoptionswindow.h"

startOptionsWindow::startOptionsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::startOptionsWindow)
{
    ui->setupUi(this);
}

startOptionsWindow::~startOptionsWindow()
{
    delete ui;
}

void startOptionsWindow::on_backButton_clicked()
{
    this->close();
}



void startOptionsWindow::on_newGameButton_clicked()
{
    this->hide();
    lcw = new levelChoiceWindow(this);
    lcw->show();
}
