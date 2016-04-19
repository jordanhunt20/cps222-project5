/*
 * province.h - declarations for the class Province.	CPS222 project 5
 *
 * Copyright Jordan Hunt and Adam Vigneaux
*/

#include <vector>

#include "town.h"


class Province
{
  public:

    /**
     * Constructor
     * @param numTowns number of towns in province
     * @param numRoads number of roads in province
     */
    Province(int numTowns, int numRoads);

    /*
     * Add a town to the province
     * @param town A town
     * @param isCapital Whether or not town is the capital of the province
     */
    void addTown(std::string townName, bool isCapital);


    /*
     * Add a road to the province
     * @param originTown Town that road starts in
     * @param destinationTown Town that road ends in
     * @param type Type of road, either "B" for bridge or "N" for none
     * @param length Length of road in miles
     */
    void addRoad(std::string originTown, std::string destinationTown,
                 char type, int length);

    /*
     * Print all relevant information for towns and roads in this province
    */
    void printAll();

    /**
     * Destructor
     */
    ~Province();

  private:
    int _numTowns;
    int _numRoads;
    std::vector<Town> _towns;
    std::vector<Road> _roads;
    Town _capital;
};
