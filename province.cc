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
 * @return      True if road1 is shorter in length than road 2
 */
bool Province::Road::operator < (Road road2) const {
    return this->_length < road2._length;
}

/**
 * Find minimum spanning tree of the province
 * @param output Stream to print output to
 */
void Province::minSpan(std::ostream & output) const {
    std::list<Road> roads;
    std::vector<Road> minSpanTree;
    std::vector<int> higher;
    
    // Initialize a numComponent value for each town to 0
    int numComponent[_numberOfTowns];
    for (int i = 0; i < _numberOfTowns; i++) {
        numComponent[i] = 0;
    }
    
    // Add all roads to list of roads
    for (int i = 0; i < _numberOfRoads; i++) {
        roads.push_back(_roads[i]);
    }

    // Sort list of roads by length
    roads.sort();

    int compNum = 0;  // Used to determine if edge forms a cycle
    while (minSpanTree.size() < _numberOfTowns - 1) {
        Road minRoad = roads.front();
        roads.pop_front();

        // Both towns have component number 0
        if (numComponent[minRoad._head] == 0 &&
            numComponent[minRoad._tail] == 0) {
            minSpanTree.push_back(minRoad);
            compNum++;
            numComponent[minRoad._head] = compNum;
            numComponent[minRoad._tail] = compNum;

        // Only one town has component number 0
        } else if (numComponent[minRoad._head] == 0) {
            minSpanTree.push_back(minRoad);
            numComponent[minRoad._head] = numComponent[minRoad._tail];

        // Other town has component number 0
        } else if (numComponent[minRoad._tail] == 0) {
            minSpanTree.push_back(minRoad);
            numComponent[minRoad._tail] = numComponent[minRoad._head];

        // If component number of one town is less than other town
        } else if (numComponent[minRoad._head] <
                   numComponent[minRoad._tail]) {
            minSpanTree.push_back(minRoad);
            higher.push_back(minRoad._tail);

            // Set all higher road components to value of lower
            for (int i = 0; i < higher.size(); i++) {
                higher[i] = numComponent[minRoad._head];
            }

        // If component number of other town is less than other town
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

    // Print names of towns in minimum spanning tree of province
    for (int i = 0; i < minSpanTree.size(); i++) {
        output << "      ";
        output << _towns[minSpanTree[i]._head]._name;
        output << " to ";
        output << _towns[minSpanTree[i]._tail]._name << std::endl;
    }
}

/**
 * Conduct a breadth-first traversal on the province, ignoring bridges
 * @param start Index of town to start traversal at
 * @return      List of indices of towns in order of traversal
 */
std::vector<int> Province::bfs(int start) const {
    // Initialize list of towns scheduled to visit
    bool scheduled[_numberOfTowns];
    for (int i = 0; i < _numberOfTowns; i ++) {
        scheduled[i] = false;
    }

    // Initialize list of towns to visit with starting town
    std::queue<int> toVisit;
    toVisit.push(start);

    scheduled[start] = true;
    std::vector<int> results;

    // While all towns have not been visited
    while (!toVisit.empty()) {

        // Remove current town from queue, add to results
        int current = toVisit.front();
        toVisit.pop();
        results.push_back(current);

        // Iterate over neighbors to current town
        for (Town::RoadList::iterator neighbor =
                 _towns[current]._roads.begin();
             neighbor != _towns[current]._roads.end();
             neighbor ++) {

            // If neighbor is not bridge and is not scheduled,
            // add to results and schedule
            if (!neighbor->_isBridge && !scheduled[neighbor->_head]) {
                toVisit.push(neighbor->_head);
                scheduled[neighbor->_head] = true;
            }
        }
    }

    return results;
}

/**
 * Remove bridges and print the list of towns that remain connected
 * 1. Remove all bridges
 * 2. Make a list of towns to visit
 * 3. Run a BFS from a town, remove that town and all reached towns
 *    from list to visit, then print all towns in that connected
 *    component.
 * 4. Repeat step 3 for all remaining towns.
 * @param output Stream to print output to
 */
void Province::removeBridges(std::ostream &output) const {
    // Mark all towns as unvisited
    std::list<int> toVisit;
    for (int i = 0; i < _numberOfTowns; i++) {
        toVisit.push_back(i);
    }

    output << "Connected components in event of a major storm are: ";
    output << std::endl << std::endl;

    // While not all towns have been visited
    while (!toVisit.empty()) {

        // Mark current town as visited
        int curr = toVisit.back();
        toVisit.pop_back();

        // Run BFS from current town
        std::vector<int> bfsResult = bfs(curr);

        // Mark all towns in BFS result as visited
        for (int i = 0; i < bfsResult.size(); i++) {
            toVisit.remove(bfsResult[i]);
        }

        output << "      ";
        output << "If all bridges fail, the following towns would form ";
        output << "an isolated group:" << std::endl;

        // Print names of all towns in connected component
        for (int i = 0; i < bfsResult.size(); i++) {
            output << "            ";
            output << _towns[bfsResult[i]]._name << std::endl;
        }
    }
}

/**
 * Perform a depth-first search on province
 * @param dfsTowns List to populate with results of search
 */
void Province::dfs(std::vector<int> &dfsTowns) const {
    bool visited [ _numberOfTowns ];
    for (int i = 0; i < _numberOfTowns; i++) {
        visited[i] = false;
    }
    dfsAux(0, dfsTowns, visited);
}

/**
 * Auxiliary function for recursive depth-first search
 * @param current Current index
 * @param dfsTowns List to populate with results of search
 * @param visited List of visited town indices
 */
void Province::dfsAux(int current, std::vector<int> &dfsTowns,
                      bool visited[]) const {
    visited[current] = true;
    dfsTowns.push_back(current);

    // Do a DFS recursively from each of its neighbors
    for (Town::RoadList::iterator neighbor =
             _towns[current]._roads.begin();
         neighbor != _towns[current]._roads.end();
         neighbor ++) {
        if (!visited[neighbor->_head]) {
            dfsAux(neighbor->_head, dfsTowns, visited);
        }
    }
}

/**
 * Get Low V for a vertex, determined by the minimum of the following:
 * 1. currNumV - vertex number in DFS traversal
 * 2. lowV - low value of any child in DFS tree
 * 3. numV - num value of any node reachable by following a back edge
 * @param vertexNumV Number value in DFS tree of current vertex
 * @param lowV       List of low values of vertices in DFS tree
 * @param numV       List of number values of vertices in DFS tree
 * @return           Low value of current vertex
 */
int getLowV(int vertexNumV, int lowV[], int numV[],
            std::vector<int> dfsTowns) {

    int vertexLowV = vertexNumV;

    // Look for lower value in list of vertex low values
    for (int i = 0; i < dfsTowns.size(); i++) {
        int currLowV = lowV[dfsTowns[i]];
        vertexLowV = std::min(currLowV, vertexLowV);
    }

    // Look for lower value in nodes reachable by following back edge
    
    
    return vertexLowV;
}

void Province::articulationPoints(std::ostream & output) const {
    std::vector<int> dfsTowns;
    int numV[_numberOfTowns];
    int lowV[_numberOfTowns];
    std::vector<Road> roadsUsed;
    std::vector<Road> backRoads;
    std::list<Road> allRoads;
    for (int i = 0; i < _numberOfRoads; i++) {
        allRoads.push_back(_roads[i]);
    }

    // Do depth-first traversal
    dfs(dfsTowns);

    // Number vertices in order visited
    for (int i = 0; i < dfsTowns.size(); i++) {
        numV[dfsTowns[i]] = i;
    }

    // Do a reverse depth-first traversal
    for (int i = dfsTowns.size() - 1; i >= 0; i--) {

        int currLowV = getLowV(numV[dfsTowns[i]], lowV, numV,
                               dfsTowns);
        lowV[dfsTowns[i]] = currLowV;
        
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
