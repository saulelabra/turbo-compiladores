#include "hoc.h"
#include "y.tab.h"

#define NSTACK 256
static Datum stack[NSTACK]; /* the stack */
static Datum *stackp; /* next free spot on the stack */

#define NPROG 2000
Inst prog[NPROG]; /* the machine */
Inst *progp; /* next free spot for code generation */
Inst *pc; /* program counter during execution */

initcode(){ /* Initialize for code generation */
    stackp = stack;
    progp = prog;
}

push(d) /* push d onto stack */
    Datum d;
{
    if(stackp >= &stack[NSTACK])
        execerror("stack overflow", (char *) 0);
    *stackp++ = d;
}

Datum pop() /* pop and return from the stack */
{
    if(stackp <= stack)
        execerror("stack underflow", (char *) 0);
    return *--stackp;
}

Inst *code(f) /* Install one instruction or operand */
    Inst f;
{
    Inst *oprogp = progp;
    if(progp >= &prog[NPROG])
        execerror("program too big", (char *) 0);
    *progp++ = f;
    return oprogp;
}

execute(p) /* run the machine */
    Inst *p;
{
    for(pc = p; *pc != STOP;)
        (*(*pc++))();
}

constpush() /* push constant onto stack */
{
    Datum d;
    d.val = ((Symbol *)* pc++)->u.val;
    push(d);
}

varpush() /* push variable onto stack  */
{
    Datum d;
    d.sym = (Symbol *)(*pc++);
    push(d);
}

prexpr()
{
    Datum d;
    d = pop();
    printf("%.8g\n", d.val);
}

add()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val += d2.val;
    push(d1);
}

sub()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val -= d2.val;
    push(d1);
}

mul()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val *= d2.val;
    push(d1);
}

div()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val /= d2.val;
    push(d1);
}

negate()
{
    Datum d1;
    d1 = pop();
    d1.val = -(d1.val);
    push(d1);
}

power()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = pow(d1.val, d2.val);
    push(d1);
}

eval()
{
    Datum d;
    d = pop();
    if(d.sym->type == UNDEF)
        execerror("undefined variable", d.sym->name);
    d.val = d.sym->u.val;
    push(d);
}

assign()
{
    Datum d1, d2;
    d1 = pop();
    d2 = pop();
    if( d1.sym->type != VAR && d1.sym->type != UNDEF)
        execerror("assignment to no-variable", d1.sym->name);
    d1.sym->u.val = d2.val;
    d1.sym->type = VAR;
    push(d2);
}

print()
{
    Datum d;
    d = pop();
    printf("\t%.8g\n", d.val);
}

bltin()
{
    Datum d;
    d = pop();
    d.val = (*(double (*)())(*pc++))(d.val);
    push(d);
}

gt()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val > d2.val);
    push(d1);   
}

lt()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val < d2.val);
    push(d1);   
}

eq()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val == d2.val);
    push(d1);   
}

ge()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val >= d2.val);
    push(d1);    
}

le()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val <= d2.val);
    push(d1);
}

ne()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val != d2.val);
    push(d1);   
}

and()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val && d2.val);
    push(d1);   
}

or()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val || d2.val);
    push(d1);   
}

not()
{
    Datum d1;
    d1 = pop();
    d1.val = (double)(-d1.val);
    push(d1);   
}

whilecode()
{
    Datum d;
    Inst savepc = pc; /* loop body */
    
    execute(savepc+2);
    d = pop();
    while(d.val) {
        execute(*((Inst**)(savepc))); /* body */
        execute(savepc+2);
        d = pop();
    }
    pc = *((Inst **)(savepc+1)); /* next statement */
}

ifcode()
{
    Datum d;
    Inst *savepc = pc; /* then part */

    execute(savepc+3); /* condition */
    d = pop();
    if(d.val)
        execute(*((Inst **)(savepc)));
    else if (*((Inst **)(savepc+1))) /* else part */
        execute(*((Inst **)(savepc+1)));
    pc = *((Inst **)(savepc+2)); /* next statement */
}