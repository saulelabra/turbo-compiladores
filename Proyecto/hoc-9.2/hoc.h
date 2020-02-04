/* Arbitrary limits used in hoc. Some day these should be removed.
   NSTACK should be replaced by an endstack pointer, with possible
   enlarging realloc of the stack when necessary.
   NFRAME should be the only one remaining a limit (to catch erronous
   infinite recursions), but it too should be possible to reallocate
   on runtime.
*/
#ifndef NSTACK		/* Maximum stack size. The stack is used for keeping */
#define NSTACK 1024	/* function parameters */
#endif
#ifndef NFRAME		/* Maximum frame size. The frame needs one entry for */
#define NFRAME 256      /* each level of recursion */
#endif
#ifndef NPROG		/* Maximum "program" size. This limits the size of */
#define NPROG 2000	/* one statement, or one func/proc definitions. */
#endif

/* Use prototypes like: double add _PROTO((double n1, int n2))
   which work whether or not prototypes are available
*/
#ifdef __STDC__
#define _PROTO(x) x
#else
#define _PROTO(x) ()
#endif

/* Functions used as stack-machine instructions, i.e., added to the program
   using code() during the compilation phase and later executed by execute()
   must all return the same type of value, since execute() cannot know which
   function it calls, and it assumes it knows which type is returned so it
   can ignore it. This type will be called SMI (for "stack machine
   instruction"), and will be typically be defined as void.

   Inst is the type for intructions kept in the "program" (instruction list).
   Each instruction is a pointer to the appropriate function, i.e., it is
   a pointer to a function returning SMI.
*/
typedef void SMI;
typedef SMI (*Inst)();

/* Sometimes we want to put small integers as instructions (e.g, argassign
   and a few other instructions read the next instruction and assumes it to be
   a small integer, and flow control instructions like ifcode put numbers of
   instructions to jump as small integers in the program).
   Some versions of the C compiler, especially on systems where "int" and
   "void *" are not of the same size (e.g., x86_64, where int is 32 bit but
   void * is 64 bit), warn about "cast to pointer from integer of different
   size" if we do casts like (Inst)i. Rather, they expect us to do something
   ugly like (Inst)(pointer_sized_int)i.
   
*/
#ifndef pointer_sized_int
/* if pointer_sized_int is defined, use that. Otherwise, just used "int"
   (which is redundant in the following casts, so will basically do nothing)
 */
#define pointer_sized_int int
#endif
#define ITOINST(i) ((Inst)(pointer_sized_int)(i))
#define INSTTOI(i) ((int)(pointer_sized_int)(i))

typedef struct Local Local;
typedef struct Constant Constant;
typedef struct Symbol {
	char *name;
	short type;
	union {
		double val;	/*VAR*/
		double (*ptr)();/*BLTIN*/
		Inst defn;	/*FUNCTION,PROCEDURE*/
		char *str;	/*STRING*/
		Local *localptr;/*LOCAL*/
		Constant *Const;/*CONST*/
	} u;
	struct Symbol *left;
	struct Symbol *right;
} Symbol;
struct Constant {
	double d;
	struct Constant *left;
	struct Constant *right;
};

typedef union Datum {
	double val;
	Symbol *sym;
} Datum;
typedef struct Frame {
	Symbol *sp;
	Inst *retpc;
	Datum *argn;
	int nargs;
	Local *locals;
} Frame;
struct Local {
	double val;		/* value of local variable */
	Local *nextdef;		/* definition from previous scope of
				   this variable */
	Local *nextlocal;	/* next local variable in this function */
	Symbol *real;		/* pointer to the global structure */
	union {
		Frame *frame;		/* pointer to frame that called
					   mklocal, needed in all the Local
					   structures in the linked list
					   exept the last one */ 
		short type;		/* type: VAR or UNDEF, needed only
				   	   for the last Local structure
				   	   in the linked list */
	} p;
};

