#include "hoc.h"

#ifndef MSDOS
#include "y.tab.h"
#else
#include "y.h"
#endif

#include <stdio.h>
#include <ctype.h>

#ifdef STDC_HEADERS
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#else
char *malloc(),*memcpy();
double fmod();
#endif


static Datum stack[NSTACK];
static Datum *stackp;

extern FILE *fin;
#include <setjmp.h>
extern jmp_buf begin;

Inst prog[NPROG];
Inst *progp;
Inst *pc;
Inst *progbase=prog;
int returning,whilebreak,whilecont;
int inwhile;
Frame frame[NFRAME];
Frame *fp;

/* set by Set() and used by other routines */
static int Sprcalls=0,prcalls=0;
static int Signoreundef=0,ignoreundef=0;
static int Sallnames=0,allnames=0;

void
initcode()
{
	progp=progbase;
	stackp=stack;
	fp=frame;
	returning=0;
	whilebreak=0;
	whilecont=0;
	inwhile=0;
	indef=0;
}
static void
push(d)
	Datum d;
{
	if(stackp>=&stack[NSTACK])
		execerror("stack too deep", (char *)0);
	*stackp++=d;
}
static void
pushd(d)
	double d;
{
	if(stackp>=&stack[NSTACK])
		execerror("stack too deep", (char *)0);
	(*stackp++).val=d;
}
static Datum
pop()
{
	if(stackp==stack)
		execerror("stack underflow", (char *)0);
	return *--stackp;
}
void
define(sp)
	Symbol *sp;
{
	Inst *tmp;
	Inst *tmp1;
	if(sp->u.defn!=(Inst)deffunc&&sp->u.defn!=(Inst)defproc){
		free((Inst*)sp->u.defn);
	}

	tmp1=(Inst*)emalloc((progp-prog)*sizeof(Inst));
	sp->u.defn=(Inst)tmp1;
	tmp=prog;
	while(tmp<progp)
		*tmp1++= *tmp++;
	progp=prog;
}
static
double *
getarg()
{
	int nargs=INSTTOI(*pc++);
	/* we assume that the given argument number nargs can never be
	   <=0 (since that is checked in the lexical analyzer yylex())
	   so we only have to check whether it is too large.
	*/
	if(nargs>fp->nargs)
		execerror(fp->sp->name, "not enough arguments");
	return &fp->argn[nargs-fp->nargs].val;
}
static double
getval(v)
	Symbol *v;
{
	switch(v->type){
	case UNDEF:
		if(ignoreundef)
			return 0;
		else
			execerror(v->name,"is used before defined");
	case VAR:
		return v->u.val;
	case LOCAL:
		if(v->u.localptr->p.frame!=fp){
			/* found local from another function. look for the
			   global with the same name */
			/* ->nextdef because global can't be first */
			Local *x=v->u.localptr->nextdef;
			while(x->nextdef)
				x=x->nextdef;
			if(x->p.type==UNDEF){
				if(ignoreundef){
					return 0;
				} else
					execerror(v->name,"is used before defined");
			} else
				return x->val;
		} else {
			return v->u.localptr->val;
		}
		break;	
	default:
		execerror(v->name,"is not a varible");
		break;
	}
}	
/* getvar pops a variable (pushed by varpush) from the stack, and returns the
   address of the value of the variable, so it can be used and assigned. it
   gives an error if the variable is undefined, and an assignment to
   non-variable error if it isn't a variable.
   Because of the errors it prints, it was meant to be called by functions
   which both use the value of the variable and assign it a new variable,
   like in ++, +=, and etc.
*/
static double *
getvar()
{
	Datum d;
	d=pop();
	switch(d.sym->type){
	case UNDEF:
		if(ignoreundef){
			d.sym->u.val=0;
			d.sym->type=VAR;
			return &(d.sym->u.val);
		} else
			execerror(d.sym->name,"is used before defined");
		break;
	case VAR:
		return &(d.sym->u.val);
	case LOCAL:
		if(d.sym->u.localptr->p.frame!=fp){
			Local *x=d.sym->u.localptr->nextdef;
			while(x->nextdef)
				x=x->nextdef;
			if(x->p.type==UNDEF){
				if(ignoreundef){
					x->val=0;
					x->p.type=VAR;
				} else
					execerror(d.sym->name,"is used before defined");
			}
			return &(x->val);
		} else {
			return &(d.sym->u.localptr->val);
		}
	default:
		execerror("assignment to non-variable",d.sym->name);
	}
}
void
Line(lineinfile,filename)
	Inst filename, lineinfile;
{
	infile=((char *)filename);
	if(infile[0]=='\0')
		infile=(char*)0;
	lineno=((int)(((Constant *)lineinfile)->d))-1;
}
Inst *
code(f)
	Inst f;
{
	Inst *oprogp=progp;
	if(progp>=&prog[NPROG])
		execerror("program too big", (char *)0);
	*progp++=f;
	return oprogp;
}
void
move(p,n)
	Inst *p;
	int n;
{
	Inst *tmp;
	tmp=progp-1;
	progp+=n;
	if(progp>=&prog[NPROG])
		execerror("program too big", (char *)0);
	for(;tmp>=p;tmp--){
		tmp[n]=tmp[0];
	}
}
void
execute(p)
	Inst *p;
{
	/* By definition in the construct (*(*pc++))(), the function should
	   see the increased pc (with this construct the function pointed to
	   in the current position of pc is called, as in (*pc[0])(), but the
	   pc passed to it is the next pc).
	   In fact not only does it makes sense, the ANSI C standard defines
	   the concept "sequence point" which states that after a sequence
	   point (and only after one) all side effects are guaranteed to have
	   happened. As it turns out one sequence point is after the function's
	   parameters AND THE EXPRESSION OF THE FUNCTION ITSELF are evaluated -
	   and that is before the function is actually called.
	   However, IBM AIX 2.3's compiler has a bug that causes the side
	   effect to happen only after the function call. This is the only
	   compiler I know with that bug.

	   I could have used the alternate expression in all cases, instead
	   of having a compilation flag, since the alternate expression
	   always works.
	*/
#ifndef COMPILER_BUG_INCR
	for(pc=p;*pc!=STOP && !returning && !whilebreak && !whilecont;)
		(*(*pc++))();
#else
	for(pc=p;*pc!=STOP && !returning && !whilebreak && !whilecont;){
		++pc;
		(*(pc[-1]))();
	}
#endif
}
/****************************************************************************/
/* Stack machine instructions. Pointers to the following functions can be
   are used as instructions for our stack machines. Note that all these
   functions must be of type SMI (stack machine instruction), since
   the pointer, Inst, is declared as a pointer to a function returning SMI.
   The size of this return value is very important in execute(), where the
   C compiler needs to prepare memory for the return value. (This importance
   is illustrated by the need of popandforget() instead of using using a
   pointer to pop() - which caused a serious and hard-to-find bug in hoc8).
   SMI is typically void.
*/
SMI
constpush()
{
	Datum d;
	d.val=((Constant *)*pc++)->d;
	push(d);
}

