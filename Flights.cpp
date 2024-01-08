//
// Created by bruno on 1/7/23.
//

#include "Flights.h"

Flights::Flights(string source, string target, string airline) :
source(source),
target(target),
airline(airline){}

string Flights::getSource()const {
    return source;
}

string Flights::getTarget()const {
    return target;
}

string Flights::getAirline()const {
    return airline;
}