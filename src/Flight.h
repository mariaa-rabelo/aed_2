//
// Created by user on 05-Dec-23.
//

#ifndef AED_2_FLIGHT_H
#define AED_2_FLIGHT_H

#include "Airline.h"
class Airport;

class Flight {
private:
    Airport* destination;
    Airline* airline;

public:
    Flight(Airport* destination, Airline* airline);

    Airport* getDestination() const;
    Airline* getAirline() const;
};

#endif //AED_2_FLIGHT_H