SMI
Set()
{
	switch(INSTTOI(*pc++)){
	case S_IGNOREUNDEF:
		ignoreundef=1;break;
	case -S_IGNOREUNDEF:
		ignoreundef=0;break;
	case S_TRACECALLS:
		prcalls=1;break;
	case -S_TRACECALLS:
		prcalls=0;break;
	case S_ALLNAMES:
		allnames=1;break;
	case -S_ALLNAMES:
		allnames=0;break;
	case S_ALL:
		fprintf(stderr,"%signoreundef\n%stracecalls\n%sallnames\n",
			ignoreundef?"":"no",prcalls?"":"no",allnames?"":"no");
#if YYDEBUG
		{	extern int yydebug;
			if(!yydebug)fprintf(stderr,"nodebug\n");
			else
				fprintf(stderr,"debug%d\n",yydebug);
		}
#endif
		break;
	case S_DEFAULT:
		prcalls=Sprcalls; ignoreundef=Signoreundef; allnames=Sallnames;
#if YYDEBUG
		{	extern int yydebug;
			yydebug=0;
		}
#endif
		break;
	case S_CHANGED:
		if(prcalls!=Sprcalls)
			fprintf(stderr,"%stracecalls\n",prcalls?"":"no");
		if(ignoreundef!=Signoreundef)
			fprintf(stderr,"%signoreundef\n",ignoreundef?"":"no");
		if(allnames!=Sallnames)
			fprintf(stderr,"%sallnames\n",allnames?"":"no");
#if YYDEBUG
		{	extern int yydebug;
			if(yydebug!=0)
				fprintf(stderr,"debug%d\n",yydebug);
		}
#endif
		break;
	}
}
SMI
varpush()
{
	Datum d;
	d.sym=(Symbol *)(*pc++);
	push(d);
}
SMI
whilecode()
{
	Datum d;
	Inst *savepc=pc;
	Inst *PA=savepc+INSTTOI(*(savepc));
	Inst *PB=savepc+2;
	int z;
	z=inwhile;
	execute(PB);
	d=pop();
	inwhile++;
	while(d.val){
		execute(PA);
		if(whilebreak){
			whilebreak--;
			break;
		} else if(returning){
			goto RETURNING;
		}
		whilecont=0;
		execute(PB);
		d=pop();
	}
	pc=savepc+INSTTOI(*(savepc+1));
RETURNING:
	inwhile=z;
}
SMI
forcode()
{
	Datum d;
	Inst *savepc=pc;
	int z;
	int B=INSTTOI(*(savepc+1));
	int C=INSTTOI(*(savepc+2));
	Inst *PB=savepc+B;
	Inst *PC=savepc+C;
	Inst *PD=savepc+INSTTOI(*(savepc+3));
	z=inwhile;
	inwhile=0;
	if(INSTTOI(*(savepc))) execute(savepc+INSTTOI(*(savepc)));
	if(returning)goto RETURNING;
	inwhile=z+1;
	if(B){
		execute(PB);
		d=pop();
	} else {
		d.val = 1.0;
	}
	while(d.val){
		execute(PD);
		if(whilebreak){
			whilebreak--;
			break;
		} else if(returning){
			goto RETURNING;
		}
		whilecont=0;
		if(C){
			execute(PC);
			if(whilebreak){
				whilebreak--;
				break;
			} else if(returning){
				goto RETURNING;
			}
			whilecont=0;
		}
		if(B){
			execute(PB);
			d=pop();
		}
	}
	pc=savepc+INSTTOI(*(savepc+4));
RETURNING:
	inwhile=z;
}	
SMI
ifcode()
{
	Datum d;
	Inst *savepc=pc;
	execute(savepc+3);
	d=pop();
	if (d.val)
		execute(savepc+INSTTOI(*(savepc)));
	else if (INSTTOI(*(savepc+1)))
		execute(savepc+INSTTOI(*(savepc+1)));
	if(!returning)
		pc=savepc+INSTTOI(*(savepc+2));
}
SMI
conditional()
{
	Datum d;
	Inst *savepc=pc;
	execute(savepc+INSTTOI(*(savepc)));
	d=pop();
	if(d.val)execute(savepc+3);
	else execute(savepc+INSTTOI(*(savepc+1)));
	pc=savepc+INSTTOI(*(savepc+2));
}
SMI
call()
{
	Symbol *sp=(Symbol *)pc[0];
	int sinwhile;

	if(INSTTOI(pc[2])!=sp->type)
		execerror(sp->name,"called after type changed");

	if(fp++>=&frame[NFRAME-1]){
		/* the fp--; must be done because execerror frees the locals
		    and fp must be in the frame. */
		fp--;
		execerror(sp->name,"call nested too deeply");
	}
	fp->sp=sp;
	fp->nargs=INSTTOI(pc[1]);
	fp->retpc=pc+3;
	fp->argn=stackp-1;
	fp->locals=0;
	if(prcalls){
		int i,z;
		Datum *x,*y;
		y=stackp-1;
		z=fp-&frame[0];
		for(i=0;i<z;i++){
			putc('-',stderr);
		}
		fprintf(stderr,"%s(",fp->sp->name);
		for(x=stackp-INSTTOI(pc[1]);x<=y;x++){
			fprintf(stderr,"%g",x->val);
			if(x!=y)putc(',',stderr);
		}
		putc(')',stderr);
		putc('\n',stderr);
	}
	sinwhile=inwhile;
	inwhile=0;
	execute((Inst *)sp->u.defn);
	inwhile=sinwhile;
	returning=0;
}
SMI
ret()
{
	int i;
	if(fp->locals){
		/* free all local variables of current function */
		/* same code as in execerror() */
		Local *tmp=fp->locals, *tmp1;
		while(tmp1=tmp){
			tmp=tmp1->nextlocal;
			if(!tmp1->nextdef->nextdef){
				/* next one is global/undef */
				tmp1->real->u.val=
					tmp1->nextdef->val;
				tmp1->real->type=
					tmp1->nextdef->p.type;
				FREELOCAL(tmp1->nextdef);
				FREELOCAL(tmp1);
				continue;
			}
			tmp1->real->u.localptr=tmp1->nextdef;
			FREELOCAL(tmp1);
		}
	}
	for(i=0;i<fp->nargs; i++)
		pop();
	pc=(Inst *)fp->retpc;
	--fp;
	returning=1;
}
/* makelocal: make some variable local, and assign it a value */
SMI
makelocal()
{
	Datum d1,d2;
	double tmp1;
	Local *tmp;

	d1=pop();	/* var to make local */
	d2=pop();	/* initial value of the local */

	switch(d1.sym->type){
	case UNDEF:	/* variable undefined */
		/* put the new local var */
		d1.sym->type=LOCAL;
		d1.sym->u.localptr=NEWLOCAL();
		d1.sym->u.localptr->val=d2.val;
		d1.sym->u.localptr->p.frame=fp;
		d1.sym->u.localptr->real=d1.sym;
		/* move the undef var to a Local structure */
		d1.sym->u.localptr->nextdef=NEWLOCAL();
		d1.sym->u.localptr->nextdef->real=d1.sym;
		d1.sym->u.localptr->nextdef->p.type=UNDEF;
		break;
	case VAR:	/* variable already defined as global */
		tmp1=d1.sym->u.val;
		/* put the new local var */
		d1.sym->type=LOCAL;
		d1.sym->u.localptr=NEWLOCAL();
		d1.sym->u.localptr->val=d2.val;
		d1.sym->u.localptr->p.frame=fp;
		d1.sym->u.localptr->real=d1.sym;
		/* move the global var to a Local structure */
		d1.sym->u.localptr->nextdef=NEWLOCAL();
		d1.sym->u.localptr->nextdef->val=tmp1;
		d1.sym->u.localptr->nextdef->real=d1.sym;
		d1.sym->u.localptr->nextdef->p.type=VAR;
		break;
	case LOCAL:	/* variable already defined as local */
		if(d1.sym->u.localptr->p.frame==fp){/* same local defined twice
						       in same function */
			d1.sym->u.localptr->val=d2.val;
			goto PUSH;
		}
		tmp=d1.sym->u.localptr;
		d1.sym->u.localptr=NEWLOCAL();
		d1.sym->u.localptr->val=d2.val;
		d1.sym->u.localptr->nextdef=tmp;
		d1.sym->u.localptr->p.frame=fp;
		d1.sym->u.localptr->real=d1.sym;
		break;
	default:	/* ERROR */
		execerror("attempt to make a local with a non-variable name",
			d1.sym->name);
		break;
	}
	/* put local on the locals-to-free list */
	tmp=fp->locals;
	fp->locals=d1.sym->u.localptr;
	d1.sym->u.localptr->nextlocal=tmp;
PUSH:
	push(d2);
}
SMI 
Break()
{
	if(inwhile)
		whilebreak++;
	else
		execerror("break","not in while");
}
SMI
Breakn()
{
	Datum d;
	d=pop();
	if(inwhile<whilebreak+d.val)
		execerror("break","level greater than loop level");
	whilebreak+=d.val;
}
SMI
cont()
{
	if(inwhile)
		whilecont=1;
	else
		execerror("continue", "not in while");
}
SMI
contn()
{
	Datum d;
	d=pop();
	if(inwhile<whilebreak+d.val)
		execerror("continue", "level greater than loop level");
	whilebreak+=d.val-1;
	whilecont=1;
}
SMI
Abort()
{
	if(fp==frame)
		execerror("program aborted",(char*)0);
	else
		execerror(fp->sp->name, "aborted");
}
/* end current file, even if it is stdin */
SMI
Doeof()
{
	execerror((char*)0,(char*)0);
}
SMI
funcret()
{
	Datum d;
	if(fp->sp->type==PROCEDURE)
		execerror(fp->sp->name, "(proc) returns value");
	d=pop();
	if(prcalls){
		int i,z;
		z=fp-&frame[0];
		for(i=0;i<z;i++){
			putc('-',stderr);
		}
		fprintf(stderr,"%s returns %g\n",fp->sp->name,d.val);
	}
	ret();
	push(d);
}
SMI
procret()
{
	if(fp->sp->type==FUNCTION)
		execerror(fp->sp->name, "(func) returns no value");
	if(prcalls){
		int i,z;
		z=fp-&frame[0];
		for(i=0;i<z;i++){
			putc('-',stderr);
		}
		fprintf(stderr,"%s returns\n",fp->sp->name);
	}
	ret();
}
SMI
arg()
{
	Datum d;
	/* the following complication is because a bug in unixpc C */
	register double *temp;
	temp = getarg ();
	d.val = *temp;
	push(d);
}
SMI
argcnt()
{
	Datum d;
	d.val = fp->nargs;
	push(d);
}
SMI
argassign()
{
#ifdef BUG1
	Datum d;
	register double *temp;
	temp = getarg();
	d=pop();
	push(d);
	*temp=d.val;
#else
	Datum d;
	push(d=pop());
	*getarg()=d.val;
#endif
}
SMI
argaddeq()
{
#ifdef BUG1
	register double *temp=getarg();
	Datum d;
	d=pop();
	*temp+=d.val;
	pushd(*temp);
#else
	Datum d;
	d=pop();
	pushd(*getarg()+=d.val);
#endif
}
SMI
argsubeq()
{
#ifdef BUG1
	register double *temp=getarg();
	Datum d;
	d=pop();
	*temp-=d.val;
	pushd(*temp);
#else
	Datum d;
	d=pop();
	pushd(*getarg()-=d.val);
#endif
}
SMI
argmuleq()
{
#ifdef BUG1
	register double *temp=getarg();
	Datum d;
	d=pop();;
	*temp*=d.val;
	pushd(*temp);
#else
	Datum d;
	d=pop();
	pushd(*getarg()*=d.val);
#endif
}
SMI
argdiveq()
{
#ifdef BUG1
	register double *temp=getarg();
	Datum d;
	d=pop();
	if(d.val==0.0)
		execerror("division by zero", (char *)0);
	*temp/=d.val;
	pushd(*temp);
#else
	Datum d;
	d=pop();
	if(d.val==0.0)
		execerror("division by zero", (char *)0);
	pushd(*getarg()/=d.val);
#endif
}
SMI
argpoweq()
{
#ifdef BUG1
	register double *temp=getarg();
	Datum d;
	d=pop();
	*temp=Pow(*temp,d.val);
	pushd(*temp);
#else
	register double *temp=getarg();
	Datum d;
	d=pop();
	pushd(*temp=Pow(*temp,d.val));
#endif
}
SMI
argmodeq()
{
#ifdef BUG1
	register double *temp=getarg();
	Datum d;
	d=pop();
	if(d.val==0.0)
		execerror("division by zero",(char *)0);
	*temp=fmod(*temp,d.val);
	pushd(*temp);
#else
	register double *temp=getarg();
	Datum d;
	d=pop();
	if(d.val==0.0)
		execerror("division by zero",(char *)0);
	pushd(*temp=fmod(*temp,d.val));
#endif
}
SMI
argpreinc()
{
#ifdef BUG1
	register double *temp=getarg();
	++(*temp);
	pushd(*temp);
#else
	pushd(++(*getarg()));
#endif
}
SMI
argpostinc()
{
#ifdef BUG1
	register double *temp=getarg();
	pushd(*temp);
	++(*temp);
#else
	pushd((*getarg())++);
#endif
}
SMI
argpredec()
{
#ifdef BUG1
	register double *temp=getarg();
	--(*temp);
	pushd(*temp);
#else
	pushd(--(*getarg()));
#endif
}
SMI
argpostdec()
{
#ifdef BUG1
	register double *temp=getarg();
	pushd(*temp);
	--(*temp);
#else
	pushd((*getarg())--);
#endif
}
SMI
bltin()
{
	Datum d;
	d=pop();
	d.val=(*(double (*)())*pc++)(d.val);
	push(d);
}
SMI
eval()
{
	Datum d;
	d=pop();
	switch(d.sym->type){
	case UNDEF:
		if(ignoreundef)
			d.val=0;
		else
			execerror(d.sym->name,"is used before defined");
		break;
	case VAR:
		d.val=d.sym->u.val;
		break;
	case LOCAL:
		if(d.sym->u.localptr->p.frame!=fp){
			/* found local from another function. look for the
			   global with the same name */
			/* ->nextdef because global can't be first */
			Local *x=d.sym->u.localptr->nextdef;
			while(x->nextdef)
				x=x->nextdef;
			if(x->p.type==UNDEF){
				if(ignoreundef){
					d.val=0;
				} else
					execerror(d.sym->name,"is used before defined");
			} else
				d.val=x->val;
		} else {
			d.val=d.sym->u.localptr->val;
		}
		break;	
	default:
		execerror("attempt to evaluate non-varible",d.sym->name);
		break;
	}
	push(d);
}
SMI
add()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	d1.val+=d2.val;
	push(d1);
}
SMI
sub()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	d1.val-=d2.val;
	push(d1);
}
SMI
mul()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	d1.val*=d2.val;
	push(d1);
}
SMI
Div()
{
	Datum d1,d2;
	d2=pop();
	if(d2.val==0.0)
		execerror("division by zero", (char *)0);
	d1=pop();
	d1.val/=d2.val;
	push(d1);
}
SMI
mod()
{	/* remainder */
	Datum d1,d2;
	d2=pop();
	if(d2.val==0.0)
		execerror("division by zero", (char *)0);
	d1=pop();
	d1.val=fmod(d1.val,d2.val);
	push(d1);
}
SMI
Mod()
{	/* modulo: like in math */
	Datum d1,d2;
	d2=pop();
	if(d2.val==0.0)
		execerror("division by zero", (char *)0);
	d1=pop();
	d1.val=fmod(d2.val+fmod(d1.val,d2.val),d2.val);
	push(d1);
}
SMI
negate()
{
	Datum d;
	d=pop();
	d.val= -d.val;
	push(d);
}
SMI
gt()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	d1.val=(double)(d1.val > d2.val);
	push(d1);
}
SMI
lt()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	d1.val=(double)(d1.val < d2.val);
	push(d1);
}
SMI
ge()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	d1.val=(double)(d1.val >= d2.val);
	push(d1);
}
SMI
le()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	d1.val=(double)(d1.val <= d2.val);
	push(d1);
}
SMI
eq()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	d1.val=(double)(d1.val == d2.val);
	push(d1);
}
#define ABS(x) ((x)<0 ? -(x) : (x))
SMI
approxeq()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	pushd((double)(ABS(d1.val-d2.val)<=getval(vpERROR)));
}
SMI
notapproxeq()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	pushd((double)(ABS(d1.val-d2.val)>=getval(vpERROR)));
}
SMI
ne()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	d1.val=(double)(d1.val != d2.val);
	push(d1);
}
SMI
and()
{
	Datum d;
	Inst *savepc=pc;
	execute(savepc+2);
	d=pop();
	if(d.val){
		execute(savepc+INSTTOI(*(savepc)));
		d=pop();
	}
	pc=savepc+INSTTOI(*(savepc+1));
	/* and must return 1 on true and 0 on false, so we change
	   non-zero values to 1 and keep zero as 0 */
	d.val=!!d.val;
	push(d);
}
SMI
or()
{
	Datum d;
	Inst *savepc=pc;
	execute(savepc+2);
	d=pop();
	if(!d.val){
		execute(savepc+INSTTOI(*(savepc)));
		d=pop();
	}
	pc=savepc+INSTTOI(*(savepc+1));
	/* or must return 1 on true and 0 on false, so we change
	   non-zero values to 1 and keep zero as 0 */
	d.val=!!d.val;
	push(d);
}
SMI
not()
{
	Datum d;
	d=pop();
	d.val=(double)(d.val == 0.0);
	push(d);
}
SMI
power()
{
	Datum d1,d2;
	d2=pop();
	d1=pop();
	d1.val=Pow(d1.val,d2.val);
	push(d1);
}
SMI
assign()
{
	Datum d1,d2;
	d1=pop();
	d2=pop();
	switch(d1.sym->type){
	case UNDEF:
		d1.sym->u.val=d2.val;
		d1.sym->type=VAR;
		break;
	case VAR:
		d1.sym->u.val=d2.val;
		break;
	case LOCAL:
		if(d1.sym->u.localptr->p.frame!=fp){
			/* found local from another function. look for the
			   global with the same name */
			/* ->nextdef because global can't be first */
			Local *x=d1.sym->u.localptr->nextdef;
			while(x->nextdef)
				x=x->nextdef;
			x->val=d2.val;
			x->p.type=VAR;
		} else {
			d1.sym->u.localptr->val=d2.val;
		}
		break;	
	default:
		execerror("assignment to non-varible",d1.sym->name);
		break;
	}
	push(d2);
}
SMI
makeconst()
{
	Datum d1,d2;
	d1=pop();
	d2=pop();
	switch(d1.sym->type){
	case UNDEF:
		d1.sym->u.Const=installd(d2.val);
		d1.sym->type=CONST;
		break;
	case CONST:
		d1.sym->u.Const=installd(d2.val);
		break;
	default:
		execerror("constant assignment to non-constant",d1.sym->name);
		break;
	}
	push(d2);
}
SMI
preinc()
{
#ifdef BUG1
	register double *temp=getvar();
	++(*temp);
	pushd(*temp);
#else
	pushd(++(*(getvar())));
#endif
}
SMI
postinc()
{
#ifdef BUG1
	register double *temp=getvar();
	pushd(*temp);
	++(*temp);
#else
	pushd((*(getvar()))++);
#endif
}
SMI
predec()
{
#ifdef BUG1
	register double *temp=getvar();
	--(*temp);
	pushd(*temp);
#else
	pushd(--(*(getvar())));
#endif
}
SMI
postdec()
{
#ifdef BUG1
	register double *temp=getvar();
	pushd(*temp);
	--(*temp);
#else
	pushd((*(getvar()))--);
#endif
}
SMI
addeq()
{
	register double *temp=getvar();
	Datum d;
	d=pop();
#ifdef BUG1
	*temp+=d.val;
	pushd(*temp);
#else
	pushd(*temp+=d.val);
#endif
}
SMI
subeq()
{
	register double *temp=getvar();
	Datum d;
	d=pop();
#ifdef BUG1
	*temp-=d.val;
	pushd(*temp);
#else
	pushd(*temp-=d.val);
#endif
}
SMI
muleq()
{
	register double *temp=getvar();
	Datum d;
	d=pop();
#ifdef BUG1
	*temp*=d.val;
	pushd(*temp);
#else
	pushd(*temp*=d.val);
#endif
}
SMI
diveq()
{
	register double *temp=getvar();
	Datum d;
	d=pop();
	if(d.val==0.0)
		execerror("division by zero", (char *)0);
#ifdef BUG1
	*temp/=d.val;
	pushd(*temp);
#else
	pushd(*temp/=d.val);
#endif
}
SMI
poweq()
{
	register double *temp=getvar();
	Datum d;
	d=pop();
#ifdef BUG1
	*temp=Pow(*temp,d.val);
	pushd(*temp);
#else
	pushd(*temp=Pow(*temp,d.val));
#endif
}
SMI
modeq()
{
	register double *temp=getvar();
	Datum d;
	d=pop();
	if(d.val==0.0)
	execerror("division by zero", (char *)0);
#ifdef BUG1
	*temp=fmod(*temp,d.val);
	pushd(*temp);
#else
	pushd(*temp=fmod(*temp,d.val));
#endif
}
double last;
SMI
print()
{
	Datum d;
	d=pop();
	printf("\t%.*g\n",(int)getval(vpDIGITS), last=d.val);
	fflush(stdout);
}
SMI
prexpr()
{
	Datum d;
	d=pop();
	printf("%.*g",(int)getval(vpDIGITS), d.val);
}
SMI
prstr()
{
	printf("%s", (char *)*pc++);
}
SMI
Chdir()
{
	char *s=(char *)*pc++;
	if(chdir(s)==(-1)) execerror("invalid directory",s);
}
SMI
doflush()
{
	fflush(stdout);
}
SMI
System()
{
	system((char *)*pc++);
}
SMI
Include()
{
	/* part of this code is similar to moreinput() */
	char *oldinfile;
	int oldlineno;
	FILE *oldfin;
	int oldnlstate,oldinteractive;
	jmp_buf oldbegin;

	oldinfile=infile;
	oldlineno=lineno;
	oldfin=fin;
	oldnlstate=nlstate;
	oldinteractive=interactive;
	/* because jmp_buf is an array (at least on a VAX it is an array
	   and I am not sure what it is on other computers), I use memcpy
	   to copy it, not assignment. 
	*/
	memcpy((char*)oldbegin,(char *)begin,sizeof(jmp_buf));

	interactive=0;
	infile=((char *)*pc++);
	if(strcmp(infile,"-")==0){
		fin=stdin;
		infile=0;
		/* this is an interactive hoc if we're taking input from
		   stdin, and stdin is connected to a terminal
		*/
		interactive=isatty(fileno(fin));
#ifndef ALWAYSPRVER
		if(interactive) versioninfo();
#endif
		goto OPENED;
	}
	if(infile[0]=='-'&&infile[1]=='l'){
		char *tmp;
#ifdef NOLIBS
		infile=oldinfile;
		execerror("libraries not available on this system",(char*)0);
#else
#ifndef LIBPREFIX
#define LIBPREFIX "/usr/lib/hoclibs/LIB"
#endif
		tmp=malloc(strlen(infile+2)+strlen(LIBPREFIX)+1);
		tmp[0]='\0';
		strcat(tmp,LIBPREFIX);
		strcat(tmp,infile+2);
		infile=tmp;
#endif
	}
	if((fin=fopen(infile,"r"))==NULL){
		char *saveinfile=infile;
		infile=oldinfile;
		fin=oldfin;
		nlstate=oldnlstate;
		interactive=oldinteractive;
		execerror("can't open",saveinfile);
	}
OPENED:
	lineno=1;
	run();	/* fatal if interrupted between this and the memcpy. */

	if(fin!=stdin)
		fclose(fin);
	
	infile=oldinfile;
	lineno=oldlineno;
	fin=oldfin;
	nlstate=oldnlstate;
	interactive=oldinteractive;
	/* again memcpy */
	memcpy(begin,oldbegin,sizeof(jmp_buf));; /*now it's ok to interrupt*/

	/* put STOP code in beggining of prog, because the call to run changed
	   it, and we want execute who called Include to find a STOP */
	pc=progbase;
	*pc=STOP;
}
SMI
varread()
{
	/* read: read number into variable. return:
		0 on EOF
		1 on success
		-1 on input of other than a string.
	   on error, don't change the value of variable.
	*/
	Datum d;
	int x;
	Symbol *var = (Symbol *)*pc++;
	double rv;		/* value read */
	switch(fscanf(stdin, "%lf", &rv)){
	case EOF:
		d.val = 0.0;
		break;
	case 0:
		warning("non-number read into", var->name);
		while((!isspace(x=getchar()))&&x!=EOF);
		d.val= -1.0;
		break;
	default:
		switch(var->type){
		case UNDEF:
			var->u.val=rv;
			var->type=VAR;
			break;
		case VAR:
			var->u.val=rv;
			break;
		case LOCAL:
			if(var->u.localptr->p.frame!=fp){
				/* found local from another function. look for the
				   global with the same name */
				/* ->nextdef because global can't be first */
				Local *x=var->u.localptr->nextdef;
				while(x->nextdef)
					x=x->nextdef;
				x->val=rv;
				x->p.type=VAR;
			} else {
				var->u.localptr->val=rv;
			}
			break;	
		default:
			execerror("value read into non-varible",var->name);
			break;
		}
	d.val=1.0;
	break;
	}
	push(d);
}
SMI
findtype()
{
	/* findtype: return the type of the item. */
	switch(((Symbol *)*pc++)->type){
	case UNDEF:	pushd(0.); break;
	case VAR:	pushd(1.); break;
	case FUNCTION:	pushd(2.); break;
	case PROCEDURE:	pushd(3.); break;
	case LOCAL:	pushd(4.); break;
	case BLTIN:	pushd(5.); break;
	default:	pushd(6.); break;
	}
}
SMI
Free()
{
	printf("recursion: %d (+%d)\t",fp-&frame[0],&frame[NFRAME-1]-fp);
	printf("stack: %d (+%d)\n",stackp-&stack[0],&stack[NSTACK]-stackp);
}
SMI
exitn()
{
	Datum d;
	d=pop();
	exit((int)((double)d.val));
}
SMI
exit0(){
	exit(0);
}
static void
sortnames(s)
	Symbol *s;
{
	if(s->right)sortnames(s->right);
	if(!(s->name[0]=='_') || allnames)
	switch(s->type){
	case UNDEF:	break;
	case VAR:	fprintf(stderr,"%s = %.15g\n", s->name, s->u.val);
			break;
	case CONST:	fprintf(stderr,"%s = %.15g (constant)\n", s->name,
				s->u.Const->d); break;
	case FUNCTION:	fprintf(stderr,"%s: function\n", s->name); break;
	case PROCEDURE:	fprintf(stderr,"%s: procedure\n", s->name); break;
	case BLTIN:	fprintf(stderr,"%s: builtin function\n", s->name); break;
	case LOCAL:	if(s->u.localptr->p.frame!=fp){
				/* founf local from another function. look for the
				    global with the same name */
				/*->nextdef because global can't be first*/
				Local *x=s->u.localptr->nextdef;
				while(x->nextdef)
					x=x->nextdef;
				if(x->p.type==UNDEF)
					fprintf(stderr,"%s: undefined for this func/proc\n",
						s->name);
				else
					fprintf(stderr,"%s = %.15g (global for this func/proc)\n",
						s->name, x->val);
			} else {
				fprintf(stderr,"%s = %.15g (local for this func/proc)\n",
					s->name, s->u.localptr->val);
			}
			break;
	default:	fprintf(stderr,"%s: keyword\n", s->name); break;
	}
	if(s->left)sortnames(s->left);
}
SMI
printnames()
{
	sortnames(symstart());
}
SMI
printversion()
{
	int i=0;
	fprintf(stderr,"\nNYH HOC, by Brian Kernighan, Rob Pike, and Nadav Har'El.\n");
	fprintf(stderr,"Copyright (C) 1995 AT&T, (C) 1986-1997, 2007 Nadav Har'El.\n");
	while(version_array[i])
		fprintf(stderr,"%s\n",version_array[i++]+4);
	fprintf(stderr,"\n");
}
SMI
popandforget(){
	pop();
}
/****************************************************************************/
/* "Builtins", called by bltin(). These functions must all take one argument
   and return a double.
   More builtins are in math.c.
*/
double
Arg(num)
	double num;
{
	int nargs;
	nargs=(int)num;
	if(!(fp-frame))
		execerror("arg", "used outside definition");
	if(nargs<1)
		execerror(fp->sp->name, "no such argument");
	if(nargs>fp->nargs)
		execerror(fp->sp->name, "not enough arguments");
	return fp->argn[nargs-fp->nargs].val;
}
/****************************************************************************/
