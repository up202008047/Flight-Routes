//
// Created by bruno on 12/28/22.
//

#include "Graph.h"
#include <algorithm>
#include <queue>

Graph::Graph(int n) :n(n), nodes(n){}

void Graph::addEdge(int source, int target, string &airline) {
    auto it=find_if(nodes[source].adj.begin(),nodes[source].adj.end(),[target](Edge &e){return e.dest==target;});
    if (it==nodes[source].adj.end()) {
        nodes[source].adj.push_back({target,{airline}});
    } else {
        it->airlines.insert(airline);
    }
}

void Graph::bfs(int source) {
    for (auto &node : nodes) {
        node.dist = -1;
        node.visited = false;
        node.previous.clear();
    }

    queue<int> q;
    q.push(source);
    nodes[source].dist = 0;
    nodes[source].visited = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto &edge : nodes[node].adj) {
            if (!nodes[edge.dest].visited) {
                nodes[edge.dest].dist = nodes[node].dist + 1;
                nodes[edge.dest].visited = true;
                nodes[edge.dest].previous.push_back(node);
                q.push(edge.dest);
            } else if (nodes[edge.dest].dist == nodes[node].dist + 1) {
                nodes[edge.dest].previous.push_back(node);
            }
        }
    }
}

void Graph::bfs1(set<int> source) {
    for (auto &node : nodes) {
        node.dist = -1;
        node.visited = false;
        node.previous.clear();
    }

    queue<int> q;
    for (auto &s : source) {
        q.push(s);
        nodes[s].dist = 0;
        nodes[s].visited = true;
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto &edge : nodes[node].adj) {
            if (!nodes[edge.dest].visited) {
                nodes[edge.dest].dist = nodes[node].dist + 1;
                nodes[edge.dest].visited = true;
                nodes[edge.dest].previous.push_back(node);
                q.push(edge.dest);
            } else if (nodes[edge.dest].dist == nodes[node].dist + 1) {
                nodes[edge.dest].previous.push_back(node);
            }
        }
    }
}

int Graph::getNumFlights(int source) {
    return nodes[source].adj.size();
}

int Graph::getNumAirlines(int source) {
    set<string> airlines;
    for(auto e=nodes[source].adj.begin();e!=nodes[source].adj.end();e++) {
        for(auto a=e->airlines.begin();a!=e->airlines.end();a++) {
            airlines.insert(*a);
        }
    }
    return airlines.size();
}

set<int> Graph::getTargets(int source) {
    set<int> targets;
    for(auto e=nodes[source].adj.begin();e!=nodes[source].adj.end();e++) {
        targets.insert(e->dest);
    }
    return targets;

}

set<int> Graph::reachable(int source, int hops) {

    set<int> reachable;
    bfs(source);
    for(int i=0; i<nodes.size();i++) {
        if (nodes[i].dist<=hops&&nodes[i].dist!=-1) {
            reachable.insert(i);
        }
    }
    return reachable;
}

vector <list<int>> Graph::shortestPaths(int source, int target) {
    bfs(source);

    vector<list<int>> paths;
    if (nodes[target].dist == -1) return paths;

    queue<list<int>> q;
    q.push({target});

    while (!q.empty()) {
        list<int> path = q.front();
        q.pop();

        int node = path.front();
        if (node == source) {
            paths.push_back(path);
        } else {
            for (auto &previous : nodes[node].previous) {
                list<int> newPath = path;
                newPath.push_front(previous);
                q.push(newPath);
            }
        }
    }

    auto it = paths.begin();
    while (it != paths.end()) {
        if (it->size() != nodes[target].dist + 1) {
            it = paths.erase(it);
        } else {
            it++;
        }
    }

    return paths;
}

vector <list<int>> Graph::shortestPaths1(set<int> source, set<int> target) {
    bfs1(source);

    vector<list<int>> paths;
    for (auto &d : target) {
        if (nodes[d].dist == -1) continue;

        queue<list<int>> q;
        q.push({d});

        while (!q.empty()) {
            list<int> path = q.front();
            q.pop();

            int node = path.front();
            if (find(source.begin(), source.end(), node) != source.end()) {
                paths.push_back(path);
            } else {
                for (auto &previous : nodes[node].previous) {
                    list<int> newPath = path;
                    newPath.push_front(previous);
                    q.push(newPath);
                }
            }
        }
        auto it = paths.begin();
        while (it != paths.end()) {
            if (it->size() != nodes[d].dist + 1) {
                it = paths.erase(it);
            } else {
                it++;
            }
        }
    }

    return paths;
}

vector <list<int>> Graph::shortestPathsAirlines(int source, int target, set <string> &airlines) {
    bfs(source);

    vector<list<int>> paths;
    if (nodes[target].dist == -1) return paths;

    queue<list<int>> q;
    q.push({target});

    while (!q.empty()) {
        list<int> path = q.front();
        q.pop();

        int node = path.front();
        if (node == source) {
            paths.push_back(path);
        } else {
            for (auto &previous : nodes[node].previous) {
                bool valid = false;
                for (auto &edge : nodes[previous].adj) {
                    if (edge.dest == node) {
                        for (auto &airline : edge.airlines) {
                            if (find(airlines.begin(), airlines.end(), airline) != airlines.end()) {
                                valid = true;
                                break;
                            }
                        }
                        break;
                    }
                }

                if (valid) {
                    list<int> newPath = path;
                    newPath.push_front(previous);
                    q.push(newPath);
                }
            }
        }
    }

    auto it = paths.begin();
    while (it != paths.end()) {
        if (it->size() != nodes[target].dist + 1) {
            it = paths.erase(it);
        } else {
            it++;
        }
    }

    return paths;
}

vector <list<int>> Graph::shortestPathsAirlines1(set<int> source, set<int> target, set <string> &airlines) {
    bfs1(source);

    vector<list<int>> paths;
    for (auto &d : target) {
        if (nodes[d].dist == -1) continue;

        queue<list<int>> q;
        q.push({d});

        while (!q.empty()) {
            list<int> path = q.front();
            q.pop();

            int node = path.front();
            if (find(target.begin(), target.end(), node) != target.end()) {
                paths.push_back(path);
            } else {
                for (auto &previous : nodes[node].previous) {
                    bool valid = false;
                    for (auto &edge : nodes[previous].adj) {
                        if (edge.dest == node) {
                            for (auto &airline : edge.airlines) {
                                if (find(airlines.begin(), airlines.end(), airline) != airlines.end()) {
                                    valid = true;
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    if (valid) {
                        list<int> newPath = path;
                        newPath.push_front(previous);
                        q.push(newPath);
                    }
                }
            }
        }

        auto it = paths.begin();
        while (it != paths.end()) {
            if (it->size() != nodes[d].dist + 1) {
                it = paths.erase(it);
            } else {
                it++;
            }
        }
    }

    return paths;
}