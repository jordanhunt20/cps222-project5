/*
 * road.h - declarations for the class Road.	CPS222 project 5
 *
 * Copyright Jordan Hunt and Adam Vigneaux
 */

#include <string>

class Road
{
  public:

    // Constructor
    //
    // Parameter: name of file (which may be a relative or absolute
    // path).  If a file of this name exists, it is opened and the
    // tree stored in it is accessed; else a new file containing an
    // empty tree is created
    Road(std::string name);

    // Insert a road
    //
    // Parameters: key and associated value.  The key may not contain any
    // embedded spaces or control characters.
    void insert(std::string key, std::string value);

    // Lookup a key.  If found, set value to associated value and
    // return true, else leave value unchanged and return false
    bool lookup(std::string key, std::string & value) const;

    // Remove a key and its associated value.  Return true if
    // found and removed, false if not.
    bool remove(std::string key);

    // Print the contents of the entire tree to cout for testing/debugging
    // purposes.
    void print() const;

    // Destructor
    ~Road();

  private:
    std::string destination;
    char type;
};
