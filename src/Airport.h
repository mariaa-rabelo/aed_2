/**
 * @file Airport.h
 * @brief Defines the Airport class, representing an airport with various attributes.
 * @date 05-Dec-2023
 */

#ifndef AED_2_AIRPORT_H
#define AED_2_AIRPORT_H

#include <vector>
#include <string>

/**
 * @class Airport
 * @brief Represents an airport with various details such as code, name, city, country, and geographical coordinates.
 */
class Airport {
private:
    std::string code;      ///< Code of the airport.
    std::string name;      ///< Name of the airport.
    std::string city;      ///< City where the airport is located.
    std::string country;   ///< Country where the airport is located.
    double latitude;       ///< Latitude of the airport.
    double longitude;      ///< Longitude of the airport.

public:
    /**
     * @brief Constructor for the Airport class.
     * @param code Code of the airport.
     * @param name Name of the airport.
     * @param city City where the airport is located.
     * @param country Country where the airport is located.
     * @param latitude Latitude of the airport.
     * @param longitude Longitude of the airport.
     */
    Airport(const std::string& code, const std::string& name, const std::string& city, const std::string& country, double latitude, double longitude);

    /**
     * @brief Gets the code of the airport.
     * @return Code of the airport.
     */
    std::string getCode() const;

    /**
    * @brief Gets the name of the airport.
    * @return Name of the airport.
    */
    std::string getName() const;

    /**
     * @brief Gets the city where the airport is located.
     * @return City of the airport.
     */
    std::string getCity() const;

    /**
     * @brief Gets the country where the airport is located.
     * @return Country of the airport.
     */
    std::string getCountry() const;

    /**
     * @brief Gets the latitude of the airport.
     * @return Latitude of the airport.
     */
    double getLatitude() const;

    /**
     * @brief Gets the longitude of the airport.
     * @return Longitude of the airport.
     */
    double getLongitude() const;

    /**
     * @brief Compares this airport to another based on their properties.
     * @param other The other airport to compare with.
     * @return True if this airport is equal to the other.
     */
    bool operator==(const Airport& other) const;

    /**
     * @brief Defines a less-than comparison for airports, based on their code.
     * @param other The other airport to compare with.
     * @return True if this airport's code is less than the other's.
     */
    bool operator<(const Airport& other) const;

    /**
     * @brief Prints the details of the airport.
     */
    void print() const;
};


#endif //AED_2_AIRPORT_H
