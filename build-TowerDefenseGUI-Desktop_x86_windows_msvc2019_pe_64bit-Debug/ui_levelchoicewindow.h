/********************************************************************************
** Form generated from reading UI file 'levelchoicewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEVELCHOICEWINDOW_H
#define UI_LEVELCHOICEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_levelChoiceWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *backButton;
    QPushButton *loadButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *levelChoiceWindow)
    {
        if (levelChoiceWindow->objectName().isEmpty())
            levelChoiceWindow->setObjectName(QString::fromUtf8("levelChoiceWindow"));
        levelChoiceWindow->resize(800, 600);
        centralwidget = new QWidget(levelChoiceWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(backButton->sizePolicy().hasHeightForWidth());
        backButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(backButton);

        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        sizePolicy.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(loadButton);


        verticalLayout->addLayout(horizontalLayout);

        levelChoiceWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(levelChoiceWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        levelChoiceWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(levelChoiceWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        levelChoiceWindow->setStatusBar(statusbar);

        retranslateUi(levelChoiceWindow);

        QMetaObject::connectSlotsByName(levelChoiceWindow);
    } // setupUi

    void retranslateUi(QMainWindow *levelChoiceWindow)
    {
        levelChoiceWindow->setWindowTitle(QApplication::translate("levelChoiceWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("levelChoiceWindow", "Enter level name", nullptr));
        backButton->setText(QApplication::translate("levelChoiceWindow", "Back", nullptr));
        loadButton->setText(QApplication::translate("levelChoiceWindow", "Load", nullptr));
    } // retranslateUi

};

namespace Ui {
    class levelChoiceWindow: public Ui_levelChoiceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVELCHOICEWINDOW_H
