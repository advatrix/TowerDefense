#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"
#include "startoptionswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_quitButton_clicked();

    void on_aboutButton_clicked();

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    void createStartMenuInterior();
    About* aboutWindow;
    startOptionsWindow* startOptionsWindow;
};
#endif // MAINWINDOW_H
