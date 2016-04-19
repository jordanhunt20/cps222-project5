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
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using std::cin;
using std::cout;

#include "province.h"


bool eof (std::cin) {
	if (std::cin.eof())
		return false;
	else
	{
		std::cin.unget();
		return true;	
	}
}

int main(int argc, char * argv[])
{
	std::list <Province> provinces;


    // Repeatedly read input from standard input
    while (!eof(std::cin)) {
		HighwayNetwork network(std::cin);
	}
	
}
