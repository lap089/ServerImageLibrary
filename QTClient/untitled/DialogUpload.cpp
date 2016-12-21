#include "DialogUpload.h"
#include "ui_DialogUpload.h"

DialogUpload::DialogUpload(SOCKET& sock, User user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUpload)
{
    ui->setupUi(this);
    this->user = user;
    this->sock = sock;
    ui->browsePath->setText("");
    this->main = parent;
    setWindowTitle("Upload Image");
}

DialogUpload::~DialogUpload()
{
    delete ui;
}


void DialogUpload::sendCmd(std::string cmd)
{
    send(sock, cmd.c_str(), cmd.length(), 0);
}

void DialogUpload::printMessage(const QString mess) {
    QMessageBox messageBox;
    messageBox.critical(this->main,"Error", mess);
    messageBox.setFixedSize(500,200);
}

void DialogUpload::on_buttonBox_accepted()
{
    sendCmd("--upload");
    string description = ui->description->toPlainText().toStdString();
    string category = ui->category->text().toStdString();
    QFileInfo fileInfo(QFile(ui->browsePath->text()));
    string imagePath = fileInfo.absoluteFilePath().toStdString();
    int imageSize = fileInfo.size();
    FILE* picture;
    if(ui->browsePath->text().isEmpty()) {
        sendCmd(ERROR_CODE);
        printMessage("Please select image to upload");
    }
    else if (fopen_s(&picture, imagePath.c_str(), "rb") != 0) {
            sendCmd(ERROR_CODE);
            printMessage("Cannot read image");
        }
    else if (picture == NULL) {
        sendCmd(ERROR_CODE);
        printMessage("Error Opening Image File");
    }
    else {
    cout<<fileInfo.fileName().toStdString() <<endl << imagePath<<endl << imageSize<<endl;
    Image image(fileInfo.fileName().toStdString(), imagePath, category, description, imageSize, user.getUsername());
    try {
        ImageHelper::sendImage(sock, image, picture);
    } catch (SocketEx& e) {
        printMessage(e.what());
    }
    }
}

void DialogUpload::on_browse_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.bmp *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = dialog.getOpenFileName(this, tr("Open Image"), QDir::homePath(), tr("Image Files (*.png *.jpg *.bmp)"), 0, QFileDialog::DontUseNativeDialog);
    ui->browsePath->setText(fileName);
}
