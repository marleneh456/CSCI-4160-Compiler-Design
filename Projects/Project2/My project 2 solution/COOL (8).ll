/*
PROGRAMMER: Marlene Habib
PROGRAM#:2
DUE DATE: Friday, 2/16/2024
INSTRUCTOR: Dr. Dong
DESCRIPTION OF PROGRAM: 
  This program is for creating a scanner for the COOL programming.
*/


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

/*exclusive start conditions to recognize comment, string and line_comment */
%x COMMENT
%x LINE_COMMENT
%x STRING

%%

/* Start string literal when a double quote is encountered */
\" {
    buffer = ""; /* Initialize buffer to collect string contents */
    beginLine = line_no; /* Record line where string starts */
    beginCol = column_no; /* Record column where string starts */
    BEGIN(STRING); /* Enter STRING state */
}

/* Encountered the STRING state */
<STRING>\" {
    yylval.symbol = stringTable.add_string(buffer); /* Add collected string to symbol table */
    BEGIN(INITIAL); /* Return to INITIAL state */
    return STRCONST; /* Return string constant token */
}

/* Handle the escape sequences */
<STRING>\\n { buffer += "\n"; line_no++; column_no = 0; } /* New line */
<STRING>\\t { buffer += "\t"; } /* New Tab */
<STRING>\\\" { buffer += "\""; } /* Double quote */
<STRING>\\\\ { buffer += "\\"; } /* Backslash */
<STRING>\\[^tn"\\] {
    /* Handle the errors */
    error(line_no, column_no, string(YYText()) + " illegal escape sequence");
}
/* Handles the unterminated string */
<STRING>\n {
    /* Handle the newline without the closing quote */
    error(beginLine, beginCol, "Unterminated string constant");
    newline();
    yylval.symbol = stringTable.add_string(buffer); /* Add buffer to the symbol table */
    BEGIN(INITIAL); /* Call Begin for Initial */
    return STRCONST; /* Return string constant */
}
/* Appends other character to the buffer in a string */
<STRING>. { buffer += YYText(); } /* Collect the rest of the characters */

/* Start block if there are "(*" */
"(*" {
    comment_depth = 1; 
    beginLine = line_no; 
    beginCol = column_no; 
    BEGIN(COMMENT); /* Call Begin for Initial */
}

<COMMENT>"(*"	{	/* nested comment */
					comment_depth ++;
				}

<COMMENT>[^*)(\n]*	{	/*eat string that's not a '*', '(', ')' */ }

<COMMENT>"("+[^*)\n]*  {	/*eat string that starts with ( but not followed by '*' and ')' */ }

<COMMENT>[^*(\n]*")"+  {	/*eat string that doesn't contain '*' and '(' but ends with a sequence of ')' */ }

<COMMENT>"*"+[^*)(\n]*	{	/* eat string that starts with a sequence of * followed by anything other than '*', '(', ')' */	}

<COMMENT>\n		{	/* trace line # and reset column related variable */
					line_no++; 
					column_no = tokenCol = 1;
				}

<COMMENT>"*"+")"	{	/* close of a comment */
						comment_depth --;
						if ( comment_depth == 0 )
						{
							BEGIN(INITIAL);	
						}
					}
<COMMENT><<EOF>>	{	/* unclosed comments */
						error(beginLine, beginCol, "unclosed comments");
						yyterminate();
					}


--						{
							// Begin processing line comment.
							beginLine = line_no;
							beginCol = column_no;
							BEGIN (LINE_COMMENT);
						}

/* Ends a line comment upon newline */
<LINE_COMMENT>\n {
    BEGIN(INITIAL); /* Call Begin for Initial */
    newline(); /* Call new line */
}

/* Handles EOF during a line comment */
<LINE_COMMENT><<EOF>> {
    BEGIN(INITIAL); /* Call Begin for Initial */
    newline(); /* Call new line */
}

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
  "-"		{ return '-';}
  "*"		{ return '*';}
  "/"		{ return '/';}
  ">"		{ return '>';}
  "<"		{ return '<';}
  ":"		{ return ':';}
  "("		{ return '(';}
  ")"		{ return ')';}
  "{"		{ return '{';}
  "}"		{ return '}';}
  ";"		{ return ';';}
  "."		{ return '.';}
  ","		{ return ',';}
  "="		{ return '=';}
  "~"		{ return '~';}

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
[Ee][Ss][Aa][Cc]			{ return (ESAC); }
[Ll][Ee][Tt]				{ return (LET); }
[Nn][Oo][Tt]				{ return (NOT); }
[Ii][Ff]					{ return (IF); }
[Tt][Hh][Ee][Nn]			{ return (THEN); }
[Ee][Ll][Ss][Ee]			{ return (ELSE); }
[Ff][Ii]					{ return (FI); }
[Ii][Nn]					{ return (IN); }
[Ww][Hh][Ii][Ll][Ee]		{ return (WHILE); }
[Ll][Oo][Oo][Pp]			{ return (LOOP); }
[Pp][Oo][Oo][Ll]			{ return (POOL); }
[Oo][Ff]					{ return (OF); }
[Nn][Ee][Ww]				{ return (NEW); }
[Ii][Nn][Hh][Ee][Rr][Ii][Tt][Ss]				{ return (INHERITS); }
[II][Ss][Vv][Oo][Ii][Dd]						{ return (ISVOID); }
t[Rr][Uu][Ee]				{ yylval.boolean = true;return BOOLCONST; }
f[Aa][Ll][Ss][Ee]			{ yylval.boolean = false;return BOOLCONST; }

 /*
  * Add all missing rules here
  *
  */
  TYPESYMBOL  { yylval.symbol = idTable.add_string(yytext); return TYPEID;}
  OBJECTSYMBOL  { yylval.symbol = idTable.add_string(yytext); return OBJECTID;}



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