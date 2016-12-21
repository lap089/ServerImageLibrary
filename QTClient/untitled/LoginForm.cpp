#include "LoginForm.h"
#include "ui_LoginForm.h"


LoginForm::LoginForm(SOCKET& sock, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    this->sock = sock;
    this->parent = parent;
    ui->username->setText("admin");
    ui->password->setText("123456");


}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_clicked()
{


    string username = ui->username->text().toUtf8().constData();
    string password = ui->password->text().toUtf8().constData();

    try {
        string cmd = "--login --user " + username + " --pass " + password;
        cout<<cmd.c_str()<<endl;
        int ret = send(sock, cmd.c_str(), cmd.length(), 0);
        cout<<ret<<endl;
        User currentUser = login(sock, username, password);

        mainWindow = new MainWindow(sock, currentUser, this);
        this->hide();
        mainWindow->show();

    } catch (SocketEx& e) {
        QMessageBox messageBox;
        messageBox.critical(this,"Error",e.what());
        messageBox.setFixedSize(500,200);
    }


}


void LoginForm::on_signup_clicked()
{
    dialogSignup = new DialogSignup(sock, this);
    dialogSignup->show();
}
