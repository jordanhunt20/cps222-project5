#include "Graph.h"

/*
* Implentation of Graph.h
* Copyright Adam Vigneaux and Jordan Hunt
* based on algorithms from Dr. Bjork
*/

/*******************************************************************************
* Read a graph from a file into an adjacency list
* File format: first line: number of vertices (N), number of edges (E)
* next N lines: names of N vertices
* next E lines: edges - each specified by tail vertex name,
* head vertex name.
* This file format and code can be used for either an undirected graph or a
* digraph - see line marked with ** below. It can also be used for a network
* if we add a weight to each edge line - see lines marked with **** below
******************************************************************************/
/*
 * Constructor
 * @param1 source the data stram to read from
*/
Graph::Graph(std::istream & source)
{
    // Read number of vertices and number of edges

    // TODO: make this an instance variable like _numberOfVertices
    int numberOfEdges; // number of edges in the graph

    // read the number of vertices and number of edges in the graph
    source >> _numberOfTowns >> numberOfEdges;

    // Read in names of vertices. Add a Vertex object for each to the
    // _vertex array, and also temporarily store its name in a map to
    // facilitate reading in the edge descriptions by vertex name

    _town = new Town[_numberOfTowns];
    std::map < std::string, int > nameMap;

    // for each vertex representing a town, read in the
    // name of the town and create a vertex and add the name to the
    // map of vertex names
    for (int i = 0; i < _numberOfTowns; i ++) {
        std::string name;
        source >> name;
        _town[i]._name = name;
        nameMap[name] = i;
    }

    // Read in edges. Add an edge node for each to the adjacency
    // list for its vertices

    // for each edge representing a road, read in the
    // starting and ending towns, and add the road to the
    // list of roads for both towns
    for (int i = 0; i < numberOfEdges; i ++) {
        std::string tail, head;
        source >> tail >> head;
        int tailIndex = nameMap[tail]; // index of the first town
        int headIndex = nameMap[head]; // index of the second town

        // get the type of the road
        char type;
        source >> type;

        // get the weight of the road
        double weight;
        source >> weight;

        // add the roads to both towns
        _town[ tailIndex ]._roads.push_back(Road(headIndex, type, weight));
        _town[ headIndex ]._roads.push_back(Road(tailIndex, type, weight));
    }
}



/*******************************************************************************
* BFS on an adjacency list
******************************************************************************/
/*
 * writes information about towns and their roads in breadth first order
 * @param1 start the index in the vertices list of the town to begin the bfs at
 * @param2 output the output stream to write to
 */
void Graph::bfs(int start, std::ostream & output) const
{

    output << "------------------------------------------------" << std::endl;
    output << "---------------- New DataSet: ------------------" << std::endl;
    output << "------------------------------------------------" << std::endl;
    // Keep track of whether a vertex has been scheduled to be visited, lest
    // we get into a loop

    output << std::endl << std::endl;

    // keeps track of which vertices have been visited
    bool scheduled [ _numberOfTowns ];
    for (int i = 0; i < _numberOfTowns; i ++) {
        scheduled[i] = false; // default false value for each vertex
    }

    // queue to keep track of which vertex to visit next
    std::queue < int > toVisit;
    toVisit.push(start);
    scheduled[start] = true;
    output << "The input data is:" << std::endl << std::endl;

    // go through the loop until the queue is empty
    while (! toVisit.empty())
    {
        // Visit front vertex on the queue
        int current = toVisit.front(); toVisit.pop();
        output << "      "; // formatting
        output << _town [ current ]._name << std::endl;

        // Enqueue its unscheduled neighbors
        for (Town::RoadList::iterator neighbor = _town[current]._roads.begin();
        neighbor != _town[current]._roads.end(); neighbor ++)
        {
            std::string neighborName = _town[neighbor -> _head]._name;
            output << "            "; // formatting
            output << neighborName << " " << neighbor -> _weight << " mi";

            // if the type is bridge, then add to output
            if (neighbor -> _type == 'B') {
                output << " via bridge";
            }
            output << std::endl; // formatting

            int head = neighbor -> _head;

            // if the neighbor has not yet been scheduled, add it to the
            // toVisit queue
            if (! scheduled[head])
            {
                toVisit.push(head);
                scheduled[head] = true;
            }
        }
    }

    output << std::endl << std::endl;
}

/* TODO: comment out this function when we use it later */
/*******************************************************************************
* Topological sorting - using an adjacency list (two versions)
******************************************************************************/
void Graph::topsort(std::ostream & output) const
{
    // Record two facts for every vertex: whether it has been visited, and
    // the count of predecessors that have not yet been visited. The
    // latter is initialized to zero, then 1 is added for the head of
    // every edge

    bool visited [ _numberOfTowns ];
    int unvisitedPredecessors [ _numberOfTowns ];

    for (int i = 0; i < _numberOfTowns; i ++) {
        visited[i] = false;
        unvisitedPredecessors[i] = 0;
    }

    for (int i = 0; i < _numberOfTowns; i ++) {
        for (Town::RoadList::iterator iter = _town[i]._roads.begin();
        iter != _town[i]._roads.end();
        iter ++)
        unvisitedPredecessors [ iter -> _head ] ++;
    }
    // Use a queue of visitable vertices - ones that have no unvisited
    // predecessors. Initially, this queue contains all vertices that
    // have not predecessors in the initial graph

    std::queue < int > visitable;
    for (int i = 0; i < _numberOfTowns; i ++) {
        if (unvisitedPredecessors[i] == 0) {
            visitable.push(i);
        }
    }


    // Output the vertices in topological order. The following loop must
    // be done n times if all vertices are visited

    for (int i = 0; i < _numberOfTowns; i ++)
    {
        // Find an unvisited vertex with no unvisited predecessors. (If
        // none can be found, graph contains a cycle.)

        int current;
        if (! visitable.empty())
        {
            current = visitable.front();
            visitable.pop();
        }
        else
        {
            output << "Graph contains a cycle - topological sort impossible"
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
        iter ++)
        {
            unvisitedPredecessors[ iter -> _head ] --;
            if (unvisitedPredecessors[ iter -> _head ] == 0)
            visitable.push(iter -> _head);
        }
    }
}
