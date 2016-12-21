/********************************************************************************
** Form generated from reading UI file 'DialogSignup.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSIGNUP_H
#define UI_DIALOGSIGNUP_H

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

class Ui_DialogSignup
{
public:
    QFormLayout *formLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *username;
    QLabel *label_3;
    QLineEdit *password;
    QLabel *label_2;
    QLineEdit *confirm;
    QPushButton *submit;

    void setupUi(QDialog *DialogSignup)
    {
        if (DialogSignup->objectName().isEmpty())
            DialogSignup->setObjectName(QStringLiteral("DialogSignup"));
        DialogSignup->resize(400, 182);
        formLayout_2 = new QFormLayout(DialogSignup);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(DialogSignup);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        username = new QLineEdit(DialogSignup);
        username->setObjectName(QStringLiteral("username"));

        formLayout->setWidget(0, QFormLayout::FieldRole, username);

        label_3 = new QLabel(DialogSignup);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        password = new QLineEdit(DialogSignup);
        password->setObjectName(QStringLiteral("password"));
        password->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, password);

        label_2 = new QLabel(DialogSignup);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        confirm = new QLineEdit(DialogSignup);
        confirm->setObjectName(QStringLiteral("confirm"));
        confirm->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, confirm);

        submit = new QPushButton(DialogSignup);
        submit->setObjectName(QStringLiteral("submit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, submit);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, formLayout);


        retranslateUi(DialogSignup);

        QMetaObject::connectSlotsByName(DialogSignup);
    } // setupUi

    void retranslateUi(QDialog *DialogSignup)
    {
        DialogSignup->setWindowTitle(QApplication::translate("DialogSignup", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("DialogSignup", "Username", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogSignup", "Password", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogSignup", "Confirm", Q_NULLPTR));
        submit->setText(QApplication::translate("DialogSignup", "Submit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogSignup: public Ui_DialogSignup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSIGNUP_H
