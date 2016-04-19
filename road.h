/*
 * road.h - declarations for the class Road.	CPS222 project 5
 *
 * Copyright Jordan Hunt and Adam Vigneaux
 */

class Road
{
  public:

    // Constructor
    //
    // Parameter: name of file (which may be a relative or absolute
    // path).  If a file of this name exists, it is opened and the
    // tree stored in it is accessed; else a new file containing an
    // empty tree is created
    Road(string name);

    // Insert a road
    //
    // Parameters: key and associated value.  The key may not contain any
    // embedded spaces or control characters.
    void insert(string key, string value);

    // Lookup a key.  If found, set value to associated value and
    // return true, else leave value unchanged and return false
    bool lookup(string key, string & value) const;

    // Remove a key and its associated value.  Return true if
    // found and removed, false if not.
    bool remove(string key);

    // Print the contents of the entire tree to cout for testing/debugging
    // purposes.
    void print() const;

    // Destructor
    ~Road();

  private:

    int _numRoads;
	int _numRoads;
	string [] Roads;
	string [] roads


};
