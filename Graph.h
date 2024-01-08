//
// Created by bruno on 12/28/22.
//

#ifndef UNTITLED_GRAPH_H
#define UNTITLED_GRAPH_H
using namespace std;
#include <string>
#include <set>
#include <list>
#include <vector>

class Graph {
    struct Edge {
        int dest;
        set<string> airlines;
    };

    struct Node {
        list<Edge> adj;
        int dist = -1;
        bool visited;
        vector<int> previous;
    };

    int n;
    vector<Node> nodes;

public:
    /**
     * Graph constructor that receives the number of nodes
     * @param n
     */
    explicit Graph(int n);
    /**
     * Add edge from source to target with weight
     * Time Complexity: O(N)
     * @param source
     * @param target
     * @param airline
     */
    void addEdge(int source, int target, string &airline);
    /**
     * Breath first search implementation
      * Time Complexity: O(V+E)
     * @param source
     */
    void bfs(int source);
    /**
     * Breath first search implementation
     * Time Complexity: O(V+E)
     * @param source
     */
    void bfs1(set<int> source);
    /**
     * shortest path from airport to airport without any specific airline
     * Time Complexity: O(V + E)
     * @param source
     * @param target
     * @return vector of lists of integers, each represents a path
     */
    vector<list<int>> shortestPaths(int source, int target);
    /**
     * shortest path from airport to airport with specific airlines
     * Time Complexity: O(V + E)
     * @param source
     * @param target
     * @param airlines
     * @return vector of lists of integers, each represents a path
     */
    vector<list<int>> shortestPathsAirlines(int source, int target, set<string> &airlines);
    /**
     * shortest path from city to city or location to location without any specific airline
     * Time Complexity: O(V(V + E))
     * @param source
     * @param target
     * @return vector of lists of integers, each represents a path
     */
    vector<list<int>> shortestPaths1(set<int> source, set<int> target);
    /**
     * shortest path from city to city or location to location with specific airlines
     * Time Complexity: O(V(V + E))
     * @param source
     * @param target
     * @param airlines
     * @return vector of lists of integers, each represents a path
     */
    vector<list<int>> shortestPathsAirlines1(set<int> source, set<int> target, set<string> &airlines);
    /**
     * number of possible flights from the airport
     * Time Complexity: O(1)*
     * @param source
     * @return number of flights on the airport
     */
    int getNumFlights(int source);
    /**
     * number of airlines on the airport
     * Time Complexity: O(1)
     * @param source
     * @return number of airlines on the airport
     */
    int getNumAirlines(int source);
    /**
     * number of direct targets from airport
     * @param source
     * @return number of direct targets from airport
     */
    set<int> getTargets(int source);
    /**
     * number of reachable airports from airport
     * Time Complexity: O(V + E)
     * @param source
     * @param hops
     * @return set of all airports reachable from airport
     */
    set<int> reachable(int source, int hops);
};






#endif //UNTITLED_GRAPH_H
