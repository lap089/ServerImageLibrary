#include "ImageWindow.h"
#include "ui_ImageWindow.h"

ImageWindow::ImageWindow(string fileName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageWindow)
{
    ui->setupUi(this);
     QImage image(fileName.c_str());
     ui->pic->setPixmap(QPixmap::fromImage(image));
     setWindowTitle(tr("Image Viewer"));
}

ImageWindow::~ImageWindow()
{
    delete ui;
}
