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

/**
 * Province
 * Contains towns connected by roads
 */
class Province
{
public:

    /**
     * Constructor
     * @param source Input data for province
     */
    Province(std::istream & source);

    /**
     * Print towns and roads in province in breadth-first search order
     * @param start Index to start traversal at
     * @param output Stream to print data to
     */
    void bfs(int start, std::ostream & output) const;

    /**
     * Print towns and roads in province in topological sort order
     * @param output Stream to print data to
     */
    void topsort(std::ostream & output) const;

    /**
     * Find shortest path from one town to another
     */
    void findShortestPath();

    /**
     * Destructor
     */
    ~Province() { delete [] _town; }

private:

    /**
     * Road
     * Contains index of originating town, whether or not is bridge,
     * and length
     */
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

        int _head; // Index of originating town in vertex array
        bool _isBridge;
        double _length;
    };

    /**
     * Town
     * Contains name and a list of roads that connect to it
     */
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
