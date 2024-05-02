/* 
PROGRAMMER: Marlene Habib 
PROGRAM#: 3
DUE DATE: Monday, 3/11/2024
INSTRUCTOR: Dr. Dong
DESCRIPTION OF PROGRAM: 
This program is for creating context-free grammar in bison to COOL file and print the errors
*/

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

/* Define union */
%union {
	bool		boolean;	
	Symbol		symbol;	
}

/* Define tokens */
%token <symbol>		STR_CONST TYPEID OBJECTID INT_CONST 
%token <boolean>	BOOL_CONST

%token CLASS ELSE FI IF IN 
%token INHERITS LET LOOP POOL THEN WHILE 
%token CASE ESAC OF DARROW NEW ISVOID 
%token ASSIGN NOT LE 

/* Precedence declarations. */
%left LET_STMT /* Set LET_STMT on left */
%right ASSIGN /* Set ASSIGN on right */
%left NOT    /* Set NOT on left */
%left '-' '+'  /* Set minus and plus on left */
%left '*' '/'  /* Set times and divide on left */

/* The rest of the operators */
%nonassoc LE '<' '=' /* No associativity on LE, <, and = */
%left ISVOID   /* Set ISVOID on left */      
%left '~'      /* Set ~ on left */       
%left '@'      /* Set @ on left */       
%left '.'     /* Set . on left */        

/*
* The above only gives precedence levels of some operators.
* Please provide precedence levels of other operators : LE '<' '=', ISVOID '~' '@' '.'
*/



%start program

%%

/* start the grammar rules */

/* Rule for program */
program : class_list
        | error
        ;

/* Rules for class list */
class_list: class
		  | error ';'
	      | class class_list
	      | class_list error ';'
	      ;

/* Rule for class */
class: CLASS TYPEID '{' optional_feature_list '}' ';'
     | CLASS TYPEID INHERITS TYPEID '{' optional_feature_list '}' ';'
     ;

/* Rule for opitional feature list */
optional_feature_list: /* empty */
                     | feature_list
                     ;

/* Rules for feature list */
feature_list: feature ';'
            | error ';'
            | feature ';' feature_list
            | error ';' feature_list
            ;

/* Rule for feature */
feature: OBJECTID formals ':' TYPEID '{' expr '}'
       | OBJECTID ':' TYPEID optional_initialization
       ;

/* Rule for optional initialization */
optional_initialization: /* empty */
                       | ASSIGN expr
                       ;

/* Rules for formals and formals list */
formals: '(' ')'
       | '(' formal_list ')'
       ;

formal_list: formal
           | formal ',' formal_list
           ;

formal: OBJECTID ':' TYPEID
      ;

/* Rule for the let list */   
let_list: OBJECTID ':' TYPEID optional_initialization IN expr
        | OBJECTID ':' TYPEID optional_initialization ',' let_list
        ;

/* Rules for the expression */
expr: OBJECTID ASSIGN expr
    | expr '@' TYPEID '.' OBJECTID actuals
    | expr '.' OBJECTID actuals
    | IF expr THEN expr ELSE expr FI
    | WHILE expr LOOP expr POOL
    | '{' stmt_list '}'
    | LET let_list
    | CASE expr OF case_list ESAC
    | NEW TYPEID
    | ISVOID expr
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '~' expr
    | expr '<' expr
    | expr '=' expr
    | expr LE expr
    | NOT expr
    | '(' expr ')'
    | INT_CONST
    | STR_CONST
    | BOOL_CONST
    | OBJECTID
    | OBJECTID actuals
    ;

/* Rules for the statement list */
stmt_list: expr ';'
         | error ';'
         | expr ';' stmt_list
         | error ';' stmt_list
         ;

/* Rules for actuals */
actuals: '(' ')'
       | '(' exp_list ')'
       | '(' error ')'
       ;

/* Rule for the expression list */
exp_list: expr
        | expr ',' exp_list
        ;

/* Rule for the case list */
case_list: simple_case
         | simple_case case_list
         ;

/* Rule for the simple case */  
simple_case: OBJECTID ':' TYPEID DARROW expr ';'
           ;

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


