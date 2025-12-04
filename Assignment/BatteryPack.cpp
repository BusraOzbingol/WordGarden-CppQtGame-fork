#include "BatteryPack.h"
#include <algorithm>

/**
 * @brief Constructs a BatteryPack object.
 * * Initializes the base Battery class with dummy values (0,0,0) because
 * the pack's actual attributes (voltage, capacity, etc.) are derived
 * dynamically from the cells added to it.
 * * @param t The connection type of the pack (SERIES or PARALLEL).
 */
BatteryPack::BatteryPack(ConnectionType t)
    : Battery(0, 0, 0), type(t)
{
    // Base class Battery is initialized with dummy values (0,0,0) because
    // BatteryPack calculates all values dynamically from its cells.
}

/**
 * @brief Adds a battery cell to the pack.
 * * @param b Pointer to the Battery object to be added.
 */
void BatteryPack::add(Battery *b)
{
    cells.push_back(b);
}

/**
 * @brief Simulates usage of the battery pack.
 * * Discharges every cell contained within the pack by the specified amount of hours.
 * * @param hours The duration of usage in hours.
 */
void BatteryPack::use(double hours)
{
    // Discharges every cell in the pack
    for (Battery *b : cells)
    {
        b->use(hours);
    }
}

/**
 * @brief Recharges the battery pack.
 * * Recharges every cell contained within the pack by the specified amount of hours.
 * * @param hours The duration of recharging in hours.
 */
void BatteryPack::recharge(double hours)
{
    // Recharges every cell in the pack
    for (Battery *b : cells)
    {
        b->recharge(hours);
    }
}

/**
 * @brief Calculates the total voltage of the battery pack.
 * * The calculation depends on the connection type:
 * - **SERIES**: Returns the sum of all cell voltages.
 * - **PARALLEL**: Returns the voltage of the first cell (assumes uniform cells).
 * * @return double The total voltage. Returns 0.0 if the pack is empty.
 */
double BatteryPack::getVoltage() const
{
    if (cells.empty())
        return 0.0;

    if (type == SERIES)
    {
        // Series: Sum of all voltages
        double totalVoltage = 0.0;
        for (const Battery *b : cells)
        {
            totalVoltage += b->getVoltage();
        }
        return totalVoltage;
    }
    else
    {
        // Parallel: Voltage of any cell (using the first one)
        return cells[0]->getVoltage();
    }
}

/**
 * @brief Calculates the total capacity of the battery pack.
 * * The calculation depends on the connection type:
 * - **SERIES**: Returns the minimum capacity found among the cells (bottleneck).
 * - **PARALLEL**: Returns the sum of all cell capacities.
 * * @return double The total capacity. Returns 0.0 if the pack is empty.
 */
double BatteryPack::getCapacity() const
{
    if (cells.empty())
        return 0.0;

    if (type == SERIES)
    {
        // Series: Minimum capacity among cells
        double minCapacity = cells[0]->getCapacity();
        for (size_t i = 1; i < cells.size(); ++i)
        {
            double c = cells[i]->getCapacity();
            if (c < minCapacity)
            {
                minCapacity = c;
            }
        }
        return minCapacity;
    }
    else
    {
        // Parallel: Sum of all capacities
        double totalCapacity = 0.0;
        for (const Battery *b : cells)
        {
            totalCapacity += b->getCapacity();
        }
        return totalCapacity;
    }
}

/**
 * @brief Calculates the current total charge held by the battery pack.
 * * The calculation depends on the connection type:
 * - **SERIES**: Returns the minimum charge level found among the cells.
 * - **PARALLEL**: Returns the sum of charge levels of all cells.
 * * @return double The current total charge. Returns 0.0 if the pack is empty.
 */
double BatteryPack::getCharge() const
{
    if (cells.empty())
        return 0.0;

    if (type == SERIES)
    {
        // Series: Minimum charge among cells
        double minCharge = cells[0]->getCharge();
        for (size_t i = 1; i < cells.size(); ++i)
        {
            double c = cells[i]->getCharge();
            if (c < minCharge)
            {
                minCharge = c;
            }
        }
        return minCharge;
    }
    else
    {
        // Parallel: Sum of all charges
        double totalCharge = 0.0;
        for (const Battery *b : cells)
        {
            totalCharge += b->getCharge();
        }
        return totalCharge;
    }
}