//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

#ifndef SEMANT_H_
#define SEMANT_H_

#include <cassert>
#include "Absyn.h"
#include "StringTab.h"
#include "SymbolTable.h"

#include "Interpreter.h"

// These are globally defined to prevent compiler warnings about
// anonymous enumerated types.
enum Inheritable { CanInherit, CantInherit };
enum Basicness { Basic, NotBasic };
enum Reachability { Reachable, UnReachable };

//
// The major types in this file (Environment, ClassTable, InheritanceNode)
// cross-reference each other, so all must be declared first to
// allow forward references.
//
class Environment;
typedef Environment *EnvironmentP;
class ClassTable;
typedef ClassTable *ClassTableP;
class InheritanceNode;
typedef InheritanceNode *InheritanceNodeP;


///////////////////////////////////////////////////////////////////////
//
//  Enviroment functions.
//
//  The Cool type checking rules require four structures to typecheck a 
//  class X.  These four items are encapsulated in an Environment:
//
//     a) a mapping from method names to method definitions for X
//     b) a mapping from variable (local and attribute) names to
//         definitions in X
//     c) a mapping from method names and class names to defintions
//         for methods of classes other than X
//     d) the self class (X)
//
//     c) is realized using a class_table, which contains a mapping
//        from class names to InheritanceNodes (and thereby to Environments)
//        for all classes.
//
//////////////////////////////////////////////////////////////////////

//
// The environment of a COOL  expression can be completely characterized
// by 
//    1. A symbol table describing method bindings.
//    2. A symbol table describing attribute/local variable bindings.
//    3. A symbol table of all classes.
//    4. The class in which the expression occurs (the class of SELF_TYPE)
//
class Environment
{
private:
	SymbolTable<Symbol, absyn::Method>	method_table;
	SymbolTable<Symbol, ValueEntry>		var_table;		//modified for interpreter: change Entry to ValueEntry
	ClassTableP							class_table;
	absyn::Class_						self_class;
public:
	// push a new scope for each of the method/variable tables,
	// so that new methods/variables will not conflict with existing ones.
	Environment(ClassTableP ct, InheritanceNodeP sc);
	Environment(SymbolTable<Symbol, absyn::Method> mt,
				SymbolTable<Symbol, ValueEntry>  vt,	//implementation modified for interpreter
				ClassTableP ct,
				InheritanceNodeP sc);

	// Most "new" environments are duplicates of a parent class environment
	// with the self class replaced.  An small but important point is that
	// the method table and var table structures are copied, so that 
	// additions to the new environment have no effect on the original.
	EnvironmentP clone_Environment(InheritanceNodeP n);

	// class table operations
	//
	// Standard ways to report errors.
	//
	ostream& semant_error();
	ostream& semant_error(absyn::TreeNode *t);

	InheritanceNodeP lookup_class(Symbol s);

	// method table operations 
	void method_add(Symbol s, absyn::Method *m);
	absyn::Method *method_lookup(Symbol s);
	absyn::Method *method_probe(Symbol s);
	void method_enterScope();
	void method_exitScope();

	// attribute table operations
	void var_add(Symbol s, Symbol typ);		//implementation modified for interpreter
	Symbol var_lookup(Symbol s);
	Symbol var_probe(Symbol s);
	void var_enterScope();
	void var_exitScope();

	// type operations
	Symbol get_self_type();

	// type_leq   Is type X <= type Y?
	// type_lub   What is the most specific type greater than both X and Y?
	//
	// These functions are complicated slightly by the handling of SELF_TYPE
	// and by taking care to avoid generating multiple error messages for
	// undefined classes (which have already been reported by the time
	// these functions are used).
	bool type_leq(Symbol subtype, Symbol supertype);

	// Find the least common ancestor in the inheritance graph.
	Symbol type_lub(Symbol t1, Symbol t2);

	/****************Added for Interpreter*************************/
public:
	//look up the value of a given variable s
	ValueP var_value_lookup(Symbol s);

	//check the value of a given variable s in latest scope
	ValueP var_value_probe(Symbol s);

	//Modify the value for the given variable s
	void var_value_change(Symbol s, ValueP v);

	//Duplicate the environment 
	//deep copy of var_table, but shallow copy for all other member data
	EnvironmentP instantiation();
	/*****************************************/

};


