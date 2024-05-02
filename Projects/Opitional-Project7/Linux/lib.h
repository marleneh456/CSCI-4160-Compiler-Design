#ifndef _LIB_H_
#define _LIB_H_

#include <string>
#include <iostream>
#include "Semant.h"

using namespace std;


void object_abort(ValueP vp);
Symbol object_type_name(ValueP vp);
ValueP object_copy(ValueP vp);

ValueP io_out_string(ValueP vp, string x);
ValueP io_out_int(ValueP vp, int x);
string io_in_string(ValueP vp);
int io_in_int(ValueP vp);

int string_length(ValueP vp);
string string_concat(ValueP vp, string s);
string string_substr(ValueP vp, int i, int l);


bool isBasicClassMethod(EnvironmentP env, Symbol classname, Symbol method_name);

ValueP handleBasicClassMethod(ValueP vp, Symbol method_name);

ValueP handleBasicClassMethod(ValueP vp, Symbol method_name, int arg);

ValueP handleBasicClassMethod(ValueP vp, Symbol method_name, string arg);

ValueP handleBasicClassMethod(ValueP vp, Symbol method_name, int arg1, int arg2);

#endif