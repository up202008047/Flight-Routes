//
// Created by bruno on 12/28/22.
//
#include <string>
using namespace std;
#ifndef UNTITLED_AIRPORT_H
#define UNTITLED_AIRPORT_H


class Airport {
private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;
public:
    /**
     * Creates a new airport object
     * Time Complexity: O(1)
     * @param code
     * @param name
     * @param city
     * @param country
     * @param latitude
     * @param longitude
     */
    Airport(string code, string name, string city, string country, double latitude, double longitude);
    /**
     * Returns code of the airport
     * Time Complexity: O(1)
     * @return code of the airport
     */
    string getCode()const;
    /**
     * Returns name of the airport
     * Time Complexity: O(1)
     * @return name of the airport
     */
    string getName() const;
    /**
     * Returns city of the airport
     * Time Complexity: O(1)
     * @return city of the airport
     */
    string getCity() const;
    /**
     * Returns country of the airport
     * Time Complexity: O(1)
     * @return country of the airport
     */
    string getCountry() const;
    /**
     * Returns latitude of the airport
     * Time Complexity: O(1)
     * @return latitude of the airport
     */
    double getLatitude()const ;
    /**
     * Returns longitude of the airport
     * Time Complexity: O(1)
     * @return longitude of the airport
     */
    double getLongitude()const ;

    /**
 * Calculates the shortest distance between two points on a sphere using their latitude and longitude.
 *
 * @details Time Complexity: O(log(n))
 *
 * @param lat1 Latitude of the first point
 * @param lat2 Latitude of the second point
 * @param long1 Longitude of the first point
 * @param long2 Longitude of the second point
 * @return Distance between the two points in Kms
 */
    double haversine(double lat1, double lon1,double lat2, double lon2) const;};


#endif //UNTITLED_AIRPORT_H
