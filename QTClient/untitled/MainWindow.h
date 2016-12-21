#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<ClientSide.h>
#include"ImageWindow.h"
#include"DialogUpload.h"

namespace Ui {

class LoginForm;
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(SOCKET& sock, User currentUser, QWidget *parent = 0);
    ~MainWindow();
    void sendCmd(string cmd);
    void printMessage(const QString mess);

private slots:
    void on_search_clicked();

    void on_imageList_clicked(const QModelIndex &index);

    void on_download_clicked();

    void on_upload_clicked();

private:
    Ui::MainWindow *ui;
    Ui::LoginForm* loginForm;
    SOCKET sock;
    ImageManager imageManager;
    DialogUpload* dialogUpload;
    User currentUser;
};

#endif // MAINWINDOW_H
