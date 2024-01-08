//
// Created by bruno on 1/7/23.
//

#ifndef UNTITLED_FLIGHTS_H
#define UNTITLED_FLIGHTS_H
#include <string>
using namespace std;

class Flights {
private:
    string source;
    string target;
    string airline;
public:
    /**
     * Creates new flight object
     * Time Complexity: O(1)
     * @param source
     * @param target
     * @param airline
     */
    Flights(string source, string target, string airline);
    /**
     * Returns source airport code of the flight
     * Time Complexity: O(1)
     * @return source airport code of the flight
     */
    string getSource()const;
    /**
     * Returns target airport code of the flight
     * Time Complexity: O(1)
     * @return target airport code of the flight
     */
    string getTarget()const;
    /**
     * Returns airline of the flight
     * Time Complexity: O(1)
     * @return airline of the flight
     */
    string getAirline()const;
};


#endif //UNTITLED_FLIGHTS_H
