#ifndef DIALOGSIGNUP_H
#define DIALOGSIGNUP_H

#include <QDialog>
#include"ClientSide.h"
#include<QMessageBox>

namespace Ui {
class DialogSignup;
}

class DialogSignup : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSignup(SOCKET& sock, QWidget *parent = 0);
    ~DialogSignup();
    void sendCmd(string cmd);
    void printErrorMessage(const QString mess);
    void printInfoMessage(const QString mess);

private slots:
    void on_submit_clicked();

private:
    Ui::DialogSignup *ui;
    SOCKET sock;
    QWidget* parent;
};

#endif // DIALOGSIGNUP_H
