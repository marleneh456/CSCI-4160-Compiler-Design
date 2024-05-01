#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "ErrorMsg.h"
#include "tokens.h"
#include <FlexLexer.h>

using namespace std;

string toknames[] = {
"CLASS","ELSE","FI","IF","IN","INHERITS","LET","LOOP","POOL", 
"THEN","WHILE","CASE","ESAC","OF","DARROW","NEW","ISVOID",
"STR_CONST","INT_CONST","BOOL_CONST","TYPEID","OBJECTID","ASSIGN",
"NOT","LE","ERROR","LET_STMT" };


string tokname(int tok) {
  return tok<257 || tok>299 ? "BAD_TOKEN": toknames[tok-258];
}

yyFlexLexer			lexer;
YYSTYPE				yylval;

int main(int argc, char **argv) {
	ifstream	ifs; 
	extern int			beginLine, beginCol;	//beginning position of string or comment
	extern int			line_no, column_no;			//beginning position of all other tokens
	extern ErrorMsg		errormsg;
	int			tok;
	
	if (argc!=2) 
	{
		cerr << "usage: " << argv[0] << " filename" << endl;
		return 1;	
	}
	ifs.open( argv[1] );
	if( !ifs ) 
	{
		cerr << "Input file cannot be opened.\n";
        return 0;
	}
	cout << "Lexcial Analysis of the file " << argv[1] << endl;
	errormsg.reset( argv[1] );
	lexer.switch_streams(&ifs, NULL);
	for(;;) {
		tok = lexer.yylex();
		if (tok==0) break;
		switch(tok) {
		case TYPEID:
		case OBJECTID:
		case STRCONST:
			cout << setw(10) << tokname(tok) << " " << setw(2) << line_no << ":" 
				 << setw(3) << column_no << " " << yylval.symbol->getData() << endl;
			break;
		case INTCONST:
			cout << setw(10) << tokname(tok) << " " << setw(2) << line_no << ":" 
				 << setw(3) << column_no << " " << yylval.symbol->getData() << endl;
			break;
		case BOOLCONST:
			cout << setw(10) << tokname(tok) << " " << setw(2) << line_no << ":"
				<< setw(3) << column_no << " " << (yylval.boolean ? "true":"false") << endl;
			break;
		default:
			cout << setw(10) << (tok>256? tokname(tok):string(1, char(tok))) << " " << setw(2) << line_no << ":" 
				 << setw(3) << column_no << endl;
		}
	}
	return 0;
}
