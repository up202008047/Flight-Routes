//
// Created by bruno on 1/7/23.
//

#ifndef UNTITLED_UTILS_H
#define UNTITLED_UTILS_H

#include <unordered_map>
#include "Graph.h"
#include "Airport.h"

class Utils {
public:
    /**
     * Airports codes that will be stored
     */
    typedef unordered_map<string, int> Codes;
    /**
     * Airports info that will be stored
     */
    typedef unordered_map<int, Airport> Airports;
    /**
     * Cities that will be stored
     */
    typedef unordered_map<string, set<int>> Cities;

    /**
     * Clears menu screen
     */
    void clearScreen();
    /**
     * Start menu
     */
    void StartMenu();
    /**
     * Reads airport data and stores it
     * Time Complexity: O(n)
     * @param codes
     * @param airports
     * @param cities
     */
    void readAirports(Codes &codes, Airports &airports, Cities &cities);
    /**
     * Read flights data and stores it
     * Time Complexity: O(n)
     * @param codes
     * @param graph
     */
    void readFlights(const Codes codes, Graph &graph);
    /**
     * Routes menu
     * Time Complexity: O(n)
     * @param codes
     * @param airports
     * @param cities
     * @param graph
     */
    void Menu(const Codes codes, const Airports airports, const Cities cities, Graph graph);
    /**
     * Menu to select specific airlines to travel
     * Time Complexity: O(n)
     * @return none or specfic airlines to travel
     */
    set<string> airlineChoice();
    /**
     * shortest path between airports
     * @param codes
     * @param airports
     * @param graph
     * @param airlines
     */
    void routeAirports(const Codes codes, const Airports airports, Graph graph, set<string> airlines);
    /**
     * shortest path between cities;
     * @param codes
     * @param airports
     * @param cities
     * @param graph
     * @param airlines
     */
    void routeCities(const Codes codes, const Airports airports, const Cities cities, Graph graph, set<string> airlines);
    /**
     * shortest path between locations(lat,long)
     * @param codes
     * @param airports
     * @param graph
     * @param airlines
     */
    void routeLocations(const Codes codes, const Airports airports, Graph graph, set<string> airlines);
    /**
     * menu to display airports information and possible targets with X number of flights
     * @param codes
     * @param airports
     * @param graph
     */
    void airportsInfo(const Codes codes, const Airports airports, Graph graph);
};


#endif //UNTITLED_UTILS_H
