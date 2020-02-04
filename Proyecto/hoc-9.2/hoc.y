%{
#include <stdio.h>
#include <ctype.h>
#ifdef STDC_HEADERS
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#else
char *malloc();
char *strchr();
#endif

#include "hoc.h"

#define code2(c1,c2)	code(c1);code(c2)
#define code3(c1,c2,c3)	code(c1);code(c2);code(c3)
#define code4(c1,c2,c3,c4)	code(c1);code(c2);code(c3);code(c4)
#if YYDEBUG
extern int yydebug;
#endif

static Constant zero;	/* zero.d=0 because it's statically allocated (which
                           has nothing to do with the "static" keyword) */

/* Default definitions of an empty function or procedure */
Inst deffunc[] = {	/* a function that does nothing but returns 0 */
	constpush,
	(Inst)&zero,
	funcret,
	STOP
};
Inst defproc[] = {	/* procedure that does nothing */
	procret,
	STOP
};

static char *atstring="";
int indef;
static int showprompt;	/* what the next yylex should show:
				0: no prompt, 1: new statement prompt
			*/

/* functions which will be defined below */
static void defnonly _PROTO((char *s));
static int skipc _PROTO((void));
static int backslash _PROTO((int c));
static char lookahead _PROTO((void));
static RETSIGTYPE fpecatch _PROTO((int sig));
static RETSIGTYPE intcatch _PROTO((int sig));
static int moreinput _PROTO((void));

static int yylex();
static void yyerror();
%}
%union {
	Symbol	*sym;	/* symbol table pointer */
	Inst	*inst;	/* machine instruction */
	int	narg;	/* number of arguments */
	Constant *Const;/* constant number */
}
%token '(' ')' ';' '#' '{' '}' ','
%token <sym>	EXIT BREAK CONT DEBUG LEVEL MOD PRCALLS IGNOREUNDEF LOCALCMD
%token <sym>	STRING PRINT VAR BLTIN UNDEF WHILE IF ELSE FOR PRNAMES INCLUDE
%token <sym> 	FUNCTION PROCEDURE RETURN FUNC PROC READ SYSTEM LOCAL SET
%token <sym>	CONSTCMD CONST VERSION TYPE CALLFUNC CALLPROC ABORT DOEOF CHDIR
%token <narg> 	ARG ARGCNT
%token <Const>	NUMBER
%type <inst>	expr stmt asgn prlist stmtlist
%type <inst>	cond while if begin end for fsc
%type <inst>	opt_expr opt_stmt
%type <sym>	procname constname identifier
%type <narg>	opt_arglist opt_arglist1 arglist formals
%right	'=' ADDEQ SUBEQ MULEQ DIVEQ POWEQ REMEQ
%right	'?' '|'
%left	OR
%left 	AND
%left	GT GE LT LE EQ NE APPROXEQ NOTAPPROXEQ
%left	'+' '-'
%left	'*' '/' '%' MOD
%left	UNARYMINUS NOT INCR DECR
%right	'^'
%%
/* The showprompt and special "newp" instead of newl below is all done
   to keep a variable 'showprompt' which is 1 if and only if we
   are going a process a new main statement.
   Together with yylex's nlstate, we can know if we should output a prompt.
*/
list:	  /* nothing */		{showprompt=1;} /* on starting yyparse */
	| list newp
	| list defn newp
	| list asgn newp	{code2(popandforget,STOP);return 1;}
	| list stmt newp	{code(STOP);return 1;}
	| list expr newp	{code2(print,STOP);return 1;}
	| list INCLUDE STRING newp 	{code3(Include,(Inst)$3,STOP);return 1;}
	/* TODO: think if newp should be replaced by '\n', or yyerror
	   should do execerror, in order to not parse what is after
	   an error and a ';' (currently "@;2" gives a syntax error for
	   the @, but the 2 is then executed)
	*/
	| list error newp	{yyerrok;}
	;
newp:	  newl			{showprompt=1;}
	;
