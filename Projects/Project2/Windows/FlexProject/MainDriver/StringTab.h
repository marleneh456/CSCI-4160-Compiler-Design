//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"


#ifndef _STRINGTAB_H_
#define _STRINGTAB_H_

#include <string>
#include <list>
#include <cassert>
#include <sstream>

using namespace std;

class Entry;
typedef Entry* Symbol;


/////////////////////////////////////////////////////////////////////////
//
//  String Table Entries
//
/////////////////////////////////////////////////////////////////////////

class Entry {
private:
	string	data;
	int		index;		// a unique index for each string in the table
public:
	Entry(string a1, int a2) : data(a1), index(a2)
	{}

	bool equal_string(string a1) const {
		return a1 == data;
	}

	string getData() const { return data; }
	int getIndex() const { return index; }
	virtual ~Entry() {};
};

//
// There are three kinds of string table entries:
//   a true string, an string representation of an identifier, and 
//   a string representation of an integer.
//
// Having separate tables is convenient for code generation.  Different
// data definitions are generated for string constants (StringEntry) and 
// integer  constants (IntEntry).  Identifiers (IdEntry) don't produce
// static data definitions.
//
//
class StringEntry : public Entry {
public:
	StringEntry(string a1, int index) : Entry(a1, index) 
	{}
	~StringEntry() {}
};

class IdEntry : public Entry {
public:
	IdEntry(string a1, int index) : Entry(a1, index)
	{}
	~IdEntry() {}
};

class IntEntry: public Entry {
public:
	IntEntry(string a1, int index) : Entry(a1, index)
	{}

	~IntEntry() {}
};

typedef StringEntry	*StringEntryP;
typedef IdEntry		*IdEntryP;
typedef IntEntry	*IntEntryP;

//////////////////////////////////////////////////////////////////////////
//
//  String Tables
//
//////////////////////////////////////////////////////////////////////////

template <class Elem> 
class StringTable
{
protected:
   list<Elem *> tbl;   // a string table is a list
public:
   StringTable() { }   // an empty table
   // The following methods each add a string to the string table.  
   // Only one copy of each string is maintained.  
   // Returns a pointer to the string table entry with the string.

   // add a string
   Elem *add_string(string s);

   // add the string representation of an integer
   Elem *add_int(int i);


   // An iterator.
   unsigned int first();       // first index
   bool more(unsigned int i);   // are there more indices?
   unsigned int next(unsigned int i);   // next index

   Elem *lookup(unsigned int index);      // lookup an element using its index
   Elem *lookup_string(string s); // lookup an element using its string
};

class IdTable : public StringTable<IdEntry> { };

class StrTable : public StringTable<StringEntry> { };

class IntTable : public StringTable<IntEntry> { };

extern IdTable	idTable;
extern IntTable intTable;
extern StrTable stringTable;
#endif
