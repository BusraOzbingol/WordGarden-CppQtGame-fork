#ifndef BATTERY_H
#define BATTERY_H

#include <iostream>
#include <algorithm>

/**
 * @class Battery
 * @brief Represents a rechargeable battery with voltage, capacity, and current charge.
 * 
 * Provides methods to use, recharge, and check battery status.
 */
class Battery {
private:
    double voltage;   /**< Voltage of the battery in volts */
    double capacity;  /**< Capacity of the battery in mAh */
    double charge;    /**< Current charge in mAh */

public:
    static constexpr double DISCHARGE_RATE = 100.0; /**< Fixed discharge rate (mAh/hour) */
    static constexpr double RECHARGE_RATE = 150.0;  /**< Fixed recharge rate (mAh/hour) */

    /**
     * @brief Constructor for Battery.
     * @param v Voltage in volts.
     * @param c Capacity in mAh.
     * @param initial Initial charge in mAh.
     */
    Battery(double v, double c, double initial);

    /**
     * @brief Discharge the battery by a certain number of hours.
     * @param hours Number of hours to use the battery.
     */
    virtual void use(double hours);

    /**
     * @brief Recharge the battery by a certain number of hours.
     * @param hours Number of hours to recharge.
     */
    virtual void recharge(double hours);

    /**
     * @brief Get the battery voltage.
     * @return Voltage in volts.
     */
    virtual double getVoltage() const;

    /**
     * @brief Get the battery capacity.
     * @return Capacity in mAh.
     */
    virtual double getCapacity() const;

    /**
     * @brief Get the current battery charge.
     * @return Current charge in mAh.
     */
    virtual double getCharge() const;

    /**
     * @brief Get the current battery charge as a percentage.
     * @return Charge percentage (0-100%).
     */
    virtual double getPercent() const;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Battery() {}
};

#endif // BATTERY_H