newl:	  '\n'
	| ';'
	;
asgn:	  VAR '=' expr		{code3(varpush,(Inst)$1,assign);$$=$3;}
	| VAR ADDEQ expr	{code3(varpush,(Inst)$1,addeq);$$=$3;}
	| VAR SUBEQ expr	{code3(varpush,(Inst)$1,subeq);$$=$3;}
	| VAR MULEQ expr	{code3(varpush,(Inst)$1,muleq);$$=$3;}
	| VAR DIVEQ expr	{code3(varpush,(Inst)$1,diveq);$$=$3;}
	| VAR POWEQ expr	{code3(varpush,(Inst)$1,poweq);$$=$3;}
	| VAR REMEQ expr	{code3(varpush,(Inst)$1,modeq);$$=$3;}
	| INCR VAR		{$$=code3(varpush,(Inst)$2,preinc);}
	| VAR INCR		{$$=code3(varpush,(Inst)$1,postinc);}
	| DECR VAR		{$$=code3(varpush,(Inst)$2,predec);}
	| VAR DECR		{$$=code3(varpush,(Inst)$1,postdec);}
	| ARG '=' expr
		{defnonly("$");
		code2(argassign,ITOINST($1));$$=$3;}
	| ARG ADDEQ expr	{defnonly("$");code2(argaddeq,ITOINST($1));$$=$3;}
	| ARG SUBEQ expr	{defnonly("$");code2(argsubeq,ITOINST($1));$$=$3;}
	| ARG MULEQ expr	{defnonly("$");code2(argmuleq,ITOINST($1));$$=$3;}
	| ARG DIVEQ expr	{defnonly("$");code2(argdiveq,ITOINST($1));$$=$3;}
	| ARG POWEQ expr	{defnonly("$");code2(argpoweq,ITOINST($1));$$=$3;}
	| ARG REMEQ expr	{defnonly("$");code2(argmodeq,ITOINST($1));$$=$3;}
	| INCR ARG		{defnonly("$");$$=code2(argpreinc,ITOINST($2));}
	| ARG INCR		{defnonly("$");$$=code2(argpostinc,ITOINST($1));}
	| DECR ARG		{defnonly("$");$$=code2(argpredec,ITOINST($2));}
	| ARG DECR		{defnonly("$");$$=code2(argpostdec,ITOINST($1));}
	| LOCALCMD VAR '=' expr	{defnonly("local");
				code3(varpush,(Inst)$2,makelocal);$$=$4;}
	| LOCALCMD VAR		{defnonly("local");
				$$=code2(constpush,(Inst)&zero);
				code3(varpush,(Inst)$2,makelocal);}
	| CONSTCMD constname '=' expr	{code3(varpush,(Inst)$2,makeconst);$$=$4;}
	;
