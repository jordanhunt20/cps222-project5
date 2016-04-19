/*
 * province.h - declarations for the class Province.	CPS222 project 5
 *
 * Copyright Jordan Hunt and Adam Vigneaux
*/

class Province
{
  public:

    // Constructor
    //
    // Parameter: name of province
    Province(int numTowns, int numRoads);

    // Insert a road
    //
    // Parameters: road to add
    void addTown(Town town);

    ~Province();

  private:

    int _numTowns;
    int _numRoads;
    Town towns[];
};
