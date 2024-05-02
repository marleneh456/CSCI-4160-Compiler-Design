//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

//                                                                           ##
// This file defines extensions of the cool AST for                          ##
// type checking and interpreter project. 
// More specifically, it addes the following methods for interpreter:
// virtual InheritanceNodeP Program_class::semant();	use this function to start type checking and interpreter
// virtual void Feature_class::interp(EnvironmentP) = 0;
// void Method::interp(EnvironmentP);
// void Attr::interp(EnvironmentP);
// void Branch_class::interp(EnvironmentP);
// virtual void Expression_class::interp(EnvironmentP) = 0;
// void interp(EnvironmentP); for all Expression descendants

// Each interpreter method contains three versions. For example in LetExp class, 
// there are three interp methods:
// void interp_student(EnvironemntP);	//student's solution
// void interp_teacher(EnvironmentP);	//teacher's solution
// void interp(EnvironmentP);			//decide which version to use

#ifndef COOL_TREE_HANDCODE_H
#define COOL_TREE_HANDCODE_H

#include "StringTab.h"
#include "Interpreter.h"

class InheritanceNode;                               
typedef InheritanceNode *InheritanceNodeP;           
													 
class Environment;                                   
typedef Environment *EnvironmentP;
//##

#define Program_EXTRAS							\
virtual InheritanceNodeP semant();				

#define Feature_EXTRAS							\
virtual void tc(EnvironmentP) = 0;				\
virtual void add_to_table(EnvironmentP) = 0;	


#define Feature_SHARED_EXTRAS					\
void tc(EnvironmentP);							\
void add_to_table(EnvironmentP);                

#define Formal_EXTRAS                         \
virtual void tc(EnvironmentP env);  

#define Branch_EXTRAS                        \
virtual Symbol tc(EnvironmentP env);		\
virtual ValueP interp(EnvironmentP);			\
virtual ValueP interp_student(EnvironmentP);	\
virtual ValueP interp_teacher(EnvironmentP);


#define Expression_EXTRAS                    \
virtual Symbol tc(EnvironmentP) = 0;         \
Symbol type;                                 \
Symbol getType() { return type; }            \
Expression setType(Symbol s) { type = s; return this; } \
virtual ValueP interp(EnvironmentP) = 0;	\
virtual ValueP interp_student(EnvironmentP) = 0;	\
virtual ValueP interp_teacher(EnvironmentP) = 0;	



#define Expression_SHARED_EXTRAS            \
Symbol tc(EnvironmentP);                    \
ValueP interp(EnvironmentP);				\
ValueP interp_student(EnvironmentP);		\
ValueP interp_teacher(EnvironmentP);


#endif
