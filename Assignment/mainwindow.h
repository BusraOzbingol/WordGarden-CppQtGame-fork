#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <vector>
#include "Battery.h"
#include "BatteryPack.h"
#include "batteryview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createPack();
    void addBattery();
    void use();
    void recharge();
    void updateTotals();

private:
    QComboBox *comboType;
    QListWidget *batteryList;
    QPushButton *btnCreatePack;
    QPushButton *btnAddBattery;
    QPushButton *btnRecharge;
    QPushButton *btnUse;
    QLabel *lblPackInfo;
    QLabel *lblTotalVoltage;
    QLabel *lblTotalCapacity;

    std::vector<Battery> batteries;
    std::vector<Battery*> ownedBatteries;
    BatteryPack *currentPack;

    BatteryView *batteryView;
    std::vector<Battery*> currentSelectedCells;
};

#endif
