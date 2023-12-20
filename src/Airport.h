//
// Created by user on 05-Dec-23.
//

#ifndef AED_2_AIRPORT_H
#define AED_2_AIRPORT_H

#include <vector>
#include <string>

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

    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    double getLatitude() const;
    double getLongitude() const;

    bool operator==(const Airport& other) const;
    bool operator<(const Airport& other) const;
    void print() const;
};


#endif //AED_2_AIRPORT_H
