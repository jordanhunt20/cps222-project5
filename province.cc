/*
 * province.cc - implementation of methods of class Province as declared in Province.h.
 *
 * Copyright Jordan Hunt and Adam Vigneaux
 */

#include <iostream>

#include "province.h"

Province::Province(int numTowns, int numRoads)
    : _numTowns(numTowns), _numRoads(numRoads)
{ }


/*
 * Recursive auxiliary function for finding a block containing a key
 * @param1 string specifying key to be found
 * @param2 BTreeBlock number of root to start serach from
 * @return true if found, false if not
*/
void Province::addTown(Town town)
{
}
