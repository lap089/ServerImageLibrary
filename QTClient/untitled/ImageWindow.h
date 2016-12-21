#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QMainWindow>
#include<QImage>
#include<QLabel>
#include<QScrollArea>
#include<ClientSide.h>

namespace Ui {
class ImageWindow;
}

class ImageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageWindow(string fileName, QWidget *parent = 0);
    ~ImageWindow();

private:
    Ui::ImageWindow *ui;
    QLabel* imageLabel;
    QScrollArea* scrollArea;
};

#endif // IMAGEWINDOW_H
