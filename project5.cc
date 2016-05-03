/*
* project5.cc
*
* Main program for CPS222 project 5 - test driver to read in a graph
* from standard input and test the read graph
*
* Copyright Adam Vigneaux and Jordan Hunt
* Based on files by Dr. Bjork
*/

#include <iostream>
#include <string>
#include "./province.h"

/*
* check if we are at the end of the file
* @return true or false depending on if we are at the end of the file
*/
bool eof() {
    char c;
    std::cin >> c;
    // if the fie is ended, return true
    if (std::cin.eof()) {
        return true;
    } else {
        // if the file contains more data, return the previously gotten
        // data to cin
        std::cin.unget();
        return false;
    }
}

int main(int argc, char *argv[]) {
    // Repeatedly read input from standard input
    while (!eof()) {
        // create a new graph for each loop, which will read all of the
        // corresponding data per graph
        Province theProvince(std::cin);

        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "---------------- New DataSet: ------------------" << std::endl;
        std::cout << "------------------------------------------------" << std::endl;


        // call the breadth first search function on the new graph
        // to print out ('echo') all of the corresponding data
        // as specified in the project description
        theProvince.printAll(0, std::cout);

        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "------------------------------------------------" << std::endl;

        theProvince.printShortest(std::cout);

        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "------------------------------------------------" << std::endl;

        theProvince.minSpan(std::cout);

        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "------------------------------------------------" << std::endl;

        theProvince.removeBridges(std::cout);

        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
    }
}
