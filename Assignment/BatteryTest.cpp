/**
 * @file BatteryTest.cpp
 * @brief Main execution file for demonstrating and verifying the Battery and BatteryPack classes.
 *
 * This test suite validates:
 * 1. Series connection (min capacity/charge, sum voltage).
 * 2. Parallel connection  (sum capacity/charge, min voltage).
 * 3. Charge constraint handling (over-discharge and over-recharge).
 */
#include <iostream>
#include <iomanip>
#include "Battery.h"
#include "BatteryPack.h"

/**
 * @brief Helper function to print the current status of any Battery object or derived class.
 * * Displays the Voltage, Capacity, Charge, and calculated Percentage.
 * @param b A constant pointer to the Battery object or BatteryPack to query.
 */
void printStatus(const Battery* b) {
   
    std::cout << "Voltage: " << b->getVoltage()
              << " | Capacity: " << b->getCapacity()
              << " | Charge: " << b->getCharge()
              << " | Percent: " << b->getPercent() << " %\n";
}

/**
 * @brief Main entry point for the Battery and BatteryPack validation suite.
 * * Executes tests for series, parallel, and extreme charge constraint scenarios.
 * @return 0 on successful execution.
 */
int main() {
    
    // --- 1) SERIES TEST ---
    std::cout << "\n ---1) SERIES TEST--- \n";
    std::cout << "\n ->Initial values:\n";
    
   /**
     * @brief Creates three Battery objects. b2 will define the pack's capacity (1000mAh) 
     * and limits the pack's charge. 
     */
    Battery b1(2.6, 3000, 1500);
    Battery b2(2.6, 1000, 1800); 
    Battery b3(2.6, 3000, 2000);
    
    BatteryPack packSeries(BatteryPack::SERIES);
    packSeries.add(&b1);
    packSeries.add(&b2);
    packSeries.add(&b3);
    
    printStatus(&packSeries);
    
    // Use Test (2.0 hours): Expected discharge is 200mAh per cell (2 * 100).
    packSeries.use(2.0);
    std::cout << "\n ->After using for 2 hours \n";
    printStatus(&packSeries);
    
    // Recharge Test (2.0 hours): Expected recharge is 300mAh per cell (2 * 150), capped at 100% (1000mAh).
    packSeries.recharge(2.0);
    std::cout << "\n ->After charging for 2 hours \n";
    printStatus(&packSeries);

    // --- 2) PARALLEL TEST ---
    std::cout << "\n \n ---2) PARALLELS TEST--- \n";
    std::cout << "\n ->Initial values:\n";
    /**
     * @brief Creates three Battery objects for a Parallel setup. 
     * The total pack capacity will be the sum (17000mAh) and total charge will be the sum (5300mAh).
     */
    Battery b4(2.6, 4000, 1500);
    Battery b5(2.6, 5000, 1800);
    Battery b6(2.6, 8000, 2000);
    
    BatteryPack packParallel(BatteryPack::PARALLEL);
    packParallel.add(&b4);
    packParallel.add(&b5);
    packParallel.add(&b6);
    
    printStatus(&packParallel);
    
    // Use Test (1.5 hours): Total charge loss is 3 cells * 150mAh = 450mAh.
    packParallel.use(1.5);
    std::cout << "\n ->After using for 1.5 hours \n";
    printStatus(&packParallel);
    
    // Recharge Test (1.5 hours): Total charge gain is 3 cells * 225mAh = 675mAh.
    packParallel.recharge(1.5);
    std::cout << "\n ->After charging for 1.5 hours \n";
    printStatus(&packParallel);

    // --- 3) EXTREME CASES ---
    std::cout << "\n \n ---3)EXTREME CASES--- \n ";
    
    // Tests safe handling of zero cells/zero capacity/zero charge.
    BatteryPack packEmpty(BatteryPack::SERIES);
    std::cout << "\n ->Empty Pack (SERIES) \n";
    printStatus(&packEmpty);
    
    
    // Tests that charge cannot go below 0
    Battery bSmall(3.7, 1000, 50); // Starts low
    BatteryPack packSmall(BatteryPack::SERIES);
    
    std::cout << "\n \n Using more than the limit \n";
    packSmall.add(&bSmall);
    printStatus(&packSmall);
    
    packSmall.use(5.0); // 5 hours * 100mAh = 500mAh usage, should cap at 0mAh
    std::cout << "\n ->After 5 hours of use \n";
    printStatus(&packSmall); 

    // Tests that charge cannot go above 100
    Battery bHigh(3.7, 1000, 950); 
    BatteryPack packHigh(BatteryPack::PARALLEL); 
    packHigh.add(&bHigh);
    
    std::cout << "\n \n ->Charging more than the limit \n";
    printStatus(&packHigh);
    
    packHigh.recharge(5.0); // 5 hours * 150mAh = 750mAh recharge, should cap at 1000mAh
    
    std::cout << "\n ->After 5 hours of charge \n";
    printStatus(&packHigh);
    
    return 0;
}
