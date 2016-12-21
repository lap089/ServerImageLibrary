#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include"MainWindow.h"
#include"ClientSide.h"
#include<QIntValidator>
#include<QMessageBox>
#include"DialogSignup.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(SOCKET& sock, QWidget *parent = 0);
    ~LoginForm();

private slots:
    void on_pushButton_clicked();
    void on_signup_clicked();

private:
    Ui::LoginForm *ui;
    MainWindow* mainWindow;
    QWidget* parent;
    DialogSignup* dialogSignup;
    SOCKET sock;
    SOCKET client;
};

#endif // LOGINFORM_H
