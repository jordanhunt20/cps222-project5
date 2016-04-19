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
    Province(string name);

    // Insert a road
    //
    // Parameters: road to add
    bool addTown(Town town)

  private:

    int _numTowns;
	Towns [] towns;


};
