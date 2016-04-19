/*
 * province.cc - implementation of methods of class Province as declared in Province.h.
 *
 * Copyright Jordan Hunt and Adam Vigneaux
 */

#include <iostream>
using std::cout;

#include "province.h"
#include "town.h"
#include "road.h"

Province::Province(string name)
: _name(name)
{ }


/*
 * Recursive auxiliary function for finding a block containing a key
 * @param1 string specifying key to be found
 * @param2 BTreeBlock number of root to start serach from
 * @return true if found, false if not
*/
bool Province::addTown(Town town)
{
}

void Province::print() const
{
}
