/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     STRING = 259,
     PRINT = 260,
     VAR = 261,
     BLTIN = 262,
     UNDEF = 263,
     WHILE = 264,
     IF = 265,
     ELSE = 266,
     NEW = 267,
     ARRAY = 268,
     FUNCTION = 269,
     PROCEDURE = 270,
     YEET = 271,
     FUNC = 272,
     PROC = 273,
     READ = 274,
     ARG = 275,
     OR = 276,
     AND = 277,
     NE = 278,
     EQ = 279,
     LE = 280,
     LT = 281,
     GE = 282,
     GT = 283,
     NOT = 284,
     UNARYPLUS = 285,
     UNARYMINUS = 286
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define STRING 259
#define PRINT 260
#define VAR 261
#define BLTIN 262
#define UNDEF 263
#define WHILE 264
#define IF 265
#define ELSE 266
#define NEW 267
#define ARRAY 268
#define FUNCTION 269
#define PROCEDURE 270
#define YEET 271
#define FUNC 272
#define PROC 273
#define READ 274
#define ARG 275
#define OR 276
#define AND 277
#define NE 278
#define EQ 279
#define LE 280
#define LT 281
#define GE 282
#define GT 283
#define NOT 284
#define UNARYPLUS 285
#define UNARYMINUS 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 7 "hoc.y"
{
    Symbol *sym; /* Symbol table pointer */
    Inst *inst; /* Instruction */
    int narg; /* Number of arguments */
}
/* Line 1529 of yacc.c.  */
#line 117 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

