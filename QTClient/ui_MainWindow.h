/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *download;
    QLineEdit *quey;
    QListWidget *imageList;
    QComboBox *selection;
    QTextBrowser *textBrowser;
    QPushButton *search;
    QPushButton *upload;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(651, 445);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        download = new QPushButton(centralwidget);
        download->setObjectName(QStringLiteral("download"));

        gridLayout->addWidget(download, 7, 4, 1, 1);

        quey = new QLineEdit(centralwidget);
        quey->setObjectName(QStringLiteral("quey"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(quey->sizePolicy().hasHeightForWidth());
        quey->setSizePolicy(sizePolicy);

        gridLayout->addWidget(quey, 0, 1, 1, 4);

        imageList = new QListWidget(centralwidget);
        imageList->setObjectName(QStringLiteral("imageList"));

        gridLayout->addWidget(imageList, 6, 0, 2, 4);

        selection = new QComboBox(centralwidget);
        selection->setObjectName(QStringLiteral("selection"));

        gridLayout->addWidget(selection, 0, 0, 1, 1);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout->addWidget(textBrowser, 6, 4, 1, 1);

        search = new QPushButton(centralwidget);
        search->setObjectName(QStringLiteral("search"));

        gridLayout->addWidget(search, 1, 3, 1, 1);

        upload = new QPushButton(centralwidget);
        upload->setObjectName(QStringLiteral("upload"));

        gridLayout->addWidget(upload, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 651, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        download->setText(QApplication::translate("MainWindow", "Download", Q_NULLPTR));
        quey->setPlaceholderText(QString());
        search->setText(QApplication::translate("MainWindow", "Search", Q_NULLPTR));
        upload->setText(QApplication::translate("MainWindow", "Upload", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
