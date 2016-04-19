/*
 * road.cc - implementation of methods of class Road as declared in Road.h.
 *
 * Copyright Jordan Hunt and Adam Vigneaux
 */

#include <iostream>
using std::cout;

#include "Road.h"


Road::Road(std::string name)
: _file(* new Road(name))
{ }


/*
*/
bool Road::find(std::string key, Road::BlockNumber & numCurr, std::stack<Road::BlockNumber> & path) const
{
}
