//
// Created by user on 05-Dec-23.
//

#ifndef AED_2_AIRLINE_H
#define AED_2_AIRLINE_H

#include <string>

class Airline {
private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

public:
    Airline(const std::string& code, const std::string& name, const std::string& callsign, const std::string& country);

    std::string getCode() const;
    std::string getName() const;
    std::string getCallsign() const;
    std::string getCountry() const;
    bool operator<(const Airline& other) const;
};


#endif //AED_2_AIRLINE_H
