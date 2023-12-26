//
// Created by user on 20-Dec-23.
//
#include "Airline.h"

Airline::Airline(const std::string& code, const std::string& name, const std::string& callsign, const std::string& country)
: code(code), name(name), callsign(callsign), country(country){
}

std::string Airline::getCode() const{
    return code;
}
bool Airline::operator<(const Airline& other) const {
    return this->getCode() < other.getCode();
}

std::string Airline::getName() const {
    return name;
}

std::string Airline::getCallsign() const {
    return callsign;
}

std::string Airline::getCountry() const {
    return country;
}