stmt:	  expr			{code(popandforget);}
	| EXIT opt_expr		{if($$=$2)code(exitn);else $$=code(exit0);}
	| ABORT			{$$=code(Abort);}
	| DOEOF			{$$=code(Doeof);}
	| CHDIR STRING		{$$=code2(Chdir,(Inst)$2);}
	| SET			{$$=code2(Set,(Inst)0);}
	| SET STRING		{int sign=1;char *save2=(char *)$2;
				if(((char *)$2)[0]=='n' && ((char *)$2)[1]=='o'){
					sign= -1;
					$2=(Symbol *) (((char *)$2)+2);
				}
				if(!strcmp((char *)$2,"ignoreundef")){
					$$=code2(Set,ITOINST(sign*S_IGNOREUNDEF));
					free(save2);
				} else if(!strcmp((char *)$2,"tracecalls")){
					$$=code2(Set,ITOINST(sign*S_TRACECALLS));
					free(save2);
				} else if(!strcmp((char *)$2,"allnames")){
					$$=code2(Set,ITOINST(sign*S_ALLNAMES));
					free(save2);
				}
#if YYDEBUG
				else if(!strncmp((char *)$2,"debug",5)){
					if((*(((char *)$2)+5))=='\0'&&sign!=-1)
						goto SETERROR;
					if(sign==-1){
						if((*(((char*)$2)+5))!='\0')
							goto SETERROR;
						yydebug=0;
					} else {
						yydebug=atoi(((char *)$2)+5);
						free(save2);
					}
					$$=progp;
				}
#endif
				else if(!strcmp((char *)$2,"all")){
					if(sign==-1) goto SETERROR;
					$$=code2(Set,(Inst)S_ALL);
					free(save2);
				} else if(!strcmp((char *)$2,"default")){
					if(sign==-1) goto SETERROR;
					$$=code2(Set,(Inst)S_DEFAULT);
					free(save2);
				} else if(!strncmp((char *)$2,"@=",2)){
					if(sign==-1) goto SETERROR;
					atstring=(char *)$2 + 2;
					$$=progp;
				} else {
SETERROR:				free(save2);execerror("bad set option",(char *)0);
				}}
	| LEVEL			{$$=code(Free);}
	| BREAK opt_expr	{if($$=$2)code(Breakn);else $$=code(Break);}
	| CONT opt_expr		{if($$=$2)code(contn);else $$=code(cont);}
	| PRNAMES		{$$=code(printnames);}
	| VERSION		{$$=code(printversion);}
	| RETURN opt_expr	{defnonly("return");if($$=$2)code(funcret);
				else $$=code(procret);}
	| PROCEDURE begin
		{$$=$2;
		code4(call,(Inst)$1,(Inst)0,(Inst)PROCEDURE);}
	| PROCEDURE begin '(' opt_arglist ')'
		{$$=$2;
		code4(call,(Inst)$1,ITOINST($4),(Inst)PROCEDURE);}
	| CALLPROC begin '(' identifier opt_arglist1 ')'
		{$$=$2;
		code4(call,(Inst)$4,ITOINST($5),(Inst)PROCEDURE);}
	| PRINT prlist 		{$$=$2;code(doflush);}
	| SYSTEM STRING		{$$=code2(System,(Inst)$2);}
	| '#' NUMBER STRING	{Line((Inst)$2,(Inst)$3);$$=progp;}
	| while cond stmt end	{
		($1)[1] = (Inst)($3-($1+1));	/* body of loop */
		($1)[2] = (Inst)($4-($1+1));}	/* end, if cond fails */
	| if cond stmt end {		/* else-less if */
		($1)[1] = (Inst)($3-($1+1));	/* thenpart */
		($1)[2]	= (Inst)0;		/* no elsepart */
		($1)[3] = (Inst)($4-($1+1));}	/* end, if cond fails */
	| if cond stmt end ELSE stmt end {	/* if with else */
		($1)[1] = (Inst)($3-($1+1));	/* thenpart */
		($1)[2] = (Inst)($6-($1+1));	/* elsepart */
		($1)[3] = (Inst)($7-($1+1));}	/* end, if cond fails */
	| for '(' opt_stmt fsc opt_expr fsc opt_stmt frp stmt end{
		if($3) ($1)[1]=(Inst)($3-($1+1)); else ($1)[1]=(Inst)0;/*1st*/
		if($5) ($1)[2]=(Inst)($5-($1+1)); else ($1)[2]=(Inst)0;/*2nd*/
		if($7) ($1)[3]=(Inst)($7-($1+1)); else ($1)[3]=(Inst)0;/*3rd*/
		($1)[4]=(Inst)($9-($1+1));/*stmt*/
		($1)[5]=(Inst)($10-($1+1));/*end*/
		}
	| '{' stmtlist '}'	{$$=$2;}
	;
fsc:	  ';'			{code(STOP);	/*for's semi-colon*/}
	;
frp:	  ')'			{code(STOP);	/*for's right parenthesis*/}
	;
cond:	  '(' expr ')'		{code(STOP);$$=$2;}
	;
while:	  WHILE			{$$=code3(whilecode,STOP,STOP);}
	;
