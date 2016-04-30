/*
 * Implentation of Province.h
 * Copyright 2016 Adam Vigneaux and Jordan Hunt
 * Based on algorithms by Dr. Bjork
 */

#include "province.h"

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
void Province::bfs(int start, std::ostream &output) const
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
