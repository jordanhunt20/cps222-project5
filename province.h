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
class Province
{
public:

    // Constructor - construct a representation from a text file
    Province(std::istream & source);

    // BFS traversal from a specified starting vertex
    // - write vertex names to a text file
    void bfs(int start, std::ostream & output) const;

    // Write out the vertices in topological order
    void topsort(std::ostream & output) const;

    void findShortestPath();

    // Destructor
    ~Province() { delete [] _town; }

private:
    /* This inner class represents one edge (road) of the graph */
    class Road
    {
    public:

        /*
         * Constructor
         * @param head Index in vertex array of originating town
         * @param isBridge Whether or not the road is a bridge
         * @param length Length of the road in miles
         */
        Road(int head, bool isBridge, double length)
            : _head(head), _isBridge(isBridge), _length(length)
        {}

        int _head; // the index in the vertex array of the originating town
        bool _isBridge;
        double _length;
    };

    /* This inner class represents one vertex (town) of the graph */
    class Town
    {
    public:
        std::string _name;
        typedef std::list <Road> RoadList;
        RoadList _roads;
    };

    int _numberOfTowns;
    int _numberOfRoads;
    Town *_town;
};
