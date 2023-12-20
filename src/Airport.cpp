//
// Created by user on 19-Dec-23.
//
#include <iostream>
#include "Airport.h"

Airport::Airport(const std::string& code, const std::string& name, const std::string& city, const std::string& country, double latitude, double longitude)
        : code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {
}

std::string Airport::getCode() const{
    return code;
}
std::string Airport::getCity() const {
    return city;
}

std::string Airport::getName() const {
    return name;
}

std::string Airport::getCountry() const {
    return country;
}

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}


bool Airport::operator==(const Airport& other) const {
    return code == other.code;
}
bool Airport::operator<(const Airport& other) const{
    if (latitude < other.latitude){
        return true;
    }
    else if (latitude == other.latitude){
        return longitude < other.longitude;
    }
    else{
        return false;
    }
}

void Airport::print() const{
    std::cout << "Name: " << name << "; " << "Code: " << code << "; " << "City: " << city <<  "; " << "Country: " << country << std::endl;
}



