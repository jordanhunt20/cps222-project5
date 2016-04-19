/*
 * project5.cc
 *
 * Main program for CPS222 project 5 - test driver to create and test
 * a graph
 *
 * Copyright Adam Vigneaux and Jordan Hunt
 */

#include <iostream>
#include <string>
#include <list>
#include <vector>


#include "province.h"


bool eof () {
	if (std::cin.eof())
		return true;
	else
	{
		std::cin.unget();
		return false;
	}
}

int main(int argc, char *argv[])
{
    std::vector<Province*> provinces;
    int numProvinces;

    // Repeatedly read input from standard input
    while (!eof()) {
	int numTowns, numRoads;
        std::string townName, originTown, destinationTown;
        char type;
        double length;

        // first two std::cin calls get the number of towns and the number of roads
        std::cin >> numTowns;
        std::cin >> numRoads;
        Province *theProvince = new Province(numTowns, numRoads);

        // add the province to the vector of provinces
        provinces.push_back(theProvince);
        
        // only the first town is the capital
        bool isCapital = true;

        // add the towns to the province
        for (int i = 0; i < numTowns; i++) {
            std::cin >> townName;
            theProvince->addTown(townName, isCapital);
            isCapital = false;
        }

        // add the roads to the province
        for (int i = 0; i < numRoads; i++) {
            std::cin >> originTown;
            std::cin >> destinationTown;
            std::cin >> type;
            std::cin >> length;
            theProvince.addRoad(originTown, destinationTown, type, length);
        }
        numProvinces++;
    }

    // for each province, print out information about cities and roads
    for (int i = 0; i < numProvinces; i++) {
        provinces[i].printAll();
    }
}