if:	  IF			{$$=code(ifcode);code3(STOP,STOP,STOP);}
	;
for:	  FOR			{$$=code3(forcode,STOP,STOP);
				code3(STOP,STOP,STOP);}
	;
begin:	  /*nothing*/		{$$=progp;}
	;
end:	  /*nothing*/		{code(STOP);$$=progp;}
	;
stmtlist: /*nothing*/		{$$=progp;}
	| stmt
	| stmtlist newl
	| stmtlist newl stmt
	;
opt_expr: /*nothing*/		{$$=0;}
	| expr
	;
opt_stmt: /*nothing*/		{$$=0;}
	| stmt
	;
expr:	  NUMBER		{$$=code2(constpush,(Inst)$1);}
	| CONST			{$$=code2(constpush,(Inst)$1->u.Const);}
	| VAR			{$$=code3(varpush,(Inst)$1,eval);}
	| ARG			{defnonly("$");
				$$=code2(arg,ITOINST($1));}
	| ARGCNT		{defnonly("$");
				$$=code(argcnt);}
	| asgn
	| FUNCTION begin
		{$$=$2; code4(call,(Inst)$1,(Inst)0,(Inst)FUNCTION);}
	| FUNCTION begin '(' opt_arglist ')'
				{$$=$2;
				code4(call,(Inst)$1,ITOINST($4),(Inst)FUNCTION);}
	| CALLFUNC begin '(' identifier opt_arglist1 ')'
				{$$=$2;
				code4(call,(Inst)$4,ITOINST($5),(Inst)FUNCTION);}
	| READ '(' VAR ')'	{$$=code2(varread,(Inst)$3);}
	| BLTIN '(' expr ')'	{$$=$3;
				code2(bltin,(Inst)$1->u.ptr);}
	| '(' expr ')'		{$$=$2;}
	| expr '+' expr		{code(add);}
	| expr '-' expr		{code(sub);}
	| expr '*' expr		{code(mul);}
	| expr '/' expr		{code(Div);}
	| expr '%' expr		{code(mod);}
	| expr MOD expr		{code(Mod);}
	| expr '^' expr		{code(power);}
	| '-' expr %prec UNARYMINUS	{$$=$2;code(negate);}
	| expr GT expr		{code(gt);}
	| expr GE expr		{code(ge);}
	| expr LT expr		{code(lt);}
	| expr LE expr		{code(le);}
	| expr EQ expr		{code(eq);}
	| expr APPROXEQ expr	{code(approxeq);}
	| expr NOTAPPROXEQ expr	{code(notapproxeq);}
	| expr NE expr		{code(ne);}
	| expr AND expr		{
				move($$=$1,3);
				move($3+3,1);
				code(STOP);
				($1)[0]=(Inst)and;
				($1)[1]=(Inst)(3+$3-$1);
				($1)[2]=(Inst)(progp-$1-1);
				($3)[3]=STOP;
				}
	| expr OR expr		{
				move($$=$1,3);
				move($3+3,1);
				code(STOP);
				($1)[0]=(Inst)or;
				($1)[1]=(Inst)(3+$3-$1);
				($1)[2]=(Inst)(progp-$1-1);
				($3)[3]=STOP;
				}
	| NOT expr		{$$=$2;code(not);}
	| expr '?' expr '|' expr {
				move($$=$1,4);
				move($3+4,1);
				move($5+5,1);
				code(STOP);
				($1)[0]=(Inst)conditional;
				($1)[1]=(Inst)(4+$3-$1);
				($1)[2]=(Inst)(5+$5-$1);
				($1)[3]=(Inst)(progp-$1-1);
				($3)[4]=STOP;
				($5)[5]=STOP;
				}
	| TYPE '(' identifier ')'	{$$=code2(findtype,(Inst)$3);}
	;
prlist:	  expr			{code(prexpr);}
	| STRING		{$$=code2(prstr,(Inst)$1);}
	| prlist ',' expr	{code(prexpr);}
	| prlist ',' STRING	{code2(prstr,(Inst)$3);}
	;
