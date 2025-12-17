#include "mainwindow.h"
#include "batteryview.h"
#include <QVBoxLayout>
#include <QSplitter>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>
#include <QListWidget>

/**
 * @file mainwindow.cpp
 * @brief Implements the main GUI window for managing batteries and battery packs.
 */

 /**
  * @brief Constructs the MainWindow with all GUI elements initialized.
  * @param parent Parent QWidget pointer, default is nullptr.
  */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentPack(nullptr)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // --- Main splitter ---
    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal, central);

    // --- Control panel on the left ---
    QWidget *controlWidget = new QWidget();
    QVBoxLayout *controlLayout = new QVBoxLayout(controlWidget);

    comboType = new QComboBox();
    comboType->addItem("SERIES");
    comboType->addItem("PARALLEL");

    batteryList = new QListWidget();
    batteryList->setSelectionMode(QAbstractItemView::MultiSelection);

    btnAddBattery = new QPushButton("Add Battery");
    btnCreatePack = new QPushButton("Create Pack");
    btnRecharge = new QPushButton("Recharge");
    btnUse = new QPushButton("Use");

    lblTotalVoltage = new QLabel("Total Voltage: 0 V");
    lblTotalCapacity = new QLabel("Total Capacity: 0 mAh");
    lblPackInfo = new QLabel("Pack info will appear here");

    QFont bigFont = lblTotalVoltage->font();
    bigFont.setPointSize(16);
    lblTotalVoltage->setFont(bigFont);
    lblTotalCapacity->setFont(bigFont);

    controlLayout->addWidget(comboType);
    controlLayout->addWidget(batteryList);
    controlLayout->addWidget(btnAddBattery);
    controlLayout->addWidget(btnCreatePack);
    controlLayout->addWidget(btnUse);
    controlLayout->addWidget(btnRecharge);
    controlLayout->addSpacing(30);
    controlLayout->addWidget(lblTotalVoltage);
    controlLayout->addWidget(lblTotalCapacity);
    controlLayout->addWidget(lblPackInfo);
    controlLayout->addStretch(1);

    // --- Battery visualization panel on the right ---
    batteryView = new BatteryView();

    mainSplitter->addWidget(controlWidget);
    mainSplitter->addWidget(batteryView);

    QList<int> sizes;
    sizes << 250 << 550;
    mainSplitter->setSizes(sizes);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addWidget(mainSplitter);

    // --- Add sample batteries ---
    batteries.push_back(Battery(3.7, 2000, 1500));
    batteries.push_back(Battery(3.7, 2000, 1800));
    batteries.push_back(Battery(3.7, 2000, 2000));

    for (size_t i = 0; i < batteries.size(); ++i) {
        batteryList->addItem(QString("Sample Battery %1: %2V | Capacity: %3 mAh | Charge: %4 mAh")
                             .arg(i + 1)
                             .arg(batteries[i].getVoltage())
                             .arg(batteries[i].getCapacity())
                             .arg(batteries[i].getCharge()));
    }

    // --- Connect signals to slots ---
    connect(btnCreatePack, &QPushButton::clicked, this, &MainWindow::createPack);
    connect(btnAddBattery, &QPushButton::clicked, this, &MainWindow::addBattery);
    connect(btnUse, &QPushButton::clicked, this, &MainWindow::use);
    connect(btnRecharge, &QPushButton::clicked, this, &MainWindow::recharge);
}

/**
 * @brief Destructor, cleans up dynamically allocated batteries and pack.
 */
MainWindow::~MainWindow()
{
    for (auto b : ownedBatteries) delete b;
    delete currentPack;
}

/**
 * @brief Opens dialogs to add a new user battery to the list.
 */
void MainWindow::addBattery()
{
    bool ok;
    double voltage = QInputDialog::getDouble(this, "Voltage", "Enter voltage:", 3.7, 0, 100, 2, &ok);
    if (!ok) return;

    double capacity = QInputDialog::getDouble(this, "Capacity", "Enter capacity (mAh):", 2000, 0, 100000, 0, &ok);
    if (!ok) return;

    double charge = QInputDialog::getDouble(this, "Charge", "Enter current charge (mAh):", capacity, 0, capacity, 0, &ok);
    if (!ok) return;

    Battery *b = new Battery(voltage, capacity, charge);
    ownedBatteries.push_back(b);

    batteryList->addItem(QString("User Battery: %1V | Capacity: %2 mAh | Charge: %3 mAh")
                             .arg(voltage).arg(capacity).arg(charge));

    updateTotals();
}

