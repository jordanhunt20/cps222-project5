/*
 * road.h - declarations for the class Road.	CPS222 project 5
 *
 * Copyright Jordan Hunt and Adam Vigneaux
 */

#include <string>

class Road
{
  public:

    /**
     * Constructor
     * @param type Type of road, either bridge "B" or none "N"
     * @param length Length of the road in miles
     */
    Road(std::string originTown, std::string destinationTown,
                     char type, int length);

    /**
     * Destructor
     */
    ~Road();

  private:
    std::string _originTown;
    std::string _destinationTown;
    char _type;
    double _length;
};
