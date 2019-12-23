#ifndef LEVELCHOICEWINDOW_H
#define LEVELCHOICEWINDOW_H

#include <QMainWindow>
#include <QListView>

namespace Ui {
class levelChoiceWindow;
}

class levelChoiceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit levelChoiceWindow(QWidget *parent = nullptr);
    ~levelChoiceWindow();

private slots:


    void on_loadButton_clicked();

private:
    Ui::levelChoiceWindow *ui;


    QListView* list;
};

#endif // LEVELCHOICEWINDOW_H
