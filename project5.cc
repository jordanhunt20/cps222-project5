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
#include "Graph.h"




bool eof ()
{
    char c;
    std::cin >> c;
	if (std::cin.eof()) {
		return true;
    } else {
		std::cin.unget();
		return false;
	}
}

int main(int argc, char *argv[])
{

    // Repeatedly read input from standard input
    while (!eof()) {
        Graph theGraph(std::cin);

        theGraph.bfs(0, std::cout);
    }
}
