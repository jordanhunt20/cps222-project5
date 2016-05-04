/*
* Implentation of Province.h
* Copyright 2016 Adam Vigneaux and Jordan Hunt
* Based on algorithms by Dr. Bjork
*/

#include "./province.h"
#include <algorithm>
#include <stack>

/*
* Constructor
* @param source File containing province:
*               1. One line: number of towns (n), number of roads (p)
*                  as integers
*               2. n lines: names of towns, all uppercase
*               3. p lines: roads, defined as names of towns they
*                  connect, bridge/not bridge, and length in miles
*                  ex: BEVERLY DANVERS N 2.9 (connects Beverly and
*                      Danvers, not a bridge, 2.9 miles long)
*/
Province::Province(std::istream & source) {
    // Read first line of input
    source >> _numberOfTowns >> _numberOfRoads;

    _towns = new Town[_numberOfTowns];

    std::map <std::string, int> nameMap;

    // Read town names
    for (int i = 0; i < _numberOfTowns; i++) {
        source >> _towns[i]._name;
        nameMap[_towns[i]._name] = i;
    }

    // Read roads
    for (int i = 0; i < _numberOfRoads; i++) {
        std::string tail, head;
        source >> tail >> head;
        int tailIndex = nameMap[tail];  // index of the first town
        int headIndex = nameMap[head];  // index of the second town

        // Get type of road (B for bridge, N for normal)
        char type;
        source >> type;
        bool isBridge = (type == 'B');

        // Get length of road
        double length;
        source >> length;

        // Add road to road list
        Road newRoad(headIndex, tailIndex, isBridge, length);
        _roads.push_back(newRoad);

        // Add road to both towns it connects
        _towns[tailIndex]._roads.push_back(Road(headIndex, tailIndex,
            isBridge, length));
        _towns[headIndex]._roads.push_back(Road(tailIndex, headIndex,
            isBridge, length));
    }
}

/*
* Print list of towns and roads in province in
* breadth-first search order
* @param start Index to start traversal at
* @param output Output stream to write to
*/
void Province::printAll(int start, std::ostream &output) const {

    // Keep track of whether a vertex has been scheduled to be visited, lest
    // we get into a loop
    bool scheduled[_numberOfTowns];
    for (int i = 0; i < _numberOfTowns; i++) {
        scheduled[i] = false;  // default false value for each vertex
    }

    // keeps track of which vertices have been visited
    // queue to keep track of which vertex to visit next
    std::queue <int> toVisit;
    toVisit.push(start);
    scheduled[start] = true;
    output << "The input data is:" << std::endl << std::endl;

    // Visit each town in queue
    while (!toVisit.empty()) {
        // Visit front vertex in the queue
        int current = toVisit.front();
        toVisit.pop();

        output << "      ";
        output << _towns[current]._name << std::endl;

        // Enqueue current vertex's unscheduled neighbors
        for (Town::RoadList::iterator neighbor = _towns[current]._roads.begin();
        neighbor != _towns[current]._roads.end(); neighbor++) {
            std::string neighborName = _towns[neighbor->_head]._name;

            output << "            ";
            output << neighborName << " " << neighbor->_length << " mi";

            // if the type is bridge, then add to output
            if (neighbor->_isBridge) {
                output << " via bridge";
            }

            output << std::endl;

            int head = neighbor->_head;

            // Add neighbor to queue if not scheduled
            if (!scheduled[head]) {
                toVisit.push(head);
                scheduled[head] = true;
            }
        }
    }

    output << std::endl << std::endl;
}

int Province::smallest(double dist[], std::list <int> toVisit,
    int numTowns) const {
    int smallest = toVisit.front();

    if (toVisit.size() > 1) {
        for (int i = 0; i < numTowns; i++) {
            if (dist[i] < dist[smallest]) {
                bool found = (std::find(toVisit.begin(), toVisit.end(), i)
                                != toVisit.end());
                if (found) {
                    smallest = i;
                }
            }
        }
    }
    return smallest;
}

