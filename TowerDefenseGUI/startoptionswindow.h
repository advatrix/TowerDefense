#ifndef STARTOPTIONSWINDOW_H
#define STARTOPTIONSWINDOW_H

#include <QMainWindow>
#include <QListView>
#include "levelchoicewindow.h"

namespace Ui {
class startOptionsWindow;
}

class startOptionsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit startOptionsWindow(QWidget *parent = nullptr);
    ~startOptionsWindow();

private slots:
    void on_backButton_clicked();

    void on_newGameButton_clicked();

private:
    Ui::startOptionsWindow *ui;
    levelChoiceWindow* lcw;

};

#endif // STARTOPTIONSWINDOW_H