defn:	  FUNC procname		{if(!$2->u.defn)$2->u.defn=(Inst)deffunc;
				$2->type=FUNCTION;indef=1;}
		'(' opt_formals ')' stmt  {code(procret);define($2);indef=0;}
	| PROC procname		{if(!$2->u.defn)$2->u.defn=(Inst)defproc;
				$2->type=PROCEDURE;indef=1;}
		'(' opt_formals ')' stmt  {code(procret);define($2);indef=0;}
	;
procname: VAR			{if($1->type==VAR)
					execerror("attempt to make func/proc with a variable name",$1->name);}
	| FUNCTION
	| PROCEDURE
	;

/* Hoc traditionally supported numbered function arguments ($1, $2, etc.).
   Adding support for named arguments ("formals") is deceptively easy: When we
   see func f(a,b){ ... }, we simply have to start the function's code with
   the code for: local a=$1; local b=$2. And this is what we do here:
*/
opt_formals: /* nothing */
	| formals
	;
formals:  VAR			{ $$=1;
		code2(arg, ITOINST($$));
		code2(varpush,(Inst)$1);
		code2(makelocal, popandforget); }
	| formals ',' VAR	{ $$=$1+1;
		code2(arg, ITOINST($$));
		code2(varpush, (Inst)$3);
		code2(makelocal, popandforget); }
	;

constname: VAR			{if($1->type==VAR)
					execerror("attempt to make constant with a variable name",$1->name);}
	| CONST
	;
opt_arglist:  /*nothing*/	{$$=0;}
	| arglist		{$$=$1;}
	;
opt_arglist1:  /*nothing*/	{$$=0;}
	| ',' arglist		{$$=$2;}
	;
arglist:  expr			{$$=1;}
	| arglist ',' expr	{$$=$1+1;}
	;
identifier:	EXIT|BREAK|CONT|DEBUG|LEVEL|LOCALCMD|PRINT|VAR|BLTIN|UNDEF
		|WHILE|IF|ELSE|FOR|PRNAMES|INCLUDE|FUNCTION|PROCEDURE|RETURN
		|FUNC|PROC|READ|SYSTEM|LOCAL|SET|CONSTCMD|CONST|VERSION|TYPE
		|CALLFUNC|CALLPROC|ABORT|DOEOF|CHDIR;
%%

#include <signal.h>
#include <setjmp.h>
#ifdef HAVE_SIGLONGJMP
sigjmp_buf begin;
#else
jmp_buf begin;
#endif

char **gargv;
int gargc;
char *progname;

int lineno=1;
char *infile;
FILE *fin;
int c,nlstate=1;
static int endfile=0;
int interactive;

static char *SCCSID="@(#)NYH HOC - by Brian Kernighan, Rob Pike, Nadav Har'El";