/**
* Print the shortest route from the capital of the
* province to each of the other towns
* algorithm found at graphs lecture notes under
* "Single-Source" All Destinations Shortest Path
* @param output stream to write to
*/
void Province::printShortest(std::ostream & output) const {
    output << "The shortest routes from " + _towns[0]._name;
    output << " are:" << std::endl << std::endl;

    // keeps track of the index of the predecessor to each
    // vertex n on the shortest path to n
    int prev[_numberOfTowns];

    // queue to keep track of which vertex to visit next
    std::list <int> toVisit;

    // keeps track of the distance from the capital to each town
    // following the shortest path
    double dist[_numberOfTowns];


    // set defaults for dist, prev, and add all vertices to toVisit
    for (int i = 0; i < _numberOfTowns; i++) {
        dist[i] = 100000000.0;
        toVisit.push_back(i);
    }

    // distance from the capital to the capital is zero
    dist[0] = 0.0;

    while (!toVisit.empty()) {
        int smallestIndex = smallest(dist, toVisit, _numberOfTowns);

        toVisit.remove(smallestIndex);

        // Enqueue current vertex's neighbors
        for (Town::RoadList::iterator neighbor =
            _towns[smallestIndex]._roads.begin();
            neighbor != _towns[smallestIndex]._roads.end(); neighbor++) {
            // new distance needed for testing
            double newDist = dist[smallestIndex] + neighbor->_length;

            // if new dist is smaller, replace the old one, and
            // update the corresponding entry in prev
            if (newDist < dist[neighbor->_head]) {
                dist[neighbor->_head] = newDist;
                prev[neighbor->_head] = smallestIndex;
            }
        }
    }

    // print out the data for each non capital town
    for (int i = 1; i < _numberOfTowns; i++) {
        output << "      " << "The shortest route from " + _towns[0]._name;
        output << " to " + _towns[i]._name + " is " << dist[i];
        output << " mi:" << std::endl;

        // stack to hold the path to the town at index i
        std::stack <int> predecessors;

        // add town at i to stack
        int predecessor = i;
        predecessors.push(i);

        // follow the links in prev until we get to the capital,
        // adding each town to the predecessor stack
        while (predecessor != 0) {
            predecessor = prev[predecessor];
            predecessors.push(predecessor);
        }

        // print out the names for each entry in the stack
        while (!predecessors.empty()) {
            output << "            " << _towns[predecessors.top()]._name;
            output << std::endl;
            predecessors.pop();
        }
    }
}


/**
 * Overloads operator < when used to compare two roads
 * @param road2 A road
 * Returns true if road1 has a smaller length than road 2
 */
bool Province::Road::operator < (Road road2) const {
    return this->_length < road2._length;
}

void Province::minSpan(std::ostream & output) const {
    // initialize a numComponent value for each town to 0
    int numComponent[_numberOfTowns];
    for (int i = 0; i < _numberOfTowns; i++) {
        numComponent[i] = 0;
    }

    std::list<Road> roads;
    std::vector<Road> minSpanTree;

    for (int i = 0; i < _numberOfRoads; i++) {
        roads.push_back(_roads[i]);
    }

    roads.sort();

    std::vector<int> higher;

    int compNum = 0;
    while (minSpanTree.size() < _numberOfTowns - 1) {
        Road minRoad = roads.front();
        roads.pop_front();
        if (numComponent[minRoad._head] == 0 &&
          numComponent[minRoad._tail] == 0) {
            minSpanTree.push_back(minRoad);
            compNum++;
            numComponent[minRoad._head] = compNum;
            numComponent[minRoad._tail] = compNum;
        } else if (numComponent[minRoad._head] == 0) {
            minSpanTree.push_back(minRoad);
            numComponent[minRoad._head] = numComponent[minRoad._tail];
        } else if (numComponent[minRoad._tail] == 0) {
            minSpanTree.push_back(minRoad);
            numComponent[minRoad._tail] = numComponent[minRoad._head];
        } else if (numComponent[minRoad._head] <
          numComponent[minRoad._tail]) {
            minSpanTree.push_back(minRoad);
            higher.push_back(minRoad._tail);

            // Set all higher road components to value of lower
            for (int i = 0; i < higher.size(); i++) {
                higher[i] = numComponent[minRoad._head];
            }
        } else if (numComponent[minRoad._head] >
          numComponent[minRoad._tail]) {
            minSpanTree.push_back(minRoad);
            higher.push_back(minRoad._head);

            // Set all higher road components to value of lower
            for (int i = 0; i < higher.size(); i++) {
                higher[i] = numComponent[minRoad._tail];
            }
        }
    }
    output << "The road upgrading goal can be achieved at minimal cost by upgrading:";
    output << std::endl << std::endl;
    for (int i = 0; i < minSpanTree.size(); i++) {
        output << "      ";
        output << _towns[minSpanTree[i]._head]._name;
        output << " to ";
        output << _towns[minSpanTree[i]._tail]._name << std::endl;
    }

}

