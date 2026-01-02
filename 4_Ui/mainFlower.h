/**
 * @file mainflower.h
 * @brief Header file for the MainFlower custom widget.
 * * This file contains the definition of the MainFlower class, which handles
 * the dynamic rendering of flower growth stages based on user input or data.
 */

#ifndef MAINFLOWER_H
#define MAINFLOWER_H

#include <QWidget>
#include <QPixmap>
#include <QMap>

/**
 * @class MainFlower
 * @brief A custom widget responsible for displaying flower graphics.
 * * The MainFlower class inherits from QWidget and provides a specialized
 * interface for displaying different flower visuals (stages). It uses
 * a mapping system to associate specific leaf counts with visual assets.
 */
class MainFlower : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a MainFlower widget.
     * @param parent Pointer to the parent QWidget (default is nullptr).
     */
    explicit MainFlower(QWidget *parent = nullptr);

    /**
     * @brief Updates the current leaf count and triggers a redraw.
     * @param count The number of leaves used to determine the growth stage.
     */
    void setLeafCount(int count);

protected:
    /**
     * @brief Overridden paint event to render the flower image.
     * @param event The paint event triggered by the Qt framework.
     * * This function uses QPainter to draw the @ref activeVisual onto the widget's surface.
     */
    void paintEvent(QPaintEvent *event) override;

private:
    /**
     * @brief Loads the flower growth stage images from resources.
     * * Populates the @ref flowerStages map with key-value pairs representing
     * leaf counts and their corresponding QPixmap visuals.
     */
    void loadImages();

    /** @brief A map linking specific leaf counts (int) to their respective image (QPixmap). */
    QMap<int, QPixmap> flowerStages;

    /** @brief The pixmap currently selected for rendering on the screen. */
    QPixmap activeVisual;

    /** @brief The current count of leaves, used to select the appropriate stage. */
    int leafCount;
};

#endif // MAINFLOWER_H
