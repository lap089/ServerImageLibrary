/********************************************************************************
** Form generated from reading UI file 'DialogUpload.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGUPLOAD_H
#define UI_DIALOGUPLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogUpload
{
public:
    QGridLayout *gridLayout;
    QLabel *browsePath;
    QPushButton *browse;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *category;
    QLabel *label_3;
    QPlainTextEdit *description;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogUpload)
    {
        if (DialogUpload->objectName().isEmpty())
            DialogUpload->setObjectName(QStringLiteral("DialogUpload"));
        DialogUpload->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogUpload->sizePolicy().hasHeightForWidth());
        DialogUpload->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(DialogUpload);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        browsePath = new QLabel(DialogUpload);
        browsePath->setObjectName(QStringLiteral("browsePath"));

        gridLayout->addWidget(browsePath, 0, 0, 1, 1);

        browse = new QPushButton(DialogUpload);
        browse->setObjectName(QStringLiteral("browse"));

        gridLayout->addWidget(browse, 0, 1, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_2 = new QLabel(DialogUpload);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        category = new QLineEdit(DialogUpload);
        category->setObjectName(QStringLiteral("category"));

        formLayout->setWidget(0, QFormLayout::FieldRole, category);

        label_3 = new QLabel(DialogUpload);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        description = new QPlainTextEdit(DialogUpload);
        description->setObjectName(QStringLiteral("description"));

        formLayout->setWidget(1, QFormLayout::FieldRole, description);


        gridLayout->addLayout(formLayout, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(DialogUpload);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(DialogUpload);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogUpload, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogUpload, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogUpload);
    } // setupUi

    void retranslateUi(QDialog *DialogUpload)
    {
        DialogUpload->setWindowTitle(QApplication::translate("DialogUpload", "Dialog", Q_NULLPTR));
        browsePath->setText(QString());
        browse->setText(QApplication::translate("DialogUpload", "Browse...", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogUpload", "Category", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogUpload", "Description", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogUpload: public Ui_DialogUpload {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGUPLOAD_H
