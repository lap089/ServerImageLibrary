#ifndef DIALOGUPLOAD_H
#define DIALOGUPLOAD_H

#include <QDialog>
#include"ClientSide.h"
#include<QFileDialog>
#include<QMessageBox>

namespace Ui {
class DialogUpload;
}

class DialogUpload : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUpload(SOCKET& sock, User user, QWidget *parent = 0);
    ~DialogUpload();
    void sendCmd(string cmd);
    void printMessage(const QString mess);

private slots:
    void on_buttonBox_accepted();

    void on_browse_clicked();

private:
    Ui::DialogUpload *ui;
    User user;
    SOCKET sock;
    QWidget* main;
};

#endif // DIALOGUPLOAD_H