/* hoc.y */
extern void execerror _PROTO((char *s, char *t));
extern void warning _PROTO((char *s, char *t));
extern void init _PROTO((void));
extern void run _PROTO((void));
extern void versioninfo _PROTO((void));
/* code.c */
extern void initcode _PROTO((void));
extern void define _PROTO((Symbol *sp));
extern void Line _PROTO((Inst lineinfile, Inst filename));
extern Inst *code _PROTO((Inst f));
extern void move _PROTO((Inst *p, int n));
extern void execute _PROTO((Inst *p));
/* math.c */
extern double Pow _PROTO((double x, double y));
/* symbol.c */
extern Symbol *symstart _PROTO((void));
extern Symbol *lookup _PROTO((char *s));
extern Symbol *install _PROTO((char *s,int t, double d));
extern Constant *installd _PROTO((double n));
extern char *emalloc _PROTO((unsigned n));


/* Pointers to the following functions can be put in the "program", by code()
   to be executed, i.e., this is the stack-machine instruction list.
*/
#define STOP (Inst)0
extern SMI eval(),add(),sub(),mul(),Div(),negate(),power(),mod();
extern SMI assign(),bltin(),varpush(),constpush(),print(),varread(),postdec();
extern SMI prexpr(),prstr(),System(),Mod(),poweq(),argpoweq();
extern SMI gt(),lt(),eq(),ge(),le(),ne(),and(),or(),not(),forcode(),preinc();
extern SMI ifcode(),whilecode(),call(),arg(),argassign(),printnames(),predec();
extern SMI funcret(),procret(),Break(),Breakn(),exitn(),doflush(),postinc();
extern SMI cont(),contn(),argcnt(),Free(),conditional(),makelocal();
extern SMI argpredec(),argpostdec(),argpreinc(),argpostinc(),addeq(),subeq();
extern SMI muleq(),diveq(),argaddeq(),argsubeq(),argmuleq(),argdiveq(),Set();
extern SMI approxeq(),notapproxeq(),modeq(),argmodeq(),Include(),findtype();
extern SMI makeconst(), printversion(),Abort(),Doeof(),Chdir(),popandforget();
extern SMI exit0();
/* End of "program code" functions. */

/* Builtins. Builtins are all functions taking one double argument and
   returning a double, and they are defined in math.c (except Arg() defined
   in code.c). They are called by the state machine instruction bltin().
   The pointers to the builtin functions are put in the symbol table in BLTIN
   type variables, in init.c.
*/
typedef double Builtin _PROTO((double));
typedef double (*Builtinp) _PROTO((double));
extern Builtin Log,Log10,Sqrt,Exp,integer,frac,rnd,randomize,Time,Logamma,Sinh;
extern Builtin Cosh,Tanh,Tan,Asin,Acos,Gamma,Sec,Cosec,Cot,Arg;
/* End of "builtin" functions. */

/* External variables used between files. These should be kept to a minimum.
*/
/* hoc.y */
extern int indef, lineno, nlstate, interactive;
extern char *infile;
extern Inst deffunc[], defproc[];
/* TODO: 'fin' and 'begin' should also be defined (they are externed in
   code.c) but that requires inclusion of stdio.h and setjmp.h)
*/
/* code.c */
extern Inst *progp,*progbase,prog[];
extern Frame frame[],*fp;
/* init.c */
extern Symbol *vpERROR, *vpDIGITS;
/* version.c */
extern char *version_array[];
/* End of external variables */

extern int *getmem _PROTO((int i));
extern void freemem _PROTO((int *p, int i));
#define NEWLOCAL() ((Local *)getmem(sizeof(Local)/sizeof(int)))
#define FREELOCAL(p) freemem((int*)p,sizeof(Local)/sizeof(int))
#define S_CHANGED 0
#define S_IGNOREUNDEF 1
#define S_TRACECALLS 2
#define S_ALLNAMES 5
#define S_ALL 3
#define S_DEFAULT 4
