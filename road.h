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
    Road(char type, int length);

    /**
     * Destructor
     */
    ~Road();

  private:

    char _type;
    int _length;
};
