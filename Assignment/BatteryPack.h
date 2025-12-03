#ifndef BATTERYPACK_H
#define BATTERYPACK_H

#include "Battery.h"
#include <vector>

/**
 * @class BatteryPack
 * @brief Represents a pack of batteries, behaving as a single Battery.
 *
 * This class allows multiple Battery objects to be combined in either
 * series or parallel connection and provides methods to use, recharge,
 * and query the pack as a single battery.
 */
class BatteryPack : public Battery
{
public:
    /**
     * @enum ConnectionType
     * @brief Type of connection between battery cells.
     */
    enum ConnectionType
    {
        SERIES,    // Series connection: voltages add, capacity stays the same 
        PARALLEL   // Parallel connection: capacities add, voltage stays the same 
    };

    /**
     * @brief Constructs a BatteryPack with the specified connection type.
     * @param t The type of connection (SERIES or PARALLEL).
     */
    BatteryPack(ConnectionType t);

    /**
     * @brief Adds a battery to the pack.
     * @param b Pointer to the Battery to add.
     */
    void add(Battery *b);

    /**
     * @brief Uses the battery pack for a specified number of hours.
     * @param hours Number of hours to use the battery pack.
     */
    void use(double hours) override;

    /**
     * @brief Recharges the battery pack for a specified number of hours.
     * @param hours Number of hours to recharge the battery pack.
     */
    void recharge(double hours) override;

    /**
     * @brief Returns the total voltage of the battery pack.
     * @return Total voltage as a double.
     */
    double getVoltage() const override;

    /**
     * @brief Returns the total capacity of the battery pack.
     * @return Total capacity as a double.
     */
    double getCapacity() const override;

    /**
     * @brief Returns the current charge of the battery pack.
     * @return Current charge as a double.
     */
    double getCharge() const override;

private:
    ConnectionType type;           //Connection type of the battery pack 
    std::vector<Battery *> cells;  // Vector storing all battery cells in the pack 
};

#endif 