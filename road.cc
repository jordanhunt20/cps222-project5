/*
 * road.cc - implementation of methods of class Road as declared in Road.h.
 *
 * Copyright Jordan Hunt and Adam Vigneaux
 */

#include "road.h"

Road::Road(std::string originTown, std::string destinationTown,
                 char type, int length)
                 : _originTown(originTown), _destinationTown(destinationTown),
                 _type(type), _length(length)
{ }

Road::~Road()
{ }
