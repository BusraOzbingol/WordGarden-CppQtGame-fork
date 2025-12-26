#include "mainflower.h"
#include <QPainter>

MainFlower::MainFlower(QWidget *parent)
    : QWidget(parent), leafCount(6)
{
    loadImages();

    if (flowerStages.contains(6)) {
        aktifGorsel = flowerStages[6];
    }

    // act like background
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void MainFlower::loadImages()
{
    for(int i = 0; i <= 6; ++i) {
        QString path = QString(":/flower%1.png").arg(i);
        QPixmap pix;
        if(pix.load(path)) {
            flowerStages[i] = pix;
        }
    }
}

void MainFlower::setLeafCount(int count)
{
    if(count < 0) count = 0;
    if(count > 6) count = 6;

    leafCount = count;

    if(flowerStages.contains(leafCount)) {
        aktifGorsel = flowerStages[leafCount];
        update();
    }
}

void MainFlower::paintEvent(QPaintEvent *)
{
    if(aktifGorsel.isNull()) return;

    QPainter painter(this);
    painter.drawPixmap(rect(), aktifGorsel);
}
