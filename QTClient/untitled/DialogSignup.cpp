#include "DialogSignup.h"
#include "ui_DialogSignup.h"

DialogSignup::DialogSignup(SOCKET& sock, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSignup)
{
    ui->setupUi(this);
    this->sock = sock;
    this->parent = parent;
    setWindowTitle("Sign Up");
}

DialogSignup::~DialogSignup()
{
    delete ui;
}


void DialogSignup::sendCmd(std::string cmd)
{
    send(sock, cmd.c_str(), cmd.length(), 0);
}

void DialogSignup::printErrorMessage(const QString mess) {
    QMessageBox messageBox;
    messageBox.critical(this->parent,"Error", mess);
    messageBox.setFixedSize(500,200);
}

void DialogSignup::printInfoMessage(const QString mess) {
    QMessageBox messageBox;
    messageBox.information(this->parent, "Information" ,mess);
    messageBox.setFixedSize(500,200);
}

void DialogSignup::on_submit_clicked()
{
    string username = ui->username->text().toStdString();
    string password = ui->password->text().toStdString();
    string confirm = ui->confirm->text().toStdString();
    if(username.empty() ) {
        printErrorMessage("Username cannot be empty");
    }
    else if(password.empty()) {
        printErrorMessage("Password cannot be empty");
    }
    else if(password != confirm) {
        printErrorMessage("Password confirm does not match");
    }
    else {
    sendCmd("--register --user " + username + " --pass " + password);
    try {
        signUp(sock, username, password);
        printInfoMessage("SignUp successful");
        this->close();
    } catch (SocketEx& e) {
        printErrorMessage(e.what());
    }
    }
}
