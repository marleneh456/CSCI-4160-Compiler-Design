#include <sstream>
#include <list>
#include <algorithm>
#include <map>

#include "Absyn.h"
#include "Semant.h"
#include "lib.h"

using namespace std;
using namespace absyn;


///////////////////////////////////////////////////////////////////////////////
//
//  Interpreter Features
//
//  For each class of expression, there is an interpreter method to evaluate it.
//  The interpreter methods make use of the environments previously constructred
//  for each class.  This code parallels the structure of the type
//  inference rules in the CoolAid very closely.
//
///////////////////////////////////////////////////////////////////////////////

ValueP IntExp::interp_student(EnvironmentP env)
{
	return new ValueEntry(stoi(getValue()->getContent()));
}

ValueP BoolExp::interp_student(EnvironmentP env)
{
	return new ValueEntry(getValue());
}

ValueP StringExp::interp_student(EnvironmentP)
{
	return new ValueEntry(getValue()->getContent());
}

ValueP OpExp::interp_student(EnvironmentP env)
{
	//put your implementation here
	// Algorithm:
	//	interpret left operand and save its value to a local variable t1
	//	interpret right operand and save its value to a local variable t2
	//	
	// 	if operator is PLUS/MINUS/MUL/DIV/LT/LE, return the result of t1 and t2 based on the type of operator
	// 
	// 	if operator is EQ
	// 		if t1 is an integer, compare t1 and t2 as integers and return result
	//		else if t1 is a string, compare t1 and t2 as strings and return result
	// 	    else if t1 is an object, compare t1 and t2 as objects and return result
	// 
	//The return statement below is to avoid compile errors by returning VOID.
	//Your implementation should return the result of the expression being evaluated.
	return new ValueEntry();
}

ValueP NotExp::interp_student(EnvironmentP env)
{
	//put your implementation here
	//
	//Algorithm:
	// 	   interpret expr and save its return value to a local variable v
	// 	   return a value based on the result of v.
	// 
	//The return statement below is to avoid compile errors by returning VOID.
	//Your implementation should return the result of the expression being evaluated.
	return new ValueEntry();
}

ValueP ObjectExp::interp_student(EnvironmentP env)
{
	//put your implementation here
	//Algorithm:
	// 	if name is equal to self
	// 	   return ValueEntry based on the self type and env.
	// 	else
	// 	   return the value of the variable "name". (Where to get the value of a variable??)
	// 
	//The return statement below is to avoid compile errors by returning VOID.
	//Your implementation should return the result of the expression being evaluated.
	return new ValueEntry();
}

ValueP NewExp::interp_student(EnvironmentP env)
{
	//put your implementation here
	//Algorithm:
	// 	   retrieve the class information from the "type_name" and save it to a local variable.
	// 	   return a pointer to ValueEntry based on the type_name and its envrionment
	// 
	//The return statement below is to avoid compile errors by returning VOID.
	//Your implementation should return the result of the expression being evaluated.
	return new ValueEntry();
}

ValueP IsvoidExp::interp_student(EnvironmentP env)
{
	//put your implementation here
	// Algorithm:
	// 	   interpret "expr" and save its return value to a local variable v;
	// 	   return value based on the type of value in v (void or not)
	// 
	//The return statement below is to avoid compile errors by returning VOID.
	//Your implementation should return the result of the expression being evaluated.
	return new ValueEntry();
}

ValueP LetExp::interp_student(EnvironmentP env)
{
	//put your implementation here
	//Algorithm:
	// 	   enter scope for variable symbol table
	// 	   add the variable "identifier" to the variable symbol table
	// 
	// 	   if init is provided
	//			interpret the init and save its return value to a local variable v
	//			use v to update the value of variable "identifier"
	//		interpret the body and save its return value to v
	// 	   exit scope for variable symbol table
	//		return v;
	//  
	//The return statement below is to avoid compile errors by returning VOID.
	//Your implementation should return the result of the expression being evaluated.
	return new ValueEntry();
}

ValueP BlockExp::interp_student(EnvironmentP env)
{
	//put your implementation here
	//Algorithm:
	//	for each expressionin the "body"
	// 	   interpret the expression and save its value to a local variable v
	// 
	// 	   return v;
	// 
	//The return statement below is to avoid compile errors by returning VOID.
	//Your implementation should return the result of the expression being evaluated.
	return new ValueEntry();
}

ValueP AssignExp::interp_student(EnvironmentP env)
{
	//put your implementation here
	//Algorithm:
	//	interpret the "expr" and save its return value to a local variable v;
	//  use v to update the value of variable "name" in the variable symbol table
	//  return the value of variable "name"
	// 
	//The return statement below is to avoid compile errors by returning VOID.
	//Your implementation should return the result of the expression being evaluated.
	return new ValueEntry();
}

ValueP IfExp::interp_student(EnvironmentP env)
{
	//put your implementation here
	//Algorithm:
	// 	   interpret the "pred" and save its return value to a local variable "cond"
	// 	   if cond represents true
	//			interpret "then_exp" and return its result
	// 	   else
	// 			interpret "else_exp" and return its result
	//The return statement below is to avoid compile errors by returning VOID.
	//Your implementation should return the result of the expression being evaluated.
	return new ValueEntry();
}

ValueP WhileExp::interp_student(EnvironmentP env)
{
	//put your implementation here
	//Algorithm:
	// 	   interpret the "pred" and save its  return value to a local variable "cond"
	// 	   while "cond" represents true
	//			interpret the expression "body"
	//			re-interpret the "pred" and save its  return value to a local variable "cond"
	// 
	//The return statement below is to avoid compile errors by returning VOID.
	//Your implementation should return the result of the expression being evaluated.
	return new ValueEntry();
}

ValueP CallExp::interp_student(EnvironmentP env)
{
	//No need to implement this one.
	//Teacher's solution will be used.
	return new ValueEntry();
}

ValueP StaticCallExp::interp_student(EnvironmentP env)
{
	//No need to implement this one.
	//Teacher's solution will be used.
	return new ValueEntry();
}

ValueP Branch_class::interp_student(EnvironmentP env)
{
	//No need to implement this one.
	//Teacher's solution will be used.
	return new ValueEntry();
}

ValueP CaseExp::interp_student(EnvironmentP env)
{
	//No need to implement this one.
	//Teacher's solution will be used.
	return new ValueEntry();
}

ValueP NoExp::interp_student(EnvironmentP)
{
	//No need to implement this one.
	//Teacher's solution will be used.
	return new ValueEntry();
}

