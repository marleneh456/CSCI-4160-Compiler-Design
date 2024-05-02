#include "Absyn.h"
#include "Semant.h"

using namespace absyn;

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

void Attr::tc_student(EnvironmentP env)
{
	//your implementation here
	
	//Attribute declaration format
	//name : type_decl <- init
	
	/*
		Algorithm:
			if type_decl doesn't exists as a class, report an error

			if init is provided
				Perform type checking on init and save its type info
				if the type of init is not compatible with type_decl, then report an error
	*/
}


Symbol IntExp::tc_student(EnvironmentP)
{
	type = Int;
	return Int;
}

Symbol BoolExp::tc_student(EnvironmentP)
{
	type = Bool;
	return Bool;
}

Symbol StringExp::tc_student(EnvironmentP)
{
	type = Str;
	return Str;
}

Symbol OpExp::tc_student(EnvironmentP env)
{
	//your implementation here
	
	//OpExp format:
	// left op right
	
	/*
		Algorithm:
			perform type checking on left and save its return value to ltype
			perform type checking on right and save its return value to rtype
			
			if op is not EQ
				if ltype or rtype is not Int, report an error
				
			else
				if t1 is not the same as t2 and t1 or t2 is Int, Bool, or Str
					report an error
			
			if op is LT, LE, or EQ
				set attribute type to Bool
			else
				set attribute type to Int

		
	*/

	return type;
}


Symbol NotExp::tc_student(EnvironmentP env)
{
	//your implementation here
	//NotExp format:
	//	NOT expr
	/*
		perform type checking on expr and save its return type to t
		
		if t is not the same as Bool	
			report an error
		
		set attribute type to Bool
	*/

	return type;
}

Symbol ObjectExp::tc_student(EnvironmentP env)
{
	//your implementation here
	
	//ObjectExp format:
	//	name
	
	/*
		if the variable name exists
			lookup the variable  in symbol table and save its type information to attribute type
		else
			report an error (undeclared identifier)
			set attribute type to Object
	*/

	return type;
}

Symbol NewExp::tc_student(EnvironmentP env)
{
	//your implementation here
	
	//NewExp format:
	//	new type_name
	
	/* Algorithm:
		lookup the class table to check if the type_name exists
		if exists
			set attribute type to type_name
		else
			report an error of undefined class
			set attribute type to Object
	*/
	
	return type;
}

Symbol IsvoidExp::tc_student(EnvironmentP env)
{
	//your implementation here
	//IsvoidExp format:
	//	isvoid(expr)
	
	/*
		Algorithm:
			perform type checing on expr;
			set attribute type to Bool
	*/

	return type;
}

Symbol LetExp::tc_student(EnvironmentP env)
{
	//your implementation here
	
	//LetExp format
	//let identifier : type_decl <- init in body
	
	/*
		Algorithm:
		lookup type_decl in class table to check if it exists.
		if it doesn't exist, report an error of undeclared class
		
		if init is provided
			perform type checking on init
			if the type of init is not compatible with type_decl
				report an error of type mismatch
		
		enter a new scope for variables
		
		if identifier is the same as self
			report an error
		else
			insert the variable and its type into variable symbol table
		
		perform type checking on body and save the return value to attribute type
		
		exit the current scope for variables
		
	*/
	return type;
}

Symbol BlockExp::tc_student(EnvironmentP env)
{
	//your implementation here
	
	/* Algorithm:
		for each expression in the list
			perform type checking on the expression and save its return value to attribute type
	*/
	return type;
}


Symbol AssignExp::tc_student(EnvironmentP env)
{
	//Solution given
	
	//AssignExp format:
	//	name <- expr

	//if name is self, report an error
	if (name == self)
		env->semant_error(this) << "Cannot assign to 'self'." << endl;

	//if name is not defined as a variable, report an error
	if (!env->var_lookup(name))
		env->semant_error(this) << "Assignment to undeclared variable " << name
		<< "." << endl;

	//perform type checking on expr and save its return value to attribute type
	type = expr->tc(env);

	//if type of the expression is not compatible with variable type, report an error 
	if (!env->type_leq(type, env->var_lookup(name)))
		env->semant_error(this) << "Type " << type <<
		" of assigned expression does not conform to declared type " <<
		env->var_lookup(name) << " of identifier " << name << "." << endl;

	//return the type of AssignExp
	return type;

}

Symbol CallExp::tc_student(EnvironmentP env)
{
	//No need to implement this method
	return No_type;
}

Symbol StaticCallExp::tc_student(EnvironmentP env)
{
	//No need to implement this method
	return No_type;
}


Symbol IfExp::tc_student(EnvironmentP env)
{
	//your implementation here

	//IfExp format:
	// if pred 
	//	then then_exp
	//	else else_exp

	/* Algorithm:
		perform type checking on pred, if return value is NOT Bool, report an error
		
		perform type checking on then_exp and save the return value, say then_type
		perform type checking on else_exp and save the return value, say else_type
		
		set attribute type to the lub of then_type and else_type
	*/

	return type;
}

Symbol WhileExp::tc_student(EnvironmentP env)
{
	//your implementation here

	//WhileExp format: 
	// while pred
	//		body
	
	/* Algorithm:
		perform type checking on pred, if return value is NOT Bool, report an error
		
		perform type checking on body
		
		set attribute type to Object
	*/

	return Object;
}

Symbol Branch_class::tc_student(EnvironmentP env)
{
	//No need to implement
	return expr->tc(env);
}

Symbol CaseExp::tc_student(EnvironmentP env)
{
	//No need to implement this
	return No_type;
}

void Method::tc_student(EnvironmentP env)
{
	//No need to implement this
}

void Formal_class::tc_student(EnvironmentP env)
{
	//No need to implement this
}

Symbol NoExp::tc_student(EnvironmentP)
{
	type = No_type;
	return No_type;
}