/*******************************************************************************
* BFS on an adjacency list
******************************************************************************/
std::vector<int> Province::bfs(int start) const {
    // Keep track of whether a vertex has been scheduled to be visited, lest
    // we get into a loop

    bool scheduled [ _numberOfTowns ];
    for (int i = 0; i < _numberOfTowns; i ++)
    scheduled[i] = false;

    std::queue<int> toVisit;
    toVisit.push(start);
    scheduled[start] = true;
    std::vector<int> results;

    while (! toVisit.empty()) {
        // Visit front vertex on the queue

        int current = toVisit.front(); toVisit.pop();
        results.push_back(current);

        // Enqueue its unscheduled neighbors

        for (Town::RoadList::iterator neighbor =
          _towns[current]._roads.begin();
          neighbor != _towns[current]._roads.end();
          neighbor ++) {
            if (!neighbor->_isBridge) {
                int head = neighbor -> _head;
                if (! scheduled[head]) {
                    toVisit.push(head);
                    scheduled[head] = true;
                }
            }
        }
    }

    return results;
}

void Province::removeBridges(std::ostream & output) const {
    // queue to keep track of which vertex to visit next
    std::list<int> toVisit;

    // set defaults for dist, prev, and add all vertices to toVisit
    for (int i = 0; i < _numberOfTowns; i++) {
        toVisit.push_back(i);
    }
    output << "Connected components in event of a major storm are: ";
    output << std::endl << std::endl;
    while (!toVisit.empty()) {
        int curr = toVisit.back();
        toVisit.pop_back();
        std::vector<int> bfsResult = bfs(curr);
        for (int i = 0; i < bfsResult.size(); i++) {
            toVisit.remove(bfsResult[i]);
        }
        output << "      ";
        output << "If all bridges fail, the following towns would form ";
        output << "an isolated group:" << std::endl;
        for (int i = 0; i < bfsResult.size(); i++) {
            output << "            ";
            output << _towns[bfsResult[i]]._name << std::endl;
        }
    }
}

/*******************************************************************************
* DFS on an adjacency matrix
******************************************************************************/
// The most straight-forward implementation uses a recursive auxiliary
void Province::dfs(std::vector<int> & dfsTowns) const // RECURSIVE VERSION
{
    // Keep track of whether a vertex has been visited, lest we get into a loop
    bool visited [ _numberOfTowns ];
    for (int i = 0; i < _numberOfTowns; i ++)
        visited[i] = false;
    dfsAux(0, dfsTowns, visited);
}
void Province::dfsAux(int current, std::vector<int> & dfsTowns, bool visited []) const
{
    visited[current] = true;
    dfsTowns.push_back(current);
    // Do a DFS recursively from each of its neighbors
    for (Town::RoadList::iterator neighbor =
            _towns[current]._roads.begin();
            neighbor != _towns[current]._roads.end();
            neighbor ++) {
        if (! visited[neighbor->_head])
        {
            dfsAux(neighbor->_head, dfsTowns, visited);
        }
    }
}

void Province::articulationPoints(std::ostream & output) const {
    std::vector<int> dfsTowns;
    int numV [_numberOfTowns];
    std::vector<Road> roadsUsed;
    std::vector<Road> backRoads;
    std::list<Road> allRoads;
    for (int i = 0; i < _numberOfRoads; i++) {
        allRoads.push_back(_roads[i]);
    }
    
    dfs(dfsTowns);
    for (int i = 0; i < dfsTowns.size(); i++) {
        numV[dfsTowns[i]] = i;
    }

    for (int i = 0; i < dfsTowns.size() - 1; i++) {
        for (std::list<Road>::iterator neighbor =
                allRoads.begin();
                neighbor != allRoads.end();
                neighbor ++) {
            if (neighbor->_head == dfsTowns[i]) {
                if (neighbor->_tail == dfsTowns[i + 1]) {

                }
            } else if (neighbor->_tail == dfsTowns[i]) {
                if (neighbor->_head == dfsTowns[i + 1]) {

                }
            }
        }
    }
}