static int
yylex()
{
	/* On interactive sessions (read file is stdin, and it is connected
	   to a terminal, we show a prompt on new lines.
	   If this is the first lexical symbol in a complete statement,
	   showprompt is still 1 (see yacc code above) and we show a "hoc>"
	   prompt. Otherwise, we output a tab if currently defining a func
	   or proc, or output a ">" otherwise (e.g., in the middle of a
	   stmtlist).
	*/
	if(interactive && nlstate){
		if(showprompt) fprintf(stderr,"hoc> ");
		else if(indef) fprintf(stderr,"\t");
		else fprintf(stderr,"> ");
		showprompt=0;
	}

BEGYYLEX:
#ifdef MSDOS
	/* if in MSDOS there may be junk cr's and ^Z's (eof) */
	while((c=getc(fin))==' '||c=='\t'||c=='\r'||c=='\032')nlstate=0;
#else
	/* there is no need to set nlstate=0 for each and every space character,
	   but we don't care since this such a fast operation
	*/
	while((c=getc(fin))==' '||c=='\t')nlstate=0;
#endif
		;
	if(c==EOF)
		return 0;
	if ((c == '/') && lookahead() == '*'){
		getc(fin); /*throw out the * */
		if(!skipc()){nlstate=0; return 0;}
		nlstate=0;
		goto BEGYYLEX;
	}
	/* If we see a backward slash followed by a \n or \r then
	   we discard the backward slash and all \n or \r's that follow
	   it. Note that \ can not be used to continue, for example, an
	   identifier name on the next line - it can only be used between
	   two different lexical symbols.
	*/
	if(c == '\\'){
		int z;
		if((z=lookahead())=='\r' || z=='\n'){
			z=getc(fin);
			while(z=='\r'||z=='\n'){
				if(z=='\n'){
					lineno++;
					nlstate=1;
				}
				z=getc(fin);
			}
			if(z==EOF) return 0;
			else ungetc(z,fin);
			goto BEGYYLEX;
		}
	}
		
	/* support for nroff commands inside a hoc file is there for historic
	   reasons. at least when in interactive mode we don't have to support
	   it.
	*/
	if(c=='.' && nlstate && !interactive){
		while((c=getc(fin))!='\n'&&c!=EOF)
			;
		lineno++;
		goto BEGYYLEX;
	}
	if( (c=='.' && isdigit(lookahead())) || isdigit(c)){
		double d;
		ungetc(c,fin);
		/* the condition above should guarantee that the following
		   fscanf succeed. However, in the future I should probably
		   check that it indeed succeeds and else print a sanity
		   check error otherwise.
		*/
		fscanf(fin,"%lf",&d);
		yylval.Const=installd(d);
		nlstate=0;return NUMBER;
	}
	if(c=='_'){
		int z;
		if((z=lookahead())!='_'&&!isalnum(z)){
			extern double last;
			yylval.sym=install("_",VAR,last);
			nlstate=0;return VAR;
		}
	}
	if(isalpha(c)||c=='_'|| (c=='@'&&(lookahead()=='_'||isalnum(lookahead()))) ){
		Symbol *s;
		char sbuf[100], *p = sbuf;
		if(c=='@'){
			int i;
			for(i=0;atstring[i];i++){
				if(p>=sbuf+sizeof(sbuf)-1){
					*p='\0';
					execerror("@ string too long", sbuf);
				}
				*p++=atstring[i];
			}
			c=getc(fin);
		}
		do {
			if (p>=sbuf+sizeof(sbuf)-1){
				*p = '\0';
				execerror("name too long", sbuf);
			}
			*p++=c;
		} while ((c=getc(fin))!=EOF&&(isalnum(c)||c=='_'));
		ungetc(c,fin);
		*p='\0';
		if((s=lookup(sbuf))==0)
			s=install(sbuf,UNDEF,0.0);
		yylval.sym=s;
		nlstate=0;return s->type==UNDEF?VAR:s->type;
	}
	if(c=='$'){
		int n=0;
		c=getc(fin);
		if(c=='#'){
			nlstate=0;return ARGCNT;
		} else ungetc(c,fin);
		while (isdigit(c=getc(fin)))
			n=10*n+c-'0';
		ungetc(c,fin);
		/* $0 is invalid. also, if n is large enough it may even
		   become negative (since n is a twos-complement integer),
		   and that is invalid too.
		*/
		if (n<=0)
			execerror("strange $...",(char *)0);
		yylval.narg=n;
		nlstate=0;return ARG;
	}
	if(c=='"'){
		char sbuf[100],*p;
		for(p=sbuf;(c=getc(fin)) != '"'; p++){
			if(c=='\n'||c==EOF)
				execerror("missing quote", (char *)0);
			if(p>=sbuf+sizeof(sbuf)-1){
				*p='\0';
				execerror("string too long", sbuf);
			}
			*p=backslash(c);
		}
		*p=0;
		yylval.sym=(Symbol *)emalloc(strlen(sbuf)+1);
		strcpy((char*)yylval.sym,sbuf);
		nlstate=0;return STRING;
	}
	switch(c){
	case '>':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return GE;
			case EOF:
				return GT;
			default:
				ungetc(c,fin);
				return GT;
			}
	case '<':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return LE;
			case EOF:
				return LT;
			default:
				ungetc(c,fin);
				return LT;
			}
	case '=':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return EQ;
			case EOF:
				return '=';
			default:
				ungetc(c,fin);
				return '=';
			}
	case '!':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return NE;
			case '~':
				return NOTAPPROXEQ;
			case EOF:
				return NOT;
			default:
				ungetc(c,fin);
				return NOT;
			}
	case '|':	nlstate=0;
			switch(c=getc(fin)){
			case '|':
				return OR;
			case EOF:
				return '|';
			default:
				ungetc(c,fin);
				return '|';
			}
	case '&':	nlstate=0;
			switch(c=getc(fin)){
			case '&':
				return AND;
			case EOF:
				return '&';
			default:
				ungetc(c,fin);
				return '&';
			}
	case '+':	nlstate=0;
			switch(c=getc(fin)){
			case '+':
				return INCR;
			case '=':
				return ADDEQ;
			case EOF:
				return '+';
			default:
				ungetc(c,fin);
				return '+';
			}
	case '-':	nlstate=0;
			switch(c=getc(fin)){
			case '-':
				return DECR;
			case '=':
				return SUBEQ;
			case EOF:
				return '-';
			default:
				ungetc(c,fin);
				return '-';
			}
	case '*':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return MULEQ;
			case EOF:
				return '*';
			default:
				ungetc(c,fin);
				return '*';
			}
	case '/':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return DIVEQ;
			case EOF:
				return '/';
			default:
				ungetc(c,fin);
				return '/';
			}
	case '^':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return POWEQ;
			case EOF:
				return '^';
			default:
				ungetc(c,fin);
				return '^';
			}
	case '~':	nlstate=0;
			switch(c=getc(fin)){
			case '~':
				return APPROXEQ;
			case EOF:
				return '~';
			default:
				ungetc(c,fin);
				return '~';
			}
	case '%':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return REMEQ;
			case EOF:
				return '%';
			default:
				ungetc(c,fin);
				return '%';
			}
	case '\n':	nlstate=1;lineno++;return '\n';
	default:	nlstate=0;return c;
	}
}
static int
backslash(c)
	int c;
{
	static char transtab[]="b\bf\fn\nr\rt\t";
	if(c!='\\')
		return c;
	c=getc(fin);
	if(c>='0' && c<='7'){
		int tmp;
		ungetc(c,fin);
		fscanf(fin,"%3o",&tmp);
		return tmp;
	}
	if(islower(c)&&strchr(transtab,c))
		return strchr(transtab,c)[1];
	return c;
}

