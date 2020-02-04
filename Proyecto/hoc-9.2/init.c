#include "hoc.h"
#ifndef MSDOS
#include "y.tab.h"
#else
#include "y.h"
#endif
#include <math.h>

static struct {
	char *name;
	int kval;
} keywords[] = {
	"proc",		PROC,		/* define a procedure */
	"procedure",	PROC,
	"func",		FUNC,		/* define a function */
	"function",	FUNC,
	"return",	RETURN,		/* return from func/proc */
	"if",		IF,		/* if statement */
	"else",		ELSE,		/* else part of if */
	"while",	WHILE,		/* while statement */
	"print",	PRINT,		/* print things */
	"read",		READ,		/* read a variable */
	"exit",		EXIT,		/* exit from hoc */
	"quit",		EXIT,
	"bye",		EXIT,
	"break",	BREAK,		/* exit loop */
	"continue",	CONT,		/* continue loop */
	"sh",		SYSTEM,		/* execute thing in shell */
	"level",	LEVEL,		/* print recursion level + stack use */
	"mod",		MOD,		/* modulo operator */
	"for",		FOR,		/* for(s;e;s)stmt - the s is a statement
					   and the e is an expresion. the s's and
					   e's are optional. */
	"names",	PRNAMES,	/* print all keywords, builtins, functions,
					   procedures, and variable names defined */
	"local",	LOCALCMD,	/* make local variable */
	"set",		SET,		/* change/view setting */
	"include",	INCLUDE,	/* read another hoc file */
	"type",		TYPE,		/* find type of item */
	"const",	CONSTCMD,	/* make constant */
	"version",	VERSION,	/* print version */
	"callfunc",	CALLFUNC,	/* call function */
	"callproc",	CALLPROC,	/* call procedure */
	"abort",	ABORT,		/* abort with execerror */
	"eof",		DOEOF,		/* end current file (even if stdin) */
	"cd",		CHDIR,		/* change directory */
	0,		0,
};
static struct {
	char *name;
	double cval;
} consts[]= {
	"PI",		3.14159265358979323846,	/*circumference/diameter*/
	"E",		2.71828182845904523546,	/*base of natural logarithms*/
	"GAMMA",	0.57721566490153286060,	/*Euler-Marscheroni constant*/
	                                        /*lim (\sum_1^n{1/i})-log(n)*/
	"DEG",		57.29577951308232087680,/*180/PI - deg/radian*/
	"PHI",		1.61803398874989484820,	/*(sqrt(5)+1)/2 golden ratio*/
	"NSTACK",	NSTACK,	/*stack size*/
	"NFRAME",	NFRAME, /*number of times a func/proc can call itself*/
	"T_UNDEF",	0.0,	/* undefined identifier type */
	"T_VAR",	1.0,	/* variable type */
	"T_FUNC",	2.0,	/* function type */
	"T_PROC",	3.0,	/* procedure type */
	"T_LOCAL",	4.0,	/* local variable type */
	"T_BLTIN",	5.0,	/* builtin function type */
	"T_KEYWORD",	6.0,	/* builtin keyword type */
#if unix
	"OSTYPE",	1.0,
#elif MSDOS
	"OSTYPE",	2.0,
#endif
	"OS_UNIX",	1.0,
	"OS_DOS",	2.0,
	0,		0
};
static struct {
	char *name;
	Builtinp func;
} builtins[] = {
	"sin",sin,		/* sine */
	"cos",cos,		/* cosine */
	"tan",Tan,		/* tangent */
	"log",Log,		/* log base E */
	"log10",Log10,		/* log base 10 */
	"exp",Exp,		/* antilog base E */
	"sqrt",Sqrt,		/* square root */
	"int",integer,		/* integer part of number */
	"frac",frac,		/* fraction part of number */
	"abs",fabs,		/* absolute value */
	"rnd",rnd,		/* generate random number */
	"randomize",randomize,	/* set random generator seed */
	"time",Time,		/*get time in seconds from 12:00pm Jan 1,1970*/
	"logamma",Logamma,	/* log gamma */
	"gamma",Gamma,		/* gamma */
	"sinh",Sinh,		/* hyperbolic sine */
	"cosh",Cosh,		/* hyperbolic cosine */
	"tanh",Tanh,		/* hyperbolic tangent */
	"asin",Asin,		/* inverse sine */
	"acos",Acos,		/* inverse cosine */
	"atan",atan,		/* inverse tangent */
	"csc",Cosec,		/* cosecant */
	"sec",Sec,		/* secant */
	"cot",Cot,		/* cotangent */
	"arg",Arg,		/* return argument number n. */
	"floor",floor,		/* floor */
	0,0
};

Symbol *vpERROR, *vpDIGITS;

void
init()
{
	int i;
	Symbol *s;
	for(i=0;keywords[i].name; i++)
		install(keywords[i].name,keywords[i].kval, 0.0);
	for(i=0;consts[i].name; i++){
		s=install(consts[i].name, CONST, 0.0);
		s->u.Const=installd(consts[i].cval);
	} for(i=0;builtins[i].name; i++){
		s=install(builtins[i].name,BLTIN,0.0);
		s->u.ptr=builtins[i].func;
	}
	vpERROR=install("ERROR", VAR, 1e-6);
	vpDIGITS=install("DIGITS", VAR, 6.);
}
