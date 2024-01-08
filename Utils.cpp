//
// Created by bruno on 1/7/23.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Utils.h"

void Utils::clearScreen() {
    cout<<string(50,'\n');
}

void Utils::readAirports(Codes &codes, Airports &airports, Cities &cities) {
    ifstream file("../data/airports.csv");

    string l;
    getline(file, l);
    while (getline(file, l)) {
        istringstream iss(l);
        string code; string name; string city; string country; double latitude; double longitude;

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        iss >> latitude;
        iss.ignore();
        iss >> longitude;
        codes.insert({code, codes.size()});
        airports.insert({codes[code], Airport(code, name, city, country, latitude, longitude)});
        cities[city].insert(codes.size() - 1);
    }
}

void Utils::readFlights(const Codes codes, Graph &graph) {
    ifstream file("../data/flights.csv");

    string l;
    getline(file, l);

    while (getline(file, l)) {
        istringstream iss(l);
        string airline, src, dest;

        getline(iss, src, ',');
        getline(iss, dest, ',');
        getline(iss, airline, ',');

        graph.addEdge(codes.at(src), codes.at(dest), airline);
    }
}


void Utils::StartMenu() {
    Codes codes;
    Airports airports;
    Cities cities;

    readAirports(codes,airports,cities);
    Graph graph(codes.size());
    readFlights(codes, graph);
    clearScreen();
    char choice;
    do{
        cout << endl << "=========================================================" << endl;
        cout << "\t\t\tOptions:" << endl;
        cout << "1. Find the shortest route" << endl;
        cout << "2. Airports Information" << endl << endl;
        cout << "Select 'q' to quit!" << endl;
        cout << "Select 'c' to clear!" << endl;
        cout << "=========================================================" << endl;
        cout << "Option:" ;
        cin >> choice;
        cout << endl;

        switch (choice) {
            case '1':
                Menu(codes, airports, cities, graph);
                break;
            case '2':
                airportsInfo(codes, airports, graph);
                break;
            case 'q':
                break;
            case 'c':
                clearScreen();
                break;
            default:
                cout << "  Invalid option" << endl;
                break;
        }



    } while (choice!='q');
}

void Utils::Menu(const Codes codes, const Airports airports, const Cities cities, Graph graph) {
    clearScreen();

    char choice;
    do{
        cout << endl << "=========================================================" << endl;
        cout << "\t\t\tSearch by:" << endl;
        cout << "1. Codes" << endl;
        cout << "2. Cities" << endl;
        cout << "3. Coordinates" << endl;
        cout << "Select 'q' to go back!" << endl;
        cout << "=========================================================" << endl;
        cout << "Option:" ;
        cin >> choice;
        cout << endl;

        set<string>airlines;
        if((choice == '1' || choice || '2' || choice == '3')&& choice !='q') airlines = airlineChoice();

        switch (choice) {
            case '1':
                routeAirports(codes,airports,graph,airlines);
                break;
            case '2':
                routeCities(codes,airports,cities,graph,airlines);
                break;
            case '3':
                routeLocations(codes,airports,graph,airlines);
                break;
            case 'q':
                StartMenu();
                break;
            case 'c':
                clearScreen();
                break;
            default:
                cout << "  Invalid option" << endl;
                break;
        }



    } while (choice!='q');
}

set<string> Utils::airlineChoice() {
    clearScreen();
    char choice;
    cout << endl << "=========================================================" << endl;
    cout << "\t\t\tPreference in Airlines:" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl << endl;
    cout << " " << endl;
    cout << " " << endl;
    cout << "=========================================================" << endl;
    cin >> choice;
    cout << endl;
    set<string> airlines;
    switch (choice) {
        case '1': {
            cout << "Airlines (enter '0' to end):" << endl;
            string airline;
            while (airline != "0") {
                cout << "Airline:";

                cin >> airline;
                if (airline != "2") airlines.insert(airline);
            }
            return airlines;
            break;
        }
        case '2':
            break;
        default:
            cout << "  Invalid option" << endl;
            break;

    }
}

void Utils::routeAirports(const Codes codes, const Airports airports, Graph graph, set<string> airlines) {
    clearScreen();

    string src, dest;
    cout << endl << "=========================================================" << endl;
    cout << "\t\t\tRoute:" << endl;
    cout << "  Source airport code:";
    cin >> src;
    cout << "  Destination airport code:";
    cin >> dest;
    cout << " " << endl;
    cout << " " << endl;
    cout << "=========================================================" << endl;


    vector<list<int>> paths;
    if (airlines.empty()) {
        paths = graph.shortestPaths(codes.at(src), codes.at(dest));
    } else {
        paths = graph.shortestPathsAirlines(codes.at(src), codes.at(dest), airlines);
    }


    if (paths.size() == 0) cout << "  No route found" << endl;
    else {
        cout << "  Routes found:" << endl;
        for (auto &list : paths) {
            for (auto &airport : list) {
                cout << " ---> " << airports.at(airport).getName();
            }
            cout << endl;
        }
    }

    cout << endl << "  Press enter to continue...";
    cin.ignore(); cin.get();

    clearScreen();
}

