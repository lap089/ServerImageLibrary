#ifndef DIALOGIMAGE_H
#define DIALOGIMAGE_H

#include <QDialog>
#include<QImage>

namespace Ui {
class DialogImage;
}

class DialogImage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogImage(QWidget *parent = 0);
    ~DialogImage();

private:
    Ui::DialogImage *ui;
};

#endif // DIALOGIMAGE_H