/**
 * @brief Creates a battery pack from selected batteries in the list.
 * Updates the visualization and pack information labels.
 */
void MainWindow::createPack()
{
    if (currentPack) {
        delete currentPack;
        currentPack = nullptr;
    }
    currentSelectedCells.clear();

    BatteryPack::ConnectionType type = (comboType->currentText() == "SERIES") ? BatteryPack::SERIES : BatteryPack::PARALLEL;
    currentPack = new BatteryPack(type);

    auto selectedItems = batteryList->selectedItems();

    if (selectedItems.empty()) {
        QMessageBox::warning(this, "Error", "Please select at least one battery.");
        delete currentPack;
        currentPack = nullptr;
        batteryView->updateVisualization(type, currentSelectedCells);
        return;
    }

    for (auto item : selectedItems) {
        size_t index = static_cast<size_t>(batteryList->row(item));
        size_t initial_count = batteries.size();

        Battery *b = nullptr;

        if (index < initial_count) {
            b = &batteries[index];
        } else {
            b = ownedBatteries[index - initial_count];
        }

        currentPack->add(b);
        currentSelectedCells.push_back(b);
    }

    lblPackInfo->setText(QString("Pack Type: %1\nVoltage: %2 V\nCapacity: %3 mAh\nCharge: %4 mAh")
                         .arg(comboType->currentText())
                         .arg(currentPack->getVoltage())
                         .arg(currentPack->getCapacity())
                         .arg(currentPack->getCharge()));
    updateTotals();

    batteryView->updateVisualization(type, currentSelectedCells);
}

/**
 * @brief Uses the current battery pack for a specified number of hours.
 */
void MainWindow::use()
{
    if (currentPack == nullptr) {
        QMessageBox::warning(this, "Error", "Please create a battery pack first.");
        return;
    }

    bool ok;
    double hours = QInputDialog::getDouble(this, "Usage Hours", "Enter hours of usage:", 2, 0, 100, 1, &ok);
    if (!ok) return;

    currentPack->use(hours);

    lblPackInfo->setText(QString("Pack Type: %1\nVoltage: %2 V\nCapacity: %3 mAh\nCharge: %4 mAh")
                         .arg(comboType->currentText())
                         .arg(currentPack->getVoltage())
                         .arg(currentPack->getCapacity())
                         .arg(currentPack->getCharge()));
    updateTotals();

    BatteryPack::ConnectionType type = (comboType->currentText() == "SERIES") ? BatteryPack::SERIES : BatteryPack::PARALLEL;
    batteryView->updateVisualization(type, currentSelectedCells);
}

/**
 * @brief Recharges the current battery pack for a specified number of hours.
 */
void MainWindow::recharge()
{
    if (currentPack == nullptr) {
        QMessageBox::warning(this, "Error", "Please create a battery pack first.");
        return;
    }

    bool ok;
    double hours = QInputDialog::getDouble(this, "Recharge Hours", "Enter hours to recharge:", 2, 0, 100, 1, &ok);
    if (!ok) return;

    currentPack->recharge(hours);

    lblPackInfo->setText(QString("Pack Type: %1\nVoltage: %2 V\nCapacity: %3 mAh\nCharge: %4 mAh")
                         .arg(comboType->currentText())
                         .arg(currentPack->getVoltage())
                         .arg(currentPack->getCapacity())
                         .arg(currentPack->getCharge()));
    updateTotals();

    BatteryPack::ConnectionType type = (comboType->currentText() == "SERIES") ? BatteryPack::SERIES : BatteryPack::PARALLEL;
    batteryView->updateVisualization(type, currentSelectedCells);
}

/**
 * @brief Updates the total voltage and capacity labels based on current selection or all batteries.
 */
void MainWindow::updateTotals()
{
    double totalVoltage = 0;
    double totalCapacity = 0;

    if (currentPack) {
        totalVoltage = currentPack->getVoltage();
        totalCapacity = currentPack->getCapacity();
    } else {
        for (auto &b : batteries)
        {
            totalVoltage += b.getVoltage();
            totalCapacity += b.getCapacity();
        }
        for (auto b : ownedBatteries)
        {
            totalVoltage += b->getVoltage();
            totalCapacity += b->getCapacity();
        }
    }

    lblTotalVoltage->setText(QString("Total Voltage: %1 V").arg(totalVoltage, 0, 'f', 2));
    lblTotalCapacity->setText(QString("Total Capacity: %1 mAh").arg(totalCapacity, 0, 'f', 0));
}
