/********************************************************************************
** Form generated from reading UI file 'DialogConnection.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCONNECTION_H
#define UI_DIALOGCONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogConnection
{
public:
    QFormLayout *formLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *ip;
    QLineEdit *port;
    QLabel *label_2;
    QPushButton *connect;

    void setupUi(QDialog *DialogConnection)
    {
        if (DialogConnection->objectName().isEmpty())
            DialogConnection->setObjectName(QStringLiteral("DialogConnection"));
        DialogConnection->resize(400, 153);
        formLayout_2 = new QFormLayout(DialogConnection);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(DialogConnection);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        ip = new QLineEdit(DialogConnection);
        ip->setObjectName(QStringLiteral("ip"));

        formLayout->setWidget(0, QFormLayout::FieldRole, ip);

        port = new QLineEdit(DialogConnection);
        port->setObjectName(QStringLiteral("port"));

        formLayout->setWidget(1, QFormLayout::FieldRole, port);

        label_2 = new QLabel(DialogConnection);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, formLayout);

        connect = new QPushButton(DialogConnection);
        connect->setObjectName(QStringLiteral("connect"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, connect);


        retranslateUi(DialogConnection);

        QMetaObject::connectSlotsByName(DialogConnection);
    } // setupUi

    void retranslateUi(QDialog *DialogConnection)
    {
        DialogConnection->setWindowTitle(QApplication::translate("DialogConnection", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("DialogConnection", "Server", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogConnection", "Port", Q_NULLPTR));
        connect->setText(QApplication::translate("DialogConnection", "Connect", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogConnection: public Ui_DialogConnection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONNECTION_H
