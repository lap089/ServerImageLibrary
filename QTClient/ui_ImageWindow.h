/********************************************************************************
** Form generated from reading UI file 'ImageWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEWINDOW_H
#define UI_IMAGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QLabel *pic;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ImageWindow)
    {
        if (ImageWindow->objectName().isEmpty())
            ImageWindow->setObjectName(QStringLiteral("ImageWindow"));
        ImageWindow->resize(800, 600);
        centralwidget = new QWidget(ImageWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 776, 525));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pic = new QLabel(scrollAreaWidgetContents);
        pic->setObjectName(QStringLiteral("pic"));

        gridLayout_2->addWidget(pic, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

        ImageWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ImageWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        ImageWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ImageWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ImageWindow->setStatusBar(statusbar);

        retranslateUi(ImageWindow);

        QMetaObject::connectSlotsByName(ImageWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ImageWindow)
    {
        ImageWindow->setWindowTitle(QApplication::translate("ImageWindow", "MainWindow", Q_NULLPTR));
        pic->setText(QApplication::translate("ImageWindow", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageWindow: public Ui_ImageWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEWINDOW_H
