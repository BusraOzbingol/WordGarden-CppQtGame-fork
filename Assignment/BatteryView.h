#ifndef BATTERYVIEW_H
#define BATTERYVIEW_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <vector>

#include "BatteryPack.h"
#include "Battery.h"

class BatteryView : public QWidget
{
    Q_OBJECT

public:
    explicit BatteryView(QWidget *parent = nullptr);

    // Get the data to be visualized from MainWindow.
    void updateVisualization(
        BatteryPack::ConnectionType type,
        const std::vector<Battery*>& cells
    );

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    BatteryPack::ConnectionType currentType = BatteryPack::SERIES;
    std::vector<Battery*> currentCells;

    // Method signatures have been corrected
    void drawPack(QPainter &painter);
    void drawBattery(QPainter &painter, const Battery *b, int x, int y, int width, int height);
    QColor getChargeColor(double percent) const;
};

#endif // BATTERYVIEW_H
