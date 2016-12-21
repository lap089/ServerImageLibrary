#include "DialogConnection.h"
#include "ui_DialogConnection.h"

DialogConnection::DialogConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnection)
{
    ui->setupUi(this);
    ui->port->setValidator( new QIntValidator(0, 65000, this) );
    ui->ip->setText("127.0.0.1");
    ui->port->setText("123");
}

DialogConnection::~DialogConnection()
{
    delete ui;
}

void DialogConnection::printErrorMessage(const QString mess) {
    QMessageBox messageBox;
    messageBox.critical(this,"Error", mess);
    messageBox.setFixedSize(500,200);
}

void DialogConnection::printInfoMessage(const QString mess) {
    QMessageBox messageBox;
    messageBox.information(this, "Information" ,mess);
    messageBox.setFixedSize(500,200);
}
void DialogConnection::on_connect_clicked()
{
    string ip = ui->ip->text().toUtf8().constData();
    int port = ui->port->text().toInt();
    try {
        setUpServerConnection(client, sock, ip, port);
        this->hide();
        loginForm = new LoginForm(sock, this);
        loginForm->show();
    } catch (SocketEx& e) {
        printErrorMessage(e.what());
    }

}
