/********************************************************************************
** Form generated from reading UI file 'startoptionswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTOPTIONSWINDOW_H
#define UI_STARTOPTIONSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_startOptionsWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *loadGameButton;
    QPushButton *newGameButton;
    QPushButton *backButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *startOptionsWindow)
    {
        if (startOptionsWindow->objectName().isEmpty())
            startOptionsWindow->setObjectName(QString::fromUtf8("startOptionsWindow"));
        startOptionsWindow->resize(330, 151);
        centralwidget = new QWidget(startOptionsWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        loadGameButton = new QPushButton(centralwidget);
        loadGameButton->setObjectName(QString::fromUtf8("loadGameButton"));

        horizontalLayout->addWidget(loadGameButton);

        newGameButton = new QPushButton(centralwidget);
        newGameButton->setObjectName(QString::fromUtf8("newGameButton"));

        horizontalLayout->addWidget(newGameButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        backButton = new QPushButton(centralwidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));

        verticalLayout_2->addWidget(backButton);

        startOptionsWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(startOptionsWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 330, 17));
        startOptionsWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(startOptionsWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        startOptionsWindow->setStatusBar(statusbar);

        retranslateUi(startOptionsWindow);

        QMetaObject::connectSlotsByName(startOptionsWindow);
    } // setupUi

    void retranslateUi(QMainWindow *startOptionsWindow)
    {
        startOptionsWindow->setWindowTitle(QApplication::translate("startOptionsWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("startOptionsWindow", "Choose start options", nullptr));
        loadGameButton->setText(QApplication::translate("startOptionsWindow", "Load game", nullptr));
        newGameButton->setText(QApplication::translate("startOptionsWindow", "New game", nullptr));
        backButton->setText(QApplication::translate("startOptionsWindow", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class startOptionsWindow: public Ui_startOptionsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTOPTIONSWINDOW_H
