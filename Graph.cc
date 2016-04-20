#include "Graph.h"

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
Graph::Graph(std::istream & source)
{
    // Read number of vertices and number of edges

    int numberOfEdges;

    source >> _numberOfVertices >> numberOfEdges;

    // Read in names of vertices. Add a Vertex object for each to the
    // _vertex array, and also temporarily store its name in a map to
    // facilitate reading in the edge descriptions by vertex name

    _vertex = new Vertex[_numberOfVertices];
    std::map < std::string, int > nameMap;

    for (int i = 0; i < _numberOfVertices; i ++) {
        std::string name;
        source >> name;
        _vertex[i]._name = name;
        nameMap[name] = i;
    }

    // Read in edges. Add an edge node for each to the adjacency
    // list for its vertices

    for (int i = 0; i < numberOfEdges; i ++) {
        std::string tail, head;
        source >> tail >> head;
        int tailIndex = nameMap[tail];
        int headIndex = nameMap[head];

        char type;
        source >> type;

        // **** FOR A NETWORK, ADD THE FOLLOWING LINES, AND ADD weight AS A ****
        // **** PARAMETER TO THE Edge CONSTRUCTOR IN THE SUBSEQUENT LINE(S) ****
        double weight;
        source >> weight;


        _vertex [ tailIndex ]._edges.push_back(Edge(headIndex, type, weight));
        // ** THE FOLLOWING LINE WOULD BE OMITTED FOR A DIGRAPH **
        _vertex [ headIndex ]._edges.push_back(Edge(tailIndex, type, weight));
    }
}



/*******************************************************************************
* BFS on an adjacency list
******************************************************************************/
void Graph::bfs(int start, std::ostream & output) const
{

    output << "------------------------------------------------" << std::endl;
    output << "---------------- New DataSet: ------------------" << std::endl;
    output << "------------------------------------------------" << std::endl;
    // Keep track of whether a vertex has been scheduled to be visited, lest
    // we get into a loop

    output << std::endl << std::endl;

    bool scheduled [ _numberOfVertices ];
    for (int i = 0; i < _numberOfVertices; i ++) {
        scheduled[i] = false;
    }

    std::queue < int > toVisit;
    toVisit.push(start);
    scheduled[start] = true;
    output << "The input data is:" << std::endl << std::endl;
    while (! toVisit.empty())
    {
        // Visit front vertex on the queue

        int current = toVisit.front(); toVisit.pop();
        output << "      ";
        output << _vertex [ current ]._name << std::endl;

        // Enqueue its unscheduled neighbors

        for (Vertex::EdgeList::iterator neighbor = _vertex[current]._edges.begin();
        neighbor != _vertex[current]._edges.end(); neighbor ++)
        {
            std::string neighborName = _vertex[neighbor -> _head]._name;
            output << "            ";
            output << neighborName << " " << neighbor -> _weight << " mi";
            if (neighbor -> _type == 'B') {
                output << " via bridge";
            }
            output << std::endl;
            int head = neighbor -> _head;
            if (! scheduled[head])
            {
                toVisit.push(head);
                scheduled[head] = true;
            }
        }
    }

    output << std::endl << std::endl;
}


/*******************************************************************************
* Topological sorting - using an adjacency list (two versions)
******************************************************************************/
void Graph::topsort(std::ostream & output) const
{
    // Record two facts for every vertex: whether it has been visited, and
    // the count of predecessors that have not yet been visited. The
    // latter is initialized to zero, then 1 is added for the head of
    // every edge

    bool visited [ _numberOfVertices ];
    int unvisitedPredecessors [ _numberOfVertices ];

    for (int i = 0; i < _numberOfVertices; i ++) {
        visited[i] = false;
        unvisitedPredecessors[i] = 0;
    }

    for (int i = 0; i < _numberOfVertices; i ++) {
        for (Vertex::EdgeList::iterator iter = _vertex[i]._edges.begin();
        iter != _vertex[i]._edges.end();
        iter ++)
        unvisitedPredecessors [ iter -> _head ] ++;
    }
    // Use a queue of visitable vertices - ones that have no unvisited
    // predecessors. Initially, this queue contains all vertices that
    // have not predecessors in the initial graph

    std::queue < int > visitable;
    for (int i = 0; i < _numberOfVertices; i ++) {
        if (unvisitedPredecessors[i] == 0) {
            visitable.push(i);
        }
    }


    // Output the vertices in topological order. The following loop must
    // be done n times if all vertices are visited

    for (int i = 0; i < _numberOfVertices; i ++)
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

        output << _vertex[current]._name << std::endl;
        visited[current] = true;

        // Reduce predecessor count for its successors. If any drops to
        // zero, add it to the visitable queue

        for (Vertex::EdgeList::iterator iter = _vertex[current]._edges.begin();
        iter != _vertex[current]._edges.end();
        iter ++)
        {
            unvisitedPredecessors[ iter -> _head ] --;
            if (unvisitedPredecessors[ iter -> _head ] == 0)
            visitable.push(iter -> _head);
        }
    }
}
