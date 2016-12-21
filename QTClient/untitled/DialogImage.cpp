#include "DialogImage.h"
#include "ui_DialogImage.h"

DialogImage::DialogImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImage)
{
    ui->setupUi(this);
    QImage image("candle-1280x1024.jpg");
    ui->pic->setPixmap(QPixmap::fromImage(image));
}

DialogImage::~DialogImage()
{
    delete ui;
}
