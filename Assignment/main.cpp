#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("Battery Pack Creator");
    w.resize(400, 300);
    w.show();

    return a.exec();
}