// A node of the inheritance graph is a Cool class with associated info:
//     1. parent in the inheritance graph
//     2. children " "       "        "
//     3. can inherit/can't inherit from this class
//     4. basic/not basic class
//     5. this class is reachable/unreachable from the Object class
//           via the "inherits from" relation
//     6. a type checking environment
//
class InheritanceNode : public absyn::Class_class 
{
private:
	InheritanceNodeP		parentnd;
	list<InheritanceNodeP>	children;
	Inheritable				inherit_status;
	Basicness				basic_status;
	Reachability			reach_status;
	EnvironmentP			env;

public:
	InheritanceNode(absyn::Class_ c, Inheritable istatus, Basicness bstatus);
	int basic() { return (basic_status == Basic); }
	int inherit() { return (inherit_status == CanInherit); }

	// InheritanceNode::mark_reachable()
	// Recursively mark all nodes reachable from the argument as Reachable.
	// Initally called with Object.
	void mark_reachable();
	bool reachable() { return (reach_status == Reachable); }
	void add_child(InheritanceNodeP child);
	list<InheritanceNodeP> get_children() { return children; }
	void set_parentnd(InheritanceNodeP p);
	InheritanceNodeP get_parentnd();
	//
	// The type checking environment of class X is established by copying 
	// the environment of X's parent and setting setting the self class to be 
	// X.
	//
	void copy_env(EnvironmentP e) { env = e->clone_Environment(this); }
	
	
	// The following group of functions recursively walk each feature
	// of each class, adding information to the environment for the classes
	// about the features.  Errors such as redefining method/attribute names
	// within a class are caught here.
	void build_feature_tables();
	void type_check_features();
	//
	// For the root Object class, a fresh environment structure is created.
	//
	// Allocate new Environment structure.  Presently used only for the
	// root (Object) class; all other classes make a copy of their parent's
	// Environment.
	void init_env(ClassTableP ct);
	void check_main_method();
	absyn::Method *method_lookup(Symbol s) { return env->method_lookup(s); }


	/****************Added for Interpreter*************************/
	
	EnvironmentP instantiation();	//Create a environment for an object from environment of the class
	
	EnvironmentP getEnvironment() { return env; }
	/*************************************************************/
};

////////////////////////////////////////////////////////////////////
//
// ClassTable::ClassTable
//
// The ClassTable constructor initializes a symbol table mapping
// class names to inheritance graph nodes.  The constructor also
// installs the basic classes.
//
// Cool has five basic classes: 
//   Object:     The root of the hierarchy; all objects are Objects.
//   IO:         A class for simple string and integer input/output.
//   Int:        Integers
//   Bool:       Booleans
//   String:     Strings
//
//   User-defined classes may inherit from Object and IO, but the
//   Int, Bool, and String classes cannot be inherited.
//
/////////////////////////////////////////////////////////////////////
class ClassTable : public SymbolTable<Symbol, InheritanceNode>
{
	//
	// Much of the type checker is built into the construction
	// of the class table.
	//
private:
	list<InheritanceNodeP> nds;
	int	semant_errors;             // counts the number of semantic errors

	// insert builtin classes into the list
	void install_basic_classes();

	// install_classes enters a list of classes in the symbol table.
	// The following possible errors are checked:
	//       - a class called SELF_TYPE
	//       - redefinition of a basic class
	//       - redefinition of another previously defined class
	void install_class(InheritanceNodeP nd);
	void install_classes(absyn::Classes cs);

	// This function checks whether the classes in a ClassTable illegally inherit
	// from
	//  - a CantInherit class
	//  - SELF_TYPE
	//  - an undefined class
	void check_improper_inheritance();

	// For each class node in the inheritance graph, set its parent,
	// and add the node to the parent's list of child nodes.
	void build_inheritance_tree();
	void set_relations(InheritanceNodeP nd);

	// This method should be run only after mark_reachable has executed.
	// If there are any unreachable classes in the inheritance graph and
	// all of the local checks of check_improper_inheritance succeeded,
	// then there is a cycle in the inheritance graph.
	void check_for_cycles();
	void build_feature_tables();

	// Checks for the existence of the Main class, and that it has access to a
	// method main in its inheritance hierarchy by calling InheritanceNode::check_main_method().
	void check_main();
	ostream& error_stream;
public:
	ClassTable(absyn::Classes);
	int errors() { return semant_errors; }
	InheritanceNodeP root();
	ostream& semant_error();
	ostream& semant_error(absyn::Class_ c);
	ostream& semant_error(Symbol filename, absyn::TreeNode *t);

	ValueP interp();	//added for interpreter
						//For each class, using provided initial value to initialize attribute in Environment
						//Find Main class, then find main method and interp main method.
};


#endif
