//
// Created by user on 05-Dec-23.
//

#ifndef AED_2_AIRPORT_H
#define AED_2_AIRPORT_H

#include <vector>
#include "Flight.h"

class Airport {
private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;

public:
    Airport(const std::string& code, const std::string& name, const std::string& city, const std::string& country, double latitude, double longitude);

    // Add getter functions as needed
    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    double getLatitude() const;
    double getLongitude() const;

    bool operator==(const Airport& other) const;
};


#endif //AED_2_AIRPORT_H
