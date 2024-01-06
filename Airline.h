/**
 * @file Airline.h
 * @brief Defines the Airline class, representing an airline.
 * @date 05-Dec-2023
 */

#ifndef AED_2_AIRLINE_H
#define AED_2_AIRLINE_H

#include <string>

/**
 * @class Airline
 * @brief Represents an airline with a code, name, callsign, and country.
 */
class Airline {
private:
    std::string code; ///< Code of the airline.
    std::string name; ///< Name of the airline.
    std::string callsign; ///< Callsign of the airline.
    std::string country; ///< Country of the airline.

public:
    /**
     * @brief Constructor for the Airline class.
     * @param code Code of the airline.
     * @param name Name of the airline.
     * @param callsign Callsign of the airline.
     * @param country Country of the airline.
     */
    Airline(const std::string& code, const std::string& name, const std::string& callsign, const std::string& country);

    /**
     * @brief Gets the code of the airline.
     * @return Code of the airline.
     */
    std::string getCode() const;

    /**
     * @brief Gets the name of the airline.
     * @return Name of the airline.
     */
    std::string getName() const;

    /**
     * @brief Gets the callsign of the airline.
     * @return Callsign of the airline.
     */
    std::string getCallsign() const;

    /**
     * @brief Gets the country of the airline.
     * @return Country of the airline.
     */
    std::string getCountry() const;

    /**
     * @brief Compares this airline to another based on its code.
     * @param other The other airline to compare with.
     * @return True if this airline's code is less than the other's.
     */
    bool operator<(const Airline& other) const;
};


#endif //AED_2_AIRLINE_H
