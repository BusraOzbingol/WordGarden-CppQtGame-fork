#ifndef MAINFLOWER_H
#define MAINFLOWER_H

#include <QWidget>
#include <QPixmap>
#include <QMap>

class MainFlower : public QWidget
{
    Q_OBJECT
public:
    explicit MainFlower(QWidget *parent = nullptr);
    void setLeafCount(int count);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void loadImages();

    QMap<int, QPixmap> flowerStages;
    QPixmap aktifGorsel;
    int leafCount;
};

#endif // MAINFLOWER_H
