//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

#include <cassert>
#include <sstream>
#include "StringTab.h"

//
// Explicit template instantiations.
// Comment out for versions of g++ prior to 2.7
//
template class StringTable<IdEntry>;
template class StringTable<StringEntry>;
template class StringTable<IntEntry>;

// A Symbol is a pointer to an Entry.  Symbols are stored directly
// as nodes of the abstract syntax tree defined by the cool-tree.aps.
// The APS package requires that copy and print (called dump) functions
// be defined for components of the abstract syntax tree.
//
IdTable idTable;
IntTable intTable;
StrTable stringTable;

//
// A string table is implemented a linked list of Entrys.  Each Entry
// in the list has a unique string.
//
// Add a string requires two steps.  First, the list is searched; if the
// string is found, a pointer to the existing Entry for that string is 
// returned.  If the string is not found, a new Entry is created and added
// to the list.
//
template <class Elem>
Elem *StringTable<Elem>::add_string(string s)
{
	for (Elem * e : tbl)
		if (e->equal_string(s))
			return e;

	Elem *e = new Elem(s, tbl.size());
	tbl.push_back(e);
	return e;
}

//
// To look up a string, the list is scanned until a matching Entry is located.
// If no such entry is found, an assertion failure occurs.  Thus, this function
// is used only for strings that one expects to find in the table.
//
template <class Elem>
Elem *StringTable<Elem>::lookup_string(string s)
{
	for (Elem * e : tbl)
		if (e->equal_string(s))
			return e;

	assert(0);		// fail if string is not found
	return nullptr; // to avoid compiler warning
}


//
// lookup is similar to lookup_string, but uses the index of the string
// as the key.
//
template <class Elem>
Elem *StringTable<Elem>::lookup(unsigned int ind)
{
	for (Elem * e : tbl)
		if (e->getIndex() == ind)
			return e;

	assert(0);   // fail if string is not found
	return nullptr; // to avoid compiler warning
}

//
// add_int adds the string representation of an integer to the list.
//
template <class Elem>
Elem *StringTable<Elem>::add_int(int i)
{
	stringstream ss;
	ss << i;
	return add_string(ss.str());
}

template <class Elem>
unsigned int StringTable<Elem>::first()
{
	return 0;
}

template <class Elem>
bool StringTable<Elem>::more(unsigned int i)
{
	return i < tbl.size();
}

template <class Elem>
unsigned int StringTable<Elem>::next(unsigned int i)
{
	assert(i < tbl.size());
	return i + 1;
}
