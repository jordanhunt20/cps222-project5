/*
 * Class declaration for Graph
 * Copyright Adam Vigneaux and Jordan Hunt
 * Based on files by Dr. Bjork
*/

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
    /* This inner class represents one edge (road) of the graph */
    // TODO: change Edge to Road
    class Edge
    {
    public:

        /*
         * Constructor
         * @param1 head the index in the vertex array of the originating town
         * @param2 type the type of road (either bridge or none)
         * @param3 weight the length of the road
         * TODO: change char type to a boolean or enum
         */
        Edge(int head, char type, double weight)
        : _head(head), _type(type), _weight(weight)
        { }

        int _head; // the index in the vertex array of the originating town
        double _weight; // the length of the road
        char _type; // the type of the road
    };

    /* This inner class represents one vertex (town) of the graph */
    // TODO: change Vertex to Town
    class Vertex
    {
    public:
        std::string _name; // the name of the town represented by the vertex
        typedef std::list < Edge > EdgeList; // declares type EdgeList to be a list of edges
        EdgeList _edges; // list of edges (roads)
    };

    int _numberOfVertices; // number of vertices (towns)
    Vertex * _vertex; // list of vertices (towns)
};
