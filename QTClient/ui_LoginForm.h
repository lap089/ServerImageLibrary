/********************************************************************************
** Form generated from reading UI file 'LoginForm.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *username;
    QLabel *label_2;
    QLineEdit *password;
    QPushButton *pushButton;
    QPushButton *signup;

    void setupUi(QDialog *LoginForm)
    {
        if (LoginForm->objectName().isEmpty())
            LoginForm->setObjectName(QStringLiteral("LoginForm"));
        LoginForm->resize(400, 180);
        verticalLayout_2 = new QVBoxLayout(LoginForm);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(LoginForm);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        username = new QLineEdit(LoginForm);
        username->setObjectName(QStringLiteral("username"));

        formLayout->setWidget(1, QFormLayout::FieldRole, username);

        label_2 = new QLabel(LoginForm);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        password = new QLineEdit(LoginForm);
        password->setObjectName(QStringLiteral("password"));
        password->setFrame(true);
        password->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, password);

        pushButton = new QPushButton(LoginForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        formLayout->setWidget(3, QFormLayout::FieldRole, pushButton);

        signup = new QPushButton(LoginForm);
        signup->setObjectName(QStringLiteral("signup"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(signup->sizePolicy().hasHeightForWidth());
        signup->setSizePolicy(sizePolicy1);

        formLayout->setWidget(3, QFormLayout::LabelRole, signup);


        verticalLayout->addLayout(formLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(LoginForm);

        QMetaObject::connectSlotsByName(LoginForm);
    } // setupUi

    void retranslateUi(QDialog *LoginForm)
    {
        LoginForm->setWindowTitle(QApplication::translate("LoginForm", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("LoginForm", "Username", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoginForm", "Password", Q_NULLPTR));
        pushButton->setText(QApplication::translate("LoginForm", "Login", Q_NULLPTR));
        signup->setText(QApplication::translate("LoginForm", "SignUp", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginForm: public Ui_LoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
