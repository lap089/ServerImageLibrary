#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->selection->addItem("User");
    ui->selection->addItem("Category");

}

MainWindow::MainWindow(SOCKET& sock, User user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->selection->addItem("User");
    ui->selection->addItem("Category");
    this->sock = sock;
    this->currentUser = user;
    setWindowTitle("Image Library Server");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dialogUpload;
}

void MainWindow::sendCmd(std::string cmd)
{
    send(sock, cmd.c_str(), cmd.length(), 0);
}

void MainWindow::printMessage(const QString mess) {
    QMessageBox messageBox;
    messageBox.critical(this,"Error", mess);
    messageBox.setFixedSize(500,200);
}


void MainWindow::on_search_clicked()
{
    string cmd;
    string query = ui->quey->text().toUtf8().constData();
    if(query.empty()) {
       printMessage("Query cannot be empty");
       return;
    }
    QString selection = ui->selection->currentText();
    if(selection == "User") {
        cmd = "-l --user " + query;
    }
    else {
        cmd = "-l --category " + query;
    }
    send(sock, cmd.c_str(), cmd.length(), 0);

    imageManager = getList(sock);
    cout<<"ImageManager size: "<<imageManager.getSize()<<endl;

    ui->imageList->clear();
    for(Image image : imageManager.getImages()) {
        QString imageName = QString::fromStdString(image.getName());
        ui->imageList->addItem(imageName);
    }

}

void MainWindow::on_imageList_clicked(const QModelIndex &index)
{
     int selectedIndex = index.row();
     QString info = QString::fromStdString(imageManager.getImage(selectedIndex).toString());
     ui->textBrowser->setText(info);
}

void MainWindow::on_download_clicked()
{
   int currentIndex= ui->imageList->currentRow();
   if(currentIndex == -1) {
       printMessage("Please select an image");
       return;
   }
   sendCmd("-d --id " + to_string(currentIndex));
   try {
       ui->progressBar->setMaximum(0);
       ui->progressBar->setMinimum(0);
       ui->progressBar->setValue(0);
       string fileName = downImage(sock, currentIndex);
       ImageWindow* dialogImage = new ImageWindow(fileName, this);
       dialogImage->show();
       ui->progressBar->setMaximum(100);
       ui->progressBar->setMinimum(0);
       ui->progressBar->setValue(100);
   } catch (SocketEx& e) {
       printMessage(e.what());
   }

}

void MainWindow::on_upload_clicked()
{
    dialogUpload = new DialogUpload(sock, currentUser, this);
    dialogUpload->show();
}
