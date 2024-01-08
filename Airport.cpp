//
// Created by bruno on 12/28/22.
//

#include "Airport.h"
#include "math.h"
Airport::Airport(string code, string name, string city, string country, double latitude,double longitude):
                 code(code),
                 name(name),
                 city(city),
                 country(country),
                 latitude(latitude),
                 longitude(longitude) {}

string Airport::getCode()const {
    return code;
}

string Airport::getName() const {
    return name;
}

string Airport::getCountry() const {
    return country;
}

string Airport::getCity() const {
    return city;
}

double Airport::getLatitude() const{
    return latitude;
}
double Airport::getLongitude() const{
    return longitude;
}

double Airport::haversine(double lat1, double lon1,
                 double lat2, double lon2) const
{

    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}