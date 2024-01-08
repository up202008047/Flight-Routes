//
// Created by bruno on 12/28/22.
//
#include <string>
using namespace std;
#ifndef UNTITLED_AIRLINES_H
#define UNTITLED_AIRLINES_H


class Airlines {
private:
    string code;
    string name;
    string callsign;
    string country;
public:
    /**
     * Creates a new Airline object
     * Time Complexity: O(1)
     * @param code
     * @param name
     * @param callsign
     * @param country
     */
    Airlines(string code,string name, string callsign, string country);
    /**
     * Returns the code of the airline
     * Time Complexity: O(1)
     * @return the code of the airline
     */
    string getCode()const;
    /**
     * Returns the name of the airline
     * Time Complexity: O(1)
     * @return the name of the airline
     */
    string getName()const;
    /**
     *Returns the callsign of the airline
     * Time Complexity: O(1)
     * @return the callsign of the airline
     */
    string getCallSign()const;
    /**
     * Returns the country of the airline
     * Time Complexity: O(1)
     * @return the country of the airline
     */
    string getCountry()const;
};


#endif //UNTITLED_AIRLINES_H
