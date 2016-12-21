#include "DialogConnection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(true);
    DialogConnection w;
    w.show();

    return a.exec();
}
