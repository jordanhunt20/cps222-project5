/*
 * province.cc - implementation of methods of class Province as declared in Province.h.
 *
 * Copyright Jordan Hunt and Adam Vigneaux
 */

#include <iostream>

#include "province.h"

/**
 * Constructor
 * @param numTowns number of towns in province
 * @param numRoads number of roads in province
 */
Province::Province(int numTowns, int numRoads)
    : _numTowns(numTowns), _numRoads(numRoads)
{ }


/*
 * Add a town to the province
 * @param town A town
 * @param isCapital Whether or not town is the capital of the province
 */
void Province::addTown(Town town, bool isCapital)
{
}

/*
 * Add a road to the province
 * @param originTown Town that road starts in
 * @param destinationTown Town that road ends in
 * @param type Type of road, either "B" for bridge or "N" for none
 * @param length Length of road in miles
 */
void addRoad(std::string originTown, std::string destinationTown,
                 char type, int length)
{ }
