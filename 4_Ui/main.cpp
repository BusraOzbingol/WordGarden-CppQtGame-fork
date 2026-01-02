/**
 * @file main.cpp
 * @brief Entry point for the application.
 * * This file contains the main function which initializes the Qt framework,
 * creates the primary window instance, and starts the event loop.
 */

#include "4_Ui/mainwindow.h"
#include <QApplication>

/**
 * @brief The main entry point of the application.
 * * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Status code of the application upon exit (0 for success).
 * * This function performs the following steps:
 * 1. Initializes the QApplication object to manage application-wide resources.
 * 2. Instantiates the MainWindow, which triggers the UI setup and Login screen.
 * 3. Displays the main window on the screen.
 * 4. Starts the main event loop to handle user interactions and system events.
 */
int main(int argc, char *argv[])
{
    // Initialize the Qt Application framework
    QApplication a(argc, argv);

    // Create the MainWindow instance
    // The constructor will trigger setupUI(), creating the Login screen
    MainWindow w;

    // Display the window to the user
    w.show();

    // Enter the main event loop and wait for application termination
    return a.exec();
}
