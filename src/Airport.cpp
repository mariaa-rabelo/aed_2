//
// Created by user on 19-Dec-23.
//
#include "Airport.h"

Airport::Airport(const std::string& code, const std::string& name, const std::string& city, const std::string& country, double latitude, double longitude)
        : code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {
}

bool Airport::operator==(const Airport& other) const {
    return code == other.code;
}

std::string Airport::getCode() const{
    return code;
}
