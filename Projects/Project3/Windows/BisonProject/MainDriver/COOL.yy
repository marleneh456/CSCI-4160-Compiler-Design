%debug
%verbose
%locations

%code requires {
#include <iostream>
#include "ErrorMsg.h"
#include "StringTab.h"

int yylex(void); /* function prototype */
void yyerror(char *s);	//called by the parser whenever an eror occurs

}

%union {
	bool		boolean;	
	Symbol		symbol;	
}

%token <symbol>		STR_CONST TYPEID OBJECTID INT_CONST 
%token <boolean>	BOOL_CONST

%token CLASS ELSE FI IF IN 
%token INHERITS LET LOOP POOL THEN WHILE 
%token CASE ESAC OF DARROW NEW ISVOID 
%token ASSIGN NOT LE 

/* Precedence declarations. */
%left LET_STMT
%right ASSIGN
%left NOT
%left '-' '+'
%left '*' '/'

/*
* The above only gives precedence levels of some operators.
* Please provide precedence levels of other operators : LE '<' '=', ISVOID '~' '@' '.'
*/

%start program

%%

/*
 * The following is CFG of COOL programming languages. Several simple rules in the following comments are given for demonstration purpose.
 * You can uncomment them and provide extra rules for the CFG. Please be noted that you uncomment without providing extra rules, BISON will
 * will report errors when compiling COOL.yy file since several non-terminals are not defined.
 * 
 
 * No rule action needed in this assignment 
 * If a recusive rule is needed, for example, define a list of something, always use 
 * right recursion like:
 * class_list : class class_list
 *
 */

 //This rule is introduced to avoid compilation error.
 //When you start working on the project, please delete this rule.
 program : /* empty body */
		;

 /*
//A COOL program is viewed as a list of classes 
program	: class_list
        ;

class_list 	: class			
        | error ';'             // error in the first class
		| class class_list 		// several classes
		| class_list error ';'  // error message 
		;

// If no parent is specified, the class inherits from the Object class. 
class : CLASS TYPEID '{' optional_feature_list '}' ';'
		| CLASS TYPEID INHERITS TYPEID '{' optional_feature_list '}' ';'
		;

// Feature list may be empty, but no empty features in list. 

optional_feature_list:		//empty body for this rule
        | feature_list
        ;
*/



/* end of grammar */

%%
#include <FlexLexer.h>
extern yyFlexLexer	lexer;
int yylex(void)
{
	return lexer.yylex();
}

void yyerror(char *s)
{	
	extern ErrorMsg errormsg;
	errormsg.error(yylloc.first_line, yylloc.first_column, s);
}


