#ifndef DIALOGCONNECTION_H
#define DIALOGCONNECTION_H

#include <QDialog>
#include<LoginForm.h>
#include"ClientSide.h"
#include <QHostAddress>

namespace Ui {
class DialogConnection;
}

class DialogConnection : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConnection(QWidget *parent = 0);
    ~DialogConnection();
    void sendCmd(string cmd);
    void printErrorMessage(const QString mess);
    void printInfoMessage(const QString mess);

private slots:
    void on_connect_clicked();

private:
    Ui::DialogConnection *ui;
    SOCKET sock;
    SOCKET client;
    LoginForm* loginForm;
};

#endif // DIALOGCONNECTION_H
