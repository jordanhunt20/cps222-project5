/*
 * town.cc - implementation of methods of class Town as declared in Town.h.
 *
 * Copyright Jordan Hunt and Adam Vigneaux
 */

#include <iostream>

#include "Town.h"
#include "Road.h"

Town::Town(std::string name)
: _name(name)
{ }


/*
 * Recursive auxiliary function for finding a block containing a key
 * @param1 string specifying key to be found
 * @param2 BTreeBlock number of root to start serach from
 * @return true if found, false if not
*/
bool BTree::find(std::string key, BTreeFile::BlockNumber & numCurr, std::stack<BTreeFile::BlockNumber> & path) const
{
}

void BTree::print() const
{
    cout << "BTree in file ";
    _file.printHeaderInfo();
    cout << endl;

    BTreeFile::BlockNumber root = _file.getRoot();
    if (root == 0)
        cout << "Empty tree" << endl;
    else
        _file.printBlock(root, true, 1);
}
