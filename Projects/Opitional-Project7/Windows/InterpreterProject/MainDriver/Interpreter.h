//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <cassert>
#include "Absyn.h"
#include "StringTab.h"
#include "SymbolTable.h"

class Environment;
typedef Environment*	EnvironmentP;

extern Symbol	arg,
arg2,
Bool,
concat,
cool_abort,
copy_,
Int,
in_int,
in_string,
IO,
isProto,
length,
Main,
main_meth,
No_class,
No_type,
Object,
out_int,
out_string,
prim_slot,
self,
SELF_TYPE,
Str,
str_field,
substr,
type_name,
val,
Void;


class ValueEntry {
protected:
	Symbol			type = nullptr;		//type of the value: VOID, Integer, Bool, String, class_name
	bool			boolv = false;		//Bool value
	int				intv = 0;			//Integer value
	string			strv = "";			//String value
	EnvironmentP	env = nullptr;		//Object value

public:
	ValueEntry(Symbol t) : type(t) { assert(t != No_type && t!= Void); }
	ValueEntry() : type(Void) { 
		int x =1; }

	ValueEntry(bool v) : type(Bool), boolv(v) { }
	ValueEntry(int v) : type(Int), intv(v) { }
	ValueEntry(string s) : type(Str), strv(s) { }
	ValueEntry(Symbol t, EnvironmentP e) : type(t), env(e) { }

	Symbol getType() { return type; }

	bool getBoolValue() { assert(type == Bool); return boolv; }
	int	 getIntValue() { assert(type == Int); return intv; }
	string getStrValue() { assert(type == Str); return strv; }
	EnvironmentP getObjectValue() { assert(type != Int && type != Str && type != Bool); return env; }

	void setBoolValue(bool v) { assert(type == Bool || type == Void); type = Bool; boolv = v; }
	void setIntValue(int v) { assert(type == Int || type == Void); type = Int;  intv = v; }
	void setStrValue(string v) { assert(type == Str || type == Void); type = Str; strv = v; }
	void setObjectValue(EnvironmentP e) { assert(type != Int && type != Str && type != Bool); env = e; }

	bool isVOID() { return type == Void; }
	bool isBOOL() { return type == Bool; }
	bool isINT() { return type == Int; }
	bool isSTRING() { return type == Str; }
	bool isOBJECT() { return type != Int && type != Str && type != Bool; }

	~ValueEntry() {}
};

typedef ValueEntry*	ValueP;

#endif
