#include "batteryview.h" 
#include "BatteryPack.h"
#include "Battery.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QString>
#include <QRect>
#include <QFont>
#include <QDebug>

BatteryView::BatteryView(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color: #1E1E1E;");
    setMinimumSize(400, 200);
}

void BatteryView::updateVisualization(
    BatteryPack::ConnectionType type,
    const std::vector<Battery*>& cells)
{
    currentType = type;
    currentCells = cells;
    update();
}

QColor BatteryView::getChargeColor(double percent) const
{
    if (percent < 15.0) return Qt::red;
    else if (percent < 50.0) return Qt::yellow;
    else return Qt::green;
}

void BatteryView::drawBattery(QPainter &painter, const Battery *b, int x, int y, int width, int height)
{
    double percent = b->getPercent();

   
    painter.setPen(QPen(Qt::white, 2));
    painter.setBrush(Qt::NoBrush);
    QRect batteryRect(x, y, width, height);
    painter.drawRoundedRect(batteryRect, 5, 5);

    
    int filledHeight = static_cast<int>(height * (percent / 100.0));
    QRect fillRect(x + 1, y + height - filledHeight + 1, width - 2, filledHeight - 2);

    QColor chargeColor = getChargeColor(percent);
    painter.setBrush(chargeColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(fillRect);

    
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 8));
    QString info = QString("%1V\n%2%%").arg(b->getVoltage(), 0, 'f', 1).arg(percent, 0, 'f', 0);
    painter.drawText(batteryRect, Qt::AlignCenter, info);

    
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::black);

   
    painter.drawEllipse(x + width / 2 - 4, y - 4, 8, 8);         
    painter.drawEllipse(x + width / 2 - 4, y + height - 4, 8, 8); 
}

void BatteryView::drawPack(QPainter &painter)
{
    const auto& cells = currentCells;
    int count = cells.size();

    const int B_WIDTH = 60;
    const int B_HEIGHT = 120;
    const int SPACING = 20;

    
    int totalLength = (currentType == BatteryPack::PARALLEL) ?
                     (count * B_WIDTH + (count - 1) * SPACING) :
                     (count * B_HEIGHT + (count - 1) * SPACING);

    int startX, startY;

    if (currentType == BatteryPack::SERIES) {
        startX = (this->width() - B_WIDTH) / 2;
        startY = (this->height() - totalLength) / 2;
    } else {
        startX = (this->width() - totalLength) / 2;
        startY = (this->height() - B_HEIGHT) / 2;
    }

    
    for (int i = 0; i < count; ++i) {
        Battery *b = cells[i];
        int x = startX;
        int y = startY;

        if (currentType == BatteryPack::PARALLEL) {
            x += i * (B_WIDTH + SPACING);
        } else { // SERIES
            y += i * (B_HEIGHT + SPACING);
        }

        drawBattery(painter, b, x, y, B_WIDTH, B_HEIGHT);

        
        if (i < count - 1) {
            painter.setPen(QPen(Qt::lightGray, 3));

            if (currentType == BatteryPack::SERIES) {
                
                painter.drawLine(x + B_WIDTH / 2, y + B_HEIGHT, x + B_WIDTH / 2, y + B_HEIGHT + SPACING);
            }
        }
    }

    
    if (currentType == BatteryPack::PARALLEL && count > 0) {
        int barY_P = startY - 20; // Pozitif bus bar
        int barY_N = startY + B_HEIGHT + 20; // Negatif bus bar
        int endX = startX + totalLength;

        
        painter.setPen(QPen(Qt::red, 5));
        painter.drawLine(startX, barY_P, endX, barY_P);

        
        painter.setPen(QPen(Qt::blue, 5));
        painter.drawLine(startX, barY_N, endX, barY_N);


        
        painter.setPen(QPen(Qt::lightGray, 2));
        for (int i = 0; i < count; ++i) {
            int x_center = startX + i * (B_WIDTH + SPACING) + B_WIDTH / 2;

            
            painter.drawLine(x_center, startY, x_center, barY_P + 3);

            
            painter.drawLine(x_center, startY + B_HEIGHT, x_center, barY_N - 3);
        }
    }


    
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 10));
    QString packInfo = QString("Pack Type: %1").arg(currentType == BatteryPack::SERIES ? "SERIES" : "PARALLEL");
    painter.drawText(10, 20, packInfo);
}

void BatteryView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (currentCells.empty()) {
        painter.setPen(Qt::gray);
        painter.drawText(rect(), Qt::AlignCenter, "Pil Paketi Görselleþtirme Alaný");
        return;
    }

    drawPack(painter);
}
