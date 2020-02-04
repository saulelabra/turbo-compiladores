/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EXIT = 258,
    BREAK = 259,
    CONT = 260,
    DEBUG = 261,
    LEVEL = 262,
    MOD = 263,
    PRCALLS = 264,
    IGNOREUNDEF = 265,
    LOCALCMD = 266,
    STRING = 267,
    PRINT = 268,
    VAR = 269,
    BLTIN = 270,
    UNDEF = 271,
    WHILE = 272,
    IF = 273,
    ELSE = 274,
    FOR = 275,
    PRNAMES = 276,
    INCLUDE = 277,
    FUNCTION = 278,
    PROCEDURE = 279,
    RETURN = 280,
    FUNC = 281,
    PROC = 282,
    READ = 283,
    SYSTEM = 284,
    LOCAL = 285,
    SET = 286,
    CONSTCMD = 287,
    CONST = 288,
    VERSION = 289,
    TYPE = 290,
    CALLFUNC = 291,
    CALLPROC = 292,
    ABORT = 293,
    DOEOF = 294,
    CHDIR = 295,
    ARG = 296,
    ARGCNT = 297,
    NUMBER = 298,
    ADDEQ = 299,
    SUBEQ = 300,
    MULEQ = 301,
    DIVEQ = 302,
    POWEQ = 303,
    REMEQ = 304,
    OR = 305,
    AND = 306,
    GT = 307,
    GE = 308,
    LT = 309,
    LE = 310,
    EQ = 311,
    NE = 312,
    APPROXEQ = 313,
    NOTAPPROXEQ = 314,
    UNARYMINUS = 315,
    NOT = 316,
    INCR = 317,
    DECR = 318
  };
#endif
/* Tokens.  */
#define EXIT 258
#define BREAK 259
#define CONT 260
#define DEBUG 261
#define LEVEL 262
#define MOD 263
#define PRCALLS 264
#define IGNOREUNDEF 265
#define LOCALCMD 266
#define STRING 267
#define PRINT 268
#define VAR 269
#define BLTIN 270
#define UNDEF 271
#define WHILE 272
#define IF 273
#define ELSE 274
#define FOR 275
#define PRNAMES 276
#define INCLUDE 277
#define FUNCTION 278
#define PROCEDURE 279
#define RETURN 280
#define FUNC 281
#define PROC 282
#define READ 283
#define SYSTEM 284
#define LOCAL 285
#define SET 286
#define CONSTCMD 287
#define CONST 288
#define VERSION 289
#define TYPE 290
#define CALLFUNC 291
#define CALLPROC 292
#define ABORT 293
#define DOEOF 294
#define CHDIR 295
#define ARG 296
#define ARGCNT 297
#define NUMBER 298
#define ADDEQ 299
#define SUBEQ 300
#define MULEQ 301
#define DIVEQ 302
#define POWEQ 303
#define REMEQ 304
#define OR 305
#define AND 306
#define GT 307
#define GE 308
#define LT 309
#define LE 310
#define EQ 311
#define NE 312
#define APPROXEQ 313
#define NOTAPPROXEQ 314
#define UNARYMINUS 315
#define NOT 316
#define INCR 317
#define DECR 318

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 55 "hoc.y" /* yacc.c:1909  */

	Symbol	*sym;	/* symbol table pointer */
	Inst	*inst;	/* machine instruction */
	int	narg;	/* number of arguments */
	Constant *Const;/* constant number */

#line 187 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
