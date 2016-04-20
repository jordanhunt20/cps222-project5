#include <iostream>
#include <string>
#include <list>
#include <map>
#include <queue>

/*******************************************************************************
* The following class represents a graph by using an adjacency list
******************************************************************************/
class Graph
{
public:
    // Constructor - construct a representation from a text file
    Graph(std::istream & source);
    // BFS traversal from a specified starting vertex
    // - write vertex names to a text file
    void bfs(int start, std::ostream & output) const;
    // Write out the vertices in topological order
    void topsort(std::ostream & output) const;
    // Destructor
    ~Graph()
    { delete [] _vertex; }

private:
    /* This inner class represents one edge of the graph */
    class Edge
    {
    public:

        Edge(int head, char type, double weight)
        : _head(head), _type(type), _weight(weight)
        { }

        int _head;
        // **** IF REPRESENTING A WEIGHTED GRAPH (NETWORK) ADD THE ****
        // **** FOLLOWING, USING SOME NUMERIC TYPE (E.G.double) ****
        // **** ALSO ADD A weight PARAMETER TO THE CONSTRUCTOR ****
        double _weight;
        char _type;
    };

    /* This inner class represents one vertex of the graph */
    class Vertex
    {
    public:
        std::string _name;
        typedef std::list < Edge > EdgeList;
        EdgeList _edges;
    };

    int _numberOfVertices;
    Vertex * _vertex;
};
