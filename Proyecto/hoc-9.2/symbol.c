#include "hoc.h"
#ifndef MSDOS
#include "y.tab.h"
#else
#include "y.h"
#endif

#ifdef STDC_HEADERS
#include <stdlib.h>
#include <string.h>
#else
char *calloc();
#endif

static Symbol *symlist=0;
static Constant *constlist=0;

Symbol *
symstart()
{
	return symlist;
}
Symbol *
lookup(s)
	char *s;
{
	Symbol *sp;
	int a;
	for(sp=symlist;sp;){
		a=strcmp(sp->name,s);
		if(a==0)return sp;
		if(a<0)sp=sp->left;
		else sp=sp->right;
	}
	return 0;
}

Symbol *
install(s,t,d)
	char *s;
	int t;
	double d;
{
	Symbol **sp;
	int a;
	for(sp= &symlist;*sp;){
		a=strcmp((*sp)->name,s);
		if(a==0)break;
		if(a<0)sp= &(*sp)->left;
		else sp= &(*sp)->right;
	}
	if(*sp==(Symbol *)0){
		*sp=(Symbol *)emalloc(sizeof(Symbol));
		(*sp)->name=emalloc(strlen(s)+1);
		strcpy((*sp)->name,s);
	}
	(*sp)->type=t;
	(*sp)->u.val=d;
	return *sp;
}

Constant *
installd(n)
	double n;
{
	Constant **sp;
	double a;
	for(sp= &constlist;*sp;){
		a=(*sp)->d;
		if(a==n)break;
		if(a<n)sp= &(*sp)->left;
		else sp= &(*sp)->right;
	}
	if(*sp==(Constant *)0){
		*sp=(Constant *)emalloc(sizeof(Constant));
		(*sp)->d=n;
	}
	return *sp;
}

char *
emalloc(n)
	unsigned n;
{
	char *p;

	p=calloc(1,n);
	if(p==0)
		execerror("out of memory", (char *)0);
	return p;
}
