/**
 * @file mainflower.cpp
 * @brief Implementation of the MainFlower widget.
 * * This file handles the logic for loading flower assets and rendering them
 * based on the remaining attempts (leaves) in the game.
 */

#include "4_Ui/mainFlower.h"
#include <QPainter>
#include <QDebug>

/**
 * @brief Constructor for MainFlower.
 * @param parent Pointer to the parent widget.
 * * Initializes the widget to be transparent for mouse events so it doesn't 
 * interfere with underlying UI elements. Sets the default leaf count to 6.
 */
MainFlower::MainFlower(QWidget *parent)
    : QWidget(parent), leafCount(6)
{
    // Pass mouse clicks to the background/parent widgets
    setAttribute(Qt::WA_TransparentForMouseEvents);

    loadImages();

    // Start with 6 leaves (maximum health/attempts)
    setLeafCount(6);
}

/**
 * @brief Pre-loads all flower stage images into the memory map.
 * * Iterates through the resource paths from flower0.png to flower6.png.
 * Logs a critical error if a resource is missing.
 */
void MainFlower::loadImages()
{
    flowerStages.clear(); // Ensure the map is empty before loading
    for(int i = 0; i <= 6; ++i) {
        QString path = QString(":/6_Images/Backgrounds/flower%1.png").arg(i);
        QPixmap pix(path);

        if(!pix.isNull()) {
            flowerStages[i] = pix;
        } else {
            qDebug() << "Critical Error: Image not found ->" << path;
        }
    }
}

/**
 * @brief Updates the flower visual based on the provided count.
 * @param count The number of leaves (attempts) remaining (expected 0-6).
 * * This method ensures the count stays within bounds and loads the 
 * corresponding image asset. It then calls update() to trigger a repaint.
 */
void MainFlower::setLeafCount(int count)
{
    // Boundary protection (ensure count is between 0 and 6)
    if(count < 0) count = 0;
    if(count > 6) count = 6;

    this->leafCount = count;

    // Load the specific file for the current count to ensure accuracy
    QString path = QString(":/6_Images/Backgrounds/flower%1.png").arg(count);
    QPixmap newPix(path);

    if(!newPix.isNull()) {
        activeVisual = newPix;
        update(); // Trigger the paintEvent
    } else {
        qDebug() << "Failed to load image file:" << path;
    }
}

/**
 * @brief Draws the active flower image onto the widget.
 * @param event The paint event (unused).
 * * Scales the image to fit the current dimensions of the widget.
 */
void MainFlower::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(!activeVisual.isNull()) {
        // Draw the visual to fill the entire widget rectangle
        painter.drawPixmap(this->rect(), activeVisual);
    }
}