void
Utils::routeCities(const Codes codes, const Airports airports, const Cities cities, Graph graph, set<string> airlines) {
    clearScreen();

    string src, dest;
    cout << endl << "=========================================================" << endl;
    cout << "\t\t\tRoute:" << endl;
    cout << "  Source City:";
    cin >> src;
    cout << "  Destination City:";
    cin >> dest;
    cout << " " << endl;
    cout << " " << endl;
    cout << "=========================================================" << endl;

    vector<list<int>> paths;
    if (airlines.empty()) {
        paths = graph.shortestPaths1(cities.at(src), cities.at(dest));
    } else {
        paths = graph.shortestPathsAirlines1(cities.at(src), cities.at(dest), airlines);
    }


    if (paths.size() == 0) cout << "  No route found" << endl;
    else {
        cout << "  Routes found:" << endl;
        for (auto &list : paths) {
            for (auto &airport : list) {
                cout << "--->" << airports.at(airport).getName();
            }
            cout << endl;
        }
    }

    cout << endl << "  Press enter to continue...";
    cin.ignore(); cin.get();

    clearScreen();
}

void Utils::routeLocations(const Codes codes, const Airports airports, Graph graph, set<string> airlines) {
    clearScreen();

    double srcLat, srcLong, destLat, destLong, range;
    cout << endl << "=========================================================" << endl;
    cout << "\t\t\tRoute:" << endl;
    cout << "  Source latitude:";
    cin >> srcLat;
    cout << "  Source longitude:";
    cin >> srcLong;
    cout << endl << "  Destination latitude:";
    cin >> destLat;
    cout << "  Destination longitude:";
    cin >> destLong;
    cout << "=========================================================" << endl;


    cout << endl << "  Specify the range:";
    cin >> range;

    set<int> srcAirports, destAirports;

    for (auto &pair : airports) {
        if(pair.second.haversine(srcLat,srcLong,pair.second.getLatitude(),pair.second.getLongitude())<=range) srcAirports.insert(pair.first);
        if(pair.second.haversine(destLat,destLong,pair.second.getLatitude(),pair.second.getLongitude())<=range) destAirports.insert(pair.first);
    }

    if (srcAirports.empty() || destAirports.empty()) {
        cout << endl << "=========================================================" << endl;
        cout << "  No airports found in the specified range" << endl;
        cout << " " << endl;
        cout << " " << endl;
        cout << endl << "  Press enter to continue...";
        cout << endl << "=========================================================" << endl;
        cin.ignore(); cin.get();
        clearScreen();
        return;
    }

    vector<list<int>> paths;
    if (airlines.empty()) {
        paths = graph.shortestPaths1(srcAirports, destAirports);
    } else {
        paths = graph.shortestPathsAirlines1(srcAirports, destAirports, airlines);
    }

    if (paths.size() == 0) cout << "  No route found" << endl;
    else {
        cout << "  Routes found:" << endl;
        for (auto &list : paths) {
            for (auto &airport : list) {
                cout << "--->" << airports.at(airport).getName();
            }
            cout << endl;
        }
    }

    cout << endl << "  Press enter to continue...";
    cin.ignore(); cin.get();

    clearScreen();
}

void Utils::airportsInfo(const Codes codes, const Airports airports, Graph graph) {
    clearScreen();

    cout << "  Airport code:";
    string code;
    cin >> code;

    clearScreen();

    if (codes.find(code) == codes.end()) {
        cout << endl << "=========================================================" << endl;
        cout << "  Invalid airport code" << endl;
        cout << " " << endl;
        cout << " " << endl;
        cout << endl << "  Press enter to continue...";
        cout << endl << "=========================================================" << endl;
        cin.ignore(); cin.get();
        clearScreen();
        return;
    }
    int airport = codes.at(code);
    set<int> destinations = graph.getTargets(airport);

    cout << endl << "=========================================================" << endl;
    cout << "  Number of flights from " << code << ": " << graph.getNumFlights(airport) << endl;
    cout << "  Number of airlines on " << code << ": " << graph.getNumAirlines(airport) << endl;
    cout << "  Number of destinations from " << code << ": " << destinations.size() << endl;
    cout << " " << endl;


    set<string> cities, countries;
    for (auto &dest : destinations) {
        cities.insert(airports.at(dest).getCity());
        countries.insert(airports.at(dest).getCountry());
    }
    cout << "  Number of cities with direct flights from " << code << ": " << cities.size() << endl;
    cout << "  Number of countries with direct flights from " << code << ": " << countries.size() << endl;

        cout << endl << "  Insert maximum number of flights:";
    int hops;
    cin >> hops;
    cout << endl;

    set<int> reachable = graph.reachable(airport, hops);

    cout << "  Number of airports reachable from " << code << " in " << hops << " flights: " << reachable.size() << endl;
    cities.clear();
    countries.clear();
    for (auto &dest : reachable) {
        cities.insert(airports.at(dest).getCity());
        countries.insert(airports.at(dest).getCountry());
    }

    cout << "  Number of cities reachable from " << code << " in " << hops << " flights: " << cities.size() << endl;
    cout << "  Number of countries reachable from " << code << " in " << hops << " flights: " << countries.size() << endl;
    cout << endl << "=========================================================" << endl;

    cout << endl << "  Press enter to continue...";
    cin.ignore(); cin.get();

    clearScreen();
}