#include <math.h>
#ifdef STDC_HEADERS
#include <stdlib.h>
#include <time.h>
#endif

#ifdef HAVE_MATHERR
int Errno;
#else
#include <errno.h>
#endif

#include "hoc.h"

static double errcheck _PROTO((double d, char *s));

double
Pow(x,y)
	double x,y;
{
	return errcheck(pow(x,y), "exponentiation");
}

/* Builtins: Builtins are all functions taking one double argument and
   returning a double. They are called by the state machine instruction
   bltin(). The pointers to the builtin functions are put in the symbol table
   in BLTIN type variables, in init.c
*/
double
Log(x)
	double x;
{
	return errcheck(log(x), "log");
}
double
Log10(x)
	double x;
{
	return errcheck(log10(x), "log10");
}
double
Sqrt(x)
	double x;
{
	return errcheck(sqrt(x), "sqrt");
}
double
Exp(x)
	double x;
{
	return errcheck(exp(x),"exp");
}
double
integer(x)
	double x;
{
	double iptr;
	modf(x,&iptr);
	return iptr;
}
double
frac(x)
	double x;
{
	return modf(x,&x);
}
double
rnd(limit)
	double limit;
{
	if(((int)limit)==0){
		return 0;
	}
	return (double)((int)rand()%(int)limit);
}
double
randomize(sid)
	double sid;
{
	srand((int)sid);
	return sid;
}
double
Time(dummy)
	double dummy;
{
	return (double)(long)time((long *)0);
}
double
Logamma(x)
	double x;
{
#ifdef HAVE_LGAMMA
	return errcheck(lgamma(x),"logamma");
#else
	return errcheck(gamma(x),"logamma");
#endif
}
double
Sinh(x)
	double x;
{
	return errcheck(sinh(x),"sinh");
}
double
Cosh(x)
	double x;
{
	return errcheck(cosh(x),"cosh");
}
double
Tanh(x)
	double x;
{
	return errcheck(tanh(x),"tanh");
}
double
Tan(x)
	double x;
{
	return errcheck(tan(x),"tan");
}
double
Asin(x)
	double x;
{
	return errcheck(asin(x),"asin");
}
double
Acos(x)
	double x;
{
	return errcheck(acos(x),"acos");
}
double
Gamma(x)
	double x;
{
	extern int signgam;
	double y;
#ifdef HAVE_LGAMMA
	y=errcheck(lgamma(x),"gamma");
#else
	y=errcheck(gamma(x),"gamma");
#endif
	return errcheck(signgam*exp(y), "gamma");
}
double
Sec(x)
	double x;
{
	double y;
	y=cos(x);
	if(y==0){
		execerror("sec","overflow range error");
	}
	return 1/y;
}
double
Cosec(x)
	double x;
{
	double y;
	y=sin(x);
	if(y==0){
		execerror("csc","overflow range error");
	}
	return 1/y;
}
double
Cot(x)
	double x;
{
	return errcheck(tan((3.14159265358979323846/2)-x),"cot");
}

/* End of builtins */
	

static double
errcheck(d,s)
	double d;
	char *s;
{
#ifdef HAVE_MATHERR
	int z=Errno;
	Errno=0;
	switch(z){
	case DOMAIN: execerror(s,"argument domain error"); break;
	case SING: execerror(s,"argument singularity"); break;
	case OVERFLOW: execerror(s, "overflow range error"); break;
	case UNDERFLOW: execerror(s, "underflow range error"); break;
	}
#else
	int z=errno;
	errno=0;
	switch(z){
	case EDOM: execerror(s,"argument domain error"); break;
	case ERANGE: execerror(s,"overflow range error"); break;
	}
#endif
	return d;
}
#ifdef HAVE_MATHERR
int
matherr(x)
	register struct exception *x;
{
	Errno=x->type; return 1;
}
#endif
