#include "4_Ui/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Initialize the Qt Application framework
    QApplication a(argc, argv);

    // Create the MainWindow instance
    // The constructor will trigger setupUI(), creating the Login screen
    MainWindow w;

    // Display the window to the user
    w.show();

    // Enter the main event loop
    return a.exec();
}
