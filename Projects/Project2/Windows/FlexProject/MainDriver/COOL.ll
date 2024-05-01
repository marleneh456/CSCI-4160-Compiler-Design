%option noyywrap
%option c++
%option never-interactive
%option nounistd
%option yylineno

%{
#include <iostream>
#include <string>
#include <sstream>
#include "tokens.h"
#include "ErrorMsg.h"

using std::string;
using std::stringstream;

ErrorMsg	errormsg;		//objects to trace lines and chars per line so that
							//error message can refer the correct location 
int		comment_depth = 0;	// depth of the nested comment
string	buffer = "";		// the buffer to hold part of string that has been recognized

void newline(void);				//trace the line #
void error(int, int, string);	//output the error message referring to the current token

int			line_no = 1;		//line no of current matched token
int			column_no = 1;		//column no of the current matched token

int			tokenCol = 1;		//column no after the current matched token

int			beginLine=-1;		//beginning position of a string or comment
int			beginCol=-1;		//beginning position of a string or comment

//YY_USER_ACTION will be executed after each Rule is used. Good to track locations.
#define YY_USER_ACTION {column_no = tokenCol; tokenCol=column_no+yyleng;}
%}


/* defined regular expressions */
NEWLINE			[\n]
WHITESPACES		[ \t\f\v\r]
TYPESYMBOL		[A-Z][_A-Za-z0-9]*
OBJECTSYMBOL	[a-z][_A-Za-z0-9]*

/*exclusive start conditions to recognize comment and string */
%x COMMENT
%x LINE_COMMENT
%x STRING


%%
{NEWLINE}			{ newline(); }
{WHITESPACES}+		{}


 /*
  *  If it is a token with a single character, just return the character itself.
  */
"+"	        { return '+'; }

 /*
  * Add here other rules for tokens with a single character
  *
  */

 /*
  *  The multiple-character operators.
  */
"=>"				{ return (DARROW); }
"<="				{ return (LE); }
"<-"				{ return (ASSIGN); }

 /*
  *  integers should be added to the "intTable" (check stringtab.h file) 
  *  so that there is only one copy of the same interger literal.
  *  Similarly, string literals should be added to "stringTable", and 
  *  typeid and objectid should be added to "idTable".
  *	 
  *	 yylval is a variable of YYSTYPE structure is used to hold values 
  *	 of tokens if a token is a collection of lexemes.
  *
  *  check YYSTYPE definition in tokens.h
  */

[0-9][0-9]*			{ yylval.symbol = intTable.add_string(YYText()); return INTCONST; }

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */
[Cc][Aa][Ss][Ee]			{ return (CASE); }
[Cc][Ll][Aa][Ss][Ss] 		{ return (CLASS); }

 /*
  * Add all missing rules here
  *
  */



%%

void newline()
{
	line_no ++;
	column_no = 1;
	tokenCol = 1;
}

void error(int line, int col, string msg)
{
	errormsg.error(line, col, msg);
}
