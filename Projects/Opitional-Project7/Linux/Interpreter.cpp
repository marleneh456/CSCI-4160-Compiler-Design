#include <sstream>
#include <list>
#include <algorithm>
#include <map>

#include "Absyn.h"
#include "Semant.h"
#include "lib.h"

using namespace std;
using namespace absyn;

#define student_version interp_student(env)
#define teacher_version interp_teacher(env)

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

ValueP IntExp::interp(EnvironmentP env)
{
	return teacher_version;
}

ValueP BoolExp::interp(EnvironmentP env)
{
	return teacher_version;
}

ValueP StringExp::interp(EnvironmentP env)
{
	return teacher_version;
}

ValueP OpExp::interp(EnvironmentP env)
{
	return student_version;
}

ValueP NotExp::interp(EnvironmentP env)
{
	return student_version;
}

ValueP ObjectExp::interp(EnvironmentP env)
{
	return student_version;
}

ValueP NewExp::interp(EnvironmentP env)
{
	return student_version;
}

ValueP IsvoidExp::interp(EnvironmentP env)
{
	return student_version;
}

ValueP LetExp::interp(EnvironmentP env)
{
	return student_version;
}

ValueP BlockExp::interp(EnvironmentP env)
{
	return student_version;
}

ValueP AssignExp::interp(EnvironmentP env)
{
	return student_version;
}

ValueP IfExp::interp(EnvironmentP env)
{
	return student_version;
}

ValueP WhileExp::interp(EnvironmentP env)
{
	return student_version;
}

ValueP CallExp::interp(EnvironmentP env)
{
	return teacher_version;
}

ValueP StaticCallExp::interp(EnvironmentP env)
{
	return teacher_version;
}

ValueP Branch_class::interp(EnvironmentP env)
{
	return teacher_version;
}

ValueP CaseExp::interp(EnvironmentP env)
{
	return teacher_version;
}

ValueP NoExp::interp(EnvironmentP env)
{
	return teacher_version;
}