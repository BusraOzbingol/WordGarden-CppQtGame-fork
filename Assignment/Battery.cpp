#include "Battery.h"

/**
 * @brief Constructor for Battery class.
 */
Battery::Battery(double v, double c, double initial)
    : voltage(v), capacity(c) 
{
    // Clamp initial charge between 0 and capacity
    this->charge = std::min(capacity, std::max(0.0, initial)); 
}

/**
 * @brief Use the battery for a certain number of hours.
 * @param hours Number of hours to use.
 */
void Battery::use(double hours) {
    double usage_amount = hours * DISCHARGE_RATE;
    charge -= usage_amount;
    if (charge < 0.0) charge = 0.0;
}

/**
 * @brief Recharge the battery for a certain number of hours.
 * @param hours Number of hours to recharge.
 */
void Battery::recharge(double hours) {
    double recharge_amount = hours * RECHARGE_RATE;
    charge += recharge_amount;
    if (charge > capacity) charge = capacity;
}

/**
 * @brief Get the voltage of the battery.
 * @return Voltage in volts.
 */
double Battery::getVoltage() const {
    return voltage;
}

/**
 * @brief Get the capacity of the battery.
 * @return Capacity in mAh.
 */
double Battery::getCapacity() const {
    return capacity;
}

/**
 * @brief Get the current charge of the battery.
 * @return Current charge in mAh.
 */
double Battery::getCharge() const {
    return charge;
}

/**
 * @brief Get the battery charge as a percentage.
 * @return Charge percentage.
 */
double Battery::getPercent() const {
    double currentCharge = this->getCharge();  
	    double currentCapacity = this->getCapacity(); 
	
	    if (currentCapacity == 0.0) {
	        return 0.0; 
	    }
	    return (currentCharge / currentCapacity) * 100.0;
	}
