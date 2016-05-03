/*
 * Implentation of Province.h
 * Copyright 2016 Adam Vigneaux and Jordan Hunt
 * Based on algorithms by Dr. Bjork
 */

#include "province.h"
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
Province::Province(std::istream & source)
{
    // Read first line of input
    source >> _numberOfTowns >> _numberOfRoads;

    _town = new Town[_numberOfTowns];
    std::map <std::string, int> nameMap;

    // Read town names
    for (int i = 0; i < _numberOfTowns; i++) {
        source >> _town[i]._name;
        nameMap[_town[i]._name] = i;
    }

    // Read roads
    for (int i = 0; i < _numberOfRoads; i++) {
        std::string tail, head;
        source >> tail >> head;
        int tailIndex = nameMap[tail]; // index of the first town
        int headIndex = nameMap[head]; // index of the second town

        // Get type of road (B for bridge, N for normal)
        char type;
        source >> type;
        bool isBridge = (type == 'B');

        // Get length of road
        double length;
        source >> length;

        // Add road to both towns it connects
        _town[tailIndex]._roads.push_back(Road(headIndex, isBridge, length));
        _town[headIndex]._roads.push_back(Road(tailIndex, isBridge, length));
    }
}

/*
 * Print list of towns and roads in province in
 * breadth-first search order
 * @param start Index to start traversal at
 * @param output Output stream to write to
 */
void Province::printAll(int start, std::ostream &output) const
{

    output << "------------------------------------------------" << std::endl;
    output << "---------------- New DataSet: ------------------" << std::endl;
    output << "------------------------------------------------" << std::endl;

    // Keep track of whether a vertex has been scheduled to be visited, lest
    // we get into a loop
    output << std::endl << std::endl;

    // keeps track of which vertices have been visited
    bool scheduled [_numberOfTowns];
    for (int i = 0; i < _numberOfTowns; i++) {
        scheduled[i] = false; // default false value for each vertex
    }

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
        output << _town[current]._name << std::endl;

        // Enqueue current vertex's unscheduled neighbors
        for (Town::RoadList::iterator neighbor = _town[current]._roads.begin();
             neighbor != _town[current]._roads.end(); neighbor++) {

            std::string neighborName = _town[neighbor->_head]._name;

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

int Province::smallest(double dist [], std::list <int> toVisit, int numTowns) const
{
    int smallest = toVisit.front();

    if (toVisit.size() > 1) {
        for (int i = 0; i < numTowns; i++) {
            if (dist[i] < dist[smallest] ) {
                bool found = (std::find(toVisit.begin(), toVisit.end(), i) != toVisit.end());
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
void Province::printShortest(std::ostream & output) const
{
    output << "------------------------------------------------" << std::endl;
    output << "------------------------------------------------" << std::endl;

    output << "The shortest routes from " + _town[0]._name;
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
        for (Town::RoadList::iterator neighbor = _town[smallestIndex]._roads.begin();
        neighbor != _town[smallestIndex]._roads.end(); neighbor++) {
            
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
        output << "      " << "The shortest route from " + _town[0]._name;
        output << " to " + _town[i]._name + " is " << dist[i];
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
            output << "            " << _town[predecessors.top()]._name << std::endl;
            predecessors.pop();
        }
    }

    output << "------------------------------------------------" << std::endl;
    output << "------------------------------------------------" << std::endl;
}


/**
 * Print towns and roads in province in topological sort order
 * @param output Stream to print data to
 */
void Province::topsort(std::ostream & output) const
{
    // Record two facts for every vertex: whether it has been visited, and
    // the count of predecessors that have not yet been visited. The
    // latter is initialized to zero, then 1 is added for the head of
    // every edge

    bool visited [_numberOfTowns];
    int unvisitedPredecessors [_numberOfTowns];

    for (int i = 0; i < _numberOfTowns; i ++) {
        visited[i] = false;
        unvisitedPredecessors[i] = 0;
    }

    for (int i = 0; i < _numberOfTowns; i++) {
        for (Town::RoadList::iterator iter = _town[i]._roads.begin();
             iter != _town[i]._roads.end();
             iter++) {
            unvisitedPredecessors[iter->_head]++;
        }
    }

    // Use a queue of visitable vertices - ones that have no unvisited
    // predecessors. Initially, this queue contains all vertices that
    // have not predecessors in the initial graph

    std::queue < int > visitable;
    for (int i = 0; i < _numberOfTowns; i++) {
        if (unvisitedPredecessors[i] == 0) {
            visitable.push(i);
        }
    }


    // Output the vertices in topological order. The following loop must
    // be done n times if all vertices are visited

    for (int i = 0; i < _numberOfTowns; i++) {
        // Find an unvisited vertex with no unvisited predecessors. (If
        // none can be found, graph contains a cycle.)

        int current;
        if (!visitable.empty()) {
            current = visitable.front();
            visitable.pop();
        } else {
            output << "Province contains a cycle - topological sort impossible"
            << std::endl;
            return;
        }

        // Visit the vertex

        output << _town[current]._name << std::endl;
        visited[current] = true;

        // Reduce predecessor count for its successors. If any drops to
        // zero, add it to the visitable queue
        for (Town::RoadList::iterator iter = _town[current]._roads.begin();
        iter != _town[current]._roads.end();
        iter ++) {
            unvisitedPredecessors[iter->_head]--;
            if (unvisitedPredecessors[iter->_head] == 0)
            visitable.push(iter->_head);
        }
    }
}
