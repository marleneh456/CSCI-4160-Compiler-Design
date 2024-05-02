/*
PROGRAMMER: Marlene Habib
PROGRAM#: 6
DUE DATE: Monday, 4/15/2024
INSTRUCTOR: Dr. Dong
DESCRIPTION OF PROGRAM:
This program is for printing the errors by using abstract syntax to the COOL program.
*/

#include "Absyn.h"
#include "Semant.h"

using namespace absyn;

// Declaring the global symbols
Symbol	arg,
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
val;

// Function to initialize global constants
void initialize_constants(void)
{
	arg = idtable.add_string("arg");
	arg2 = idtable.add_string("arg2");
	Bool = idtable.add_string("Bool");
	concat = idtable.add_string("concat");
	cool_abort = idtable.add_string("abort");
	copy_ = idtable.add_string("copy");
	Int = idtable.add_string("Int");
	in_int = idtable.add_string("in_int");
	in_string = idtable.add_string("in_string");
	IO = idtable.add_string("IO");
	isProto = idtable.add_string("isProto");
	length = idtable.add_string("length");
	Main = idtable.add_string("Main");
	main_meth = idtable.add_string("main");
	//   _no_class is a symbol that can't be the name of any
	//   user-defined class.
	No_class = idtable.add_string("_no_class");
	No_type = idtable.add_string("_no_type");
	Object = idtable.add_string("Object");
	out_int = idtable.add_string("out_int");
	out_string = idtable.add_string("out_string");
	prim_slot = idtable.add_string("_prim_slot");
	self = idtable.add_string("self");
	SELF_TYPE = idtable.add_string("SELF_TYPE");
	Str = idtable.add_string("String");
	str_field = idtable.add_string("_str_field");
	substr = idtable.add_string("substr");
	type_name = idtable.add_string("type_name");
	val = idtable.add_string("_val");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Type Checking Features
//
//  For each class of expression, there is a tc method to typecheck it.
//  The tc methods make use of the environments previously constructred
//  for each class.  
//  Please implement the following type checking method.
//
//  YOU ARE NOT ALLOWED TO CALL tc_teacher VERSION
///////////////////////////////////////////////////////////////////////////////

// Type checking for Attribute expression
void Attr::tc_student(EnvironmentP env)
{
	// Check if the attribute exists
	if (!env->lookup_class(type_decl)) {
		env->semant_error(this) << "Class " << type_decl << " of attribute " << name << " is undefined." << endl;
		return;
	}

	// If an initialization expression exists, check on it
	if (init) {
		Symbol init_type = init->tc(env);

		// Check if the initialization expression type conforms to the declared type
		if (!env->type_leq(init_type, type_decl)) {
			env->semant_error(this) << "Type " << init_type << " of this " << type_decl << " of identifier " << name << "." << endl;
		}

		// Add the variable to the current environment
		env->var_add(name, init_type);
	}
	else {
		// If no initialization expression, simply add the variable with the a declared type
		env->var_add(name, type_decl);
	}
}

// Type checking for Integer
Symbol IntExp::tc_student(EnvironmentP)
{
	// Set the type of the expression to Int and return Int
	type = Int;
	return Int;
}

// Type checking for Boolean 
Symbol BoolExp::tc_student(EnvironmentP)
{
	// Set the type of the expression to Bool and return Bool
	type = Bool;
	return Bool;
}

// Type checking for String
Symbol StringExp::tc_student(EnvironmentP)
{
	// Set the type of the expression to String and return String
	type = Str;
	return Str;
}

// Type checking for Operation 
Symbol OpExp::tc_student(EnvironmentP env) {
	// Perform type checking on the left expression
	Symbol ltype = left->tc(env);

	// Perform type checking on the right expression
	Symbol rtype = right->tc(env);

	// Determine the operator symbol
	string opSymbol;
	switch (op) {
	case PLUS: opSymbol = "+"; break;
	case MINUS: opSymbol = "-"; break;
	case MUL: opSymbol = "*"; break;
	case DIV: opSymbol = "/"; break;
	case LT: opSymbol = "<"; break;
	case EQ: opSymbol = "="; break;
	case LE: opSymbol = "<="; break;
	}

	// Report an error if the types are not compatible for the operation
	env->semant_error(this) << "Non-integer arguments for operator: " << ltype << " " << opSymbol << " " << rtype << endl;

	// Return the result type
	return type;
}

// Type checking for Not 
Symbol NotExp::tc_student(EnvironmentP env)
{
	// Perform type checking on the expression
	Symbol t = expr->tc(env);

	// If the expression type is not Bool, report an error
	if (t != Bool) {
		env->semant_error(this) << "Argument of 'not' has type " << t << " instead of Bool." << endl;
	}

	// Set the type of the expression to Bool and return Bool
	type = Bool;
	return type;
}

// Type checking for Object 
Symbol ObjectExp::tc_student(EnvironmentP env)
{
	// Look up the type of the object in the current environment
	Symbol found_type = env->var_lookup(name);

	// If the object type is not found, report an error and set the type to Object
	if (!found_type) {
		env->semant_error(this) << "Undeclared identifier " << name << "." << endl;
		type = Object;
	}
	else {
		// Set the type of the expression to the found type
		type = found_type;
	}

	return type;
}

// Type checking for New 
Symbol NewExp::tc_student(EnvironmentP env)
{
	// Look up the class node for the given type name
	InheritanceNodeP class_node = env->lookup_class(type_name);

	// If the class node is not found, report an error and set the type to Object
	if (class_node == nullptr) {
		env->semant_error(this) << "Class " << type_name << " is undefined." << endl;
		type = Object;
	}
	else {
		// Set the type of the expression to the given type name
		type = type_name;
	}

	return type;
}

// Type checking for Isvoid 
Symbol IsvoidExp::tc_student(EnvironmentP env)
{
	// Perform type checking on the expression
	expr->tc(env);

	// Set the type of the expression to Bool
	type = Bool;

	return type;
}

// Type checking for Let
Symbol LetExp::tc_student(EnvironmentP env)
{
	// Check if the declared type exists in the current environment
	if (!env->lookup_class(type_decl)) {
		env->semant_error(this) << "Undeclared type " << type_decl << " in let expression." << endl;
		type_decl = Object;
	}

	// Enter a new scope for variables
	env->var_enterScope();

	Symbol init_type;
	if (init) {
		// Perform type checking on the initialization expression
		init_type = init->tc(env);

		// Check if the initialization expression type conforms to the declared type
		if (!env->type_leq(init_type, type_decl)) {
			env->semant_error(this) << "Type mismatch in let expression: cannot initialize "
				<< type_decl << " with " << init_type << "." << endl;
		}
	}

	if (identifier == env->get_self_type()) {
		env->semant_error(this) << "Cannot assign to 'self' in let." << endl;
	}
	else {
		// Add the variable to the current environment
		env->var_add(identifier, type_decl);
	}

	// Perform type checking on the body expression
	Symbol body_type = body->tc(env);
	type = body_type;

	// Exit the scope for variables
	env->var_exitScope();

	return type;
}

// Type checking for Block 
Symbol BlockExp::tc_student(EnvironmentP env)
{
	Symbol last_type = No_type;

	if (body == nullptr) {
		return last_type;
	}

	List<Expression>* expr_list = body;

	// Iterate through the expressions in the block
	while (expr_list != nullptr) {
		Expression expr = expr_list->getHead();
		if (expr != nullptr) {
			last_type = expr->tc(env);
		}
		expr_list = expr_list->getRest();
	}

	// Set the type of the block expression to the type of the last expression
	type = last_type;

	return type;
}

// Type checking for Assign
Symbol AssignExp::tc_student(EnvironmentP env)
{
	// AssignExp format: name <- expr

	// If the variable name is 'self', report an error
	if (name == self)
		env->semant_error(this) << "Cannot assign to 'self'." << endl;

	// If the variable name is not defined, report an error
	if (!env->var_lookup(name))
		env->semant_error(this) << "Assignment to undeclared variable " << name << "." << endl;

	// Perform type checking on the expression and save its return value to attribute type
	type = expr->tc(env);

	// If the type of the expression is not compatible with the variable type, report an error 
	if (!env->type_leq(type, env->var_lookup(name)))
		env->semant_error(this) << "Type " << type <<
		" of assigned expression does not conform to declared type " <<
		env->var_lookup(name) << " of identifier " << name << "." << endl;

	// Return the type of AssignExp
	return type;
}

// Type checking for Call
Symbol CallExp::tc_student(EnvironmentP env)
{
	// No need to implement this method
	return No_type;
}

// Type checking for StaticCall
Symbol StaticCallExp::tc_student(EnvironmentP env)
{
	// No need to implement this method
	return No_type;
}

// Type checking for If 
Symbol IfExp::tc_student(EnvironmentP env)
{
	// Perform type checking on the predicate expression
	Symbol pred_type = pred->tc(env);

	// If the predicate type is not Bool, report an error
	if (pred_type != Bool) {
		env->semant_error(this) << "Predicate of 'if' expression must be Boolean, but found type " << pred_type << "." << endl;
	}

	// Perform type checking on the 'then' and 'else' expressions
	Symbol then_type = then_exp->tc(env);
	Symbol else_type = else_exp->tc(env);

	// Set the type of the expression to the least upper bound of 'then' and 'else' types
	type = env->type_lub(then_type, else_type);

	return type;
}

// Type checking for While 
Symbol WhileExp::tc_student(EnvironmentP env)
{
	// Perform type checking on the predicate expression
	Symbol pred_type = pred->tc(env);

	// If the predicate type is not Bool, report an error
	if (pred_type != Bool) {
		env->semant_error(this) << "Predicate of 'while' expression must be Boolean, but found type " << pred_type << "." << endl;
	}

	// Perform type checking on the body expression
	body->tc(env);

	return Object;
}

// Type checking for Branch class
Symbol Branch_class::tc_student(EnvironmentP env)
{
	// No need to implement
	return expr->tc(env);
}

// Type checking for Case 
Symbol CaseExp::tc_student(EnvironmentP env)
{
	// No need to implement this
	return No_type;
}

// Type checking for Method
void Method::tc_student(EnvironmentP env)
{
	// No need to implement this
}

// Type checking for Formal class
void Formal_class::tc_student(EnvironmentP env)
{
	// No need to implement this
}

// Type checking for No expression
Symbol NoExp::tc_student(EnvironmentP)
{
	// Set the type of the expression to No_type and return No_type
	type = No_type;
	return No_type;
}
