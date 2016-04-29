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

    // Destructor
    ~Province() { delete [] _town; }

private:
    /* This inner class represents one edge (road) of the graph */
    class Road
    {
    public:

        /*
         * Constructor
         * @param1 head the index in the vertex array of the originating town
         * @param2 type the type of road (either bridge or none)
         * @param3 weight the length of the road
         * TODO: change char type to a boolean or enum
         */
        Road(int head, char type, double weight)
        : _head(head), _type(type), _weight(weight)
        { }

        int _head; // the index in the vertex array of the originating town
        char _type; // the type of the road
        double _weight; // the length of the road
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
    Town *_town;
};
