
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 5 "COOL.yy"

#include <iostream>
#include "ErrorMsg.h"
#include <FlexLexer.h>
#include "StringTab.h"
#include "Absyn.h"

using namespace absyn;



/* Line 1676 of yacc.c  */
#line 52 "COOL.tab.hh"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     STR_CONST = 258,
     TYPEID = 259,
     OBJECTID = 260,
     INT_CONST = 261,
     BOOL_CONST = 262,
     CLASS = 263,
     ELSE = 264,
     FI = 265,
     IF = 266,
     IN = 267,
     INHERITS = 268,
     LET = 269,
     LOOP = 270,
     POOL = 271,
     THEN = 272,
     WHILE = 273,
     CASE = 274,
     ESAC = 275,
     OF = 276,
     DARROW = 277,
     NEW = 278,
     ISVOID = 279,
     ASSIGN = 280,
     NOT = 281,
     LE = 282,
     LET_STMT = 283
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 15 "COOL.yy"

	Symbol			symbol;
	bool			boolean;
	Program			program;
	Class_			class_;
	Classes			classes;
	Feature			feature;
	Features		features;
	Formal			formal;
	Formals			formals;
	Branch			branch;
	Branches		branches;
	Expression		expression;
	Expressions		expressions;



/* Line 1676 of yacc.c  */
#line 115 "COOL.tab.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

