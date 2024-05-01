#pragma once
#include "StringTab.h"

//YYSTYPE defines the structure to hold values
//assoicated with tokens. This structure will 
//be defined in the parser //in the future
typedef union  {
	bool	boolean;	
	Symbol	symbol;	
} YYSTYPE;

extern YYSTYPE yylval;	//yylval will be defined in the driver.

#define CLASS 258
#define ELSE 259
#define FI 260
#define IF 261
#define IN 262
#define INHERITS 263
#define LET 264
#define LOOP 265
#define POOL 266
#define THEN 267
#define WHILE 268
#define CASE 269
#define ESAC 270
#define OF 271
#define DARROW 272
#define NEW 273
#define ISVOID 274
#define STRCONST 275
#define INTCONST 276
#define BOOLCONST 277
#define TYPEID 278
#define OBJECTID 279
#define ASSIGN 280
#define NOT 281
#define LE 282
#define ERROR 283
#define LETSTMT 285