static void
defnonly(s)
	char *s;
{
	if(!indef)
		execerror(s,"used outside definition");
}

static void
#ifdef RESEARCH
yyerror(s,t)
	char *s, *t;
#else
yyerror(s)
	char *s;
#endif
{
	initcode();
	*progbase=STOP;
#ifndef RESEARCH
	warning(s,(char *)0);
#else
	fprintf(stderr,"%s: ",progname);
	if(infile)
		fprintf(stderr, "%s: ", infile);
	fprintf(stderr, "%d: ", lineno);
	fprintf(stderr,s,t);
#endif
}
void
execerror(s,t)
	char *s,*t;
{
	Frame *efp;
	for(efp=fp;efp>frame;efp--){
		if(efp->locals){
			/* free all local variables of current function */
			/* same code as in ret() */
			Local *tmp=efp->locals, *tmp1;
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
	}
	if(s){	/* regular call */
		warning(s,t);
	} else { /* call by 'eof' */
		endfile=1;
	}
	fseek(fin,0L,2);
#ifdef HAVE_SIGLONGJMP
	siglongjmp(begin, 0);
#else
	longjmp(begin,0);
#endif

}
/* Signal handlers. RETSIGTYPE, defined by configure, is usually void. */
/* Actually, the signal handler normally has an integer parameter, but
   we ignore it.
*/
static RETSIGTYPE
fpecatch(sig)
{
	execerror("floating point exception",(char *)0);
}

static RETSIGTYPE
intcatch(sig)
{
	execerror("interruped",(char *)0);
}
	
int
main(argc,argv)
	char *argv[];
{
#ifdef ALWAYSPRVER
	/* If ALWAYSPRVER, we show the version information every time hoc
	   runs. If it is not defined (the default), we show version
	   information only in interactive hoc sessions.
	*/
	versioninfo();
#endif
	progname=argv[0];
	if(argc==1){
		static char *stdinonly[]={ "-" };

		gargv=stdinonly;
		gargc=1;
	} else {
		gargv=argv+1;
		gargc=argc-1;
	}
	init();
	while(moreinput())
		run();
	/*nalloc_memory_show_fp(stdout);*/
	exit(0);
}
static int
moreinput()
{
MOREINPUT:
	if(gargc--<=0)
		return 0;
	if(fin&&fin!=stdin)
		fclose(fin);
	infile= *gargv++;
	lineno=1;
	interactive=0;
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
		return 1;
	}
	if(infile[0]=='-'&&infile[1]=='l'){
		char *tmp;
#ifdef NOLIBS
		fprintf(stderr,"%s: libraries not available on this system\n",progname);
		goto MOREINPUT;
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
		fprintf(stderr,"%s: can't open %s\n",progname,infile);
		goto MOREINPUT;
	}
	return 1;
}
void
run()
{
#ifdef HAVE_SIGLONGJMP
	/* In some new systems (like Linux), calling longjmp() from a signal
	   handler (like we do, in fpecatch and intcatch) has a problem: it
	   leaves the caught signal blocked, like it was inside the signal
	   handler! sigsetjmp() and siglongjmp() solve this problem, by also
	   saving and restoring the signal mask.
	*/
	sigsetjmp(begin,1);
#else
	setjmp(begin);
#endif
	if(endfile){	/* if 'eof' was called */
		endfile=0;
		return;
	}
	nlstate=1;
	signal(SIGFPE,fpecatch);
	signal(SIGINT,intcatch);
	for(initcode();yyparse();initcode())
		execute(progbase);
}
void
warning(s,t)
	char *s,*t;
{
	fprintf(stderr,"%s: %s",progname,s);
	if(t)
		fprintf(stderr, " %s",t);
	if(infile)
		fprintf(stderr, " in %s", infile);
	fprintf(stderr, " near line %d\n", lineno);
}

