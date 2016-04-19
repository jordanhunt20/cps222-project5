/*
 * road.cc - implementation of methods of class Road as declared in Road.h.
 *
 * Copyright Jordan Hunt and Adam Vigneaux
 */

#include <iostream>
using std::cout;

#include "Road.h"


Road::Road(string name)
: _file(* new RoadFile(name))
{ }


/*
*/
bool Road::find(string key, RoadFile::BlockNumber & numCurr, std::stack<RoadFile::BlockNumber> & path) const
{
}

void Road::print() const
{
    cout << "Road in file ";
    _file.printHeaderInfo();
    cout << endl;

    RoadFile::BlockNumber root = _file.getRoot();
    if (root == 0)
        cout << "Empty tree" << endl;
    else
        _file.printBlock(root, true, 1);
}