static int
skipc()
{
	/* this function RECURSIVELY skips all characters until a * / is matched */
	char z; /* current character read */
	while(1){
		z=getc(fin);
		if((z=='/')&&(lookahead()=='*')){
			/* recursive skipping of imbedded comments*/
			getc(fin); /* throw out the * */
			if(!skipc())
				return 0;
			continue;
		}
		if((z=='*')&&(lookahead()=='/')){ /* end of comment */
			z=getc(fin); /* throw out the /  */
			return 1;
		}
		if (z=='\n')
			++lineno;
		if (z==EOF)
			return 0;
	}
}
static char
lookahead()
{
	int z;
	z=getc(fin);
	if(z==EOF)
		return 0;
	ungetc(z,fin);
	return((char)z);
}

/* versioninfo() shows version information suitable to be displayed when
   hoc starts running.
   Above, if ALWAYSPRVER, we show the version information every time hoc
   runs. If it is not defined (which is the default), we show version
   information only in interactive hoc sessions.
*/
void versioninfo(){
	fprintf(stderr,"Welcome to the NYH HOC interpreter.\n");
	fprintf(stderr,"By Brian Kernighan and Rob Pike 1984, Nadav Har'El 1986-1997.\n\n");
/*	fprintf(stderr,"%s, %s.\n\n",
  version_array[0]+4,version_array[1]+4);*/
}
