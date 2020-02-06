#include "hoc.h"
#include "y.tab.h"
#include <stdio.h>

#define NSTACK 256
static Datum stack[NSTACK]; /* the stack */
static Datum *stackp; /* next free spot on the stack */

#define NPROG 2000
Inst prog[NPROG]; /* the machine */
Inst *progp; /* next free spot for code generation */
Inst *pc; /* program counter during execution */
Inst *progbase = prog; /* statr of current subprogram */
int returning; /* 1 if return stmt seen */

typedef struct Frame { /* proc/func call stack frame */
    Symbol *sp; /* symbol table entry */
    Inst *retpc; /* whero to resume after return */
    Datum *argn; /* n-th argument on stack */
    int nargs; /* number of arguments */
} Frame;

#define NFRAME 100
Frame frame[NFRAME];
Frame *fp;

initcode(){ /* Initialize for code generation */
    stackp = stack;
    progp = progbase;
    fp = frame;
    returning = 0;
}

push(Datum d){ /* push d onto stack */
    if(stackp >= &stack[NSTACK])
        execerror("stack overflow", (char *) 0);
    *stackp++ = d;
}

Datum pop(){ /* pop and return from the stack */
    if(stackp == stack){
        execerror("stack underflow", (char *) 0);
    }
    return *--stackp;
}

Inst *code(Inst f){ /* Install one instruction or operand */
    Inst *oprogp = progp;
    if(progp >= &prog[NPROG]){
        execerror("program too big", (char *) 0);
    }
    *progp++ = f;
    return oprogp;
}

execute(Inst *p){ /* run the machine */
    for(pc = p; *pc != STOP && !returning;){
        (*(*pc++))();
    }
}

constpush(){ /* push constant onto stack */
    Datum d;
    d.val = ((Symbol *)* pc++)->u.val;
    push(d);
}

varpush(){ /* push variable onto stack  */
    Datum d;
    d.sym = (Symbol *)(*pc++);
    push(d);
}

prexpr(){
    Datum d;
    d = pop();
    printf("%.8g\n", d.val);
}

add(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val += d2.val;
    push(d1);
}

sub(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val -= d2.val;
    push(d1);
}

mul(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val *= d2.val;
    push(d1);
}

div(){
    Datum d1, d2;
    d2 = pop();
    if( d2.val == 0.0){ // check if zero
        execerror("Why u do dis?! dividing by zero are you mad", (char *)0);
    }
    d1 = pop();
    d1.val /= d2.val;
    push(d1);
}

negate(){
    Datum d1;
    d1 = pop();
    d1.val = -(d1.val);
    push(d1);
}

plusate(){
    Datum d1;
    d1 = pop();
    d1.val = +(d1.val);
    push(d1);
}

modulate(){
    Datum d1, d2, d;
    d2 = pop();
    d1 = pop();
    d.val = (int)d1.val % (int)d2.val;
    push(d);
}

power(){
    Datum d1, d2;
    extern double Pow();
    d2 = pop();
    d1 = pop();
    d1.val = Pow(d1.val, d2.val);
    push(d1);
}

eval(){
    Datum d;
    d = pop();
    if(d.sym->type != VAR && d.sym->type != UNDEF){
        execerror("attempt to evaluate non-variable", d.sym->name);
    }
    if(d.sym->type == UNDEF){
         execerror("undefined variable", d.sym->name);
    }
    d.val = d.sym->u.val;
    push(d);
}

assign(){
    Datum d1, d2;
    d1 = pop();
    d2 = pop();
    if( d1.sym->type != VAR && d1.sym->type != UNDEF){
        execerror("assignment to no-variable", d1.sym->name);
    }
    d1.sym->u.val = d2.val;
    d1.sym->type = VAR;
    push(d2);
}

print(){
    Datum d;
    d = pop();
    printf("\t%.8g\n", d.val);
}

bltin(){
    Datum d;
    d = pop();
    d.val = (*(double (*)())*pc++)(d.val);
    push(d);
}

gt(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val > d2.val);
    push(d1);   
}

lt(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val < d2.val);
    push(d1);   
}

eq(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val == d2.val);
    push(d1);   
}

ge(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val >= d2.val);
    push(d1);    
}

le(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val <= d2.val);
    push(d1);
}

ne(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val != d2.val);
    push(d1);   
}

and(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)((d1.val != 0.0) && (d2.val != 0.0));
    push(d1);   
}

or(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)((d1.val != 0.0) || (d2.val != 0.0));
    push(d1);   
}

not(){
    Datum d1;
    d1 = pop();
    d1.val = (double)(d1.val == 0.0);
    push(d1);   
}

whilecode(){
    Datum d;
    Inst *savepc = pc; /* loop body */
    
    execute(savepc+2);
    d = pop();
    while(d.val) {
        execute(*((Inst**)(savepc))); /* body */
        if(returning)
            break;
        execute(savepc+2);
        d = pop();
    }
    if(!returning)
        pc = *((Inst **)(savepc+1)); /* next statement */
}

ifcode(){
    Datum d;
    Inst *savepc = pc; /* then part */

    execute(savepc+3); /* condition */
    d = pop();
    if(d.val)
        execute(*((Inst **)(savepc)));
    else if (*((Inst **)(savepc+1))) /* else part */
        execute(*((Inst **)(savepc+1)));
    if(!returning)
        pc = *((Inst **)(savepc+2)); /* next statement */
}

define(Symbol *sp){ /* put func/proc in symbol table */
    sp->u.defn = (Inst)progbase; /*start of the code*/
    progbase = progp; /* next code starts here */
}

call(){
    Symbol *sp = (Symbol *)pc[0]; /* symbol table entry */
    /*if(fp++ >= &frame[NFRAME-1]);
        printf("*fp: %d\tfp: %d\n", *fp, &fp);
        execerror(sp->name, "call nested too deeply");*/
    fp->sp = sp;
    fp->nargs = (int)pc[1];
    fp->retpc = pc + 2;
    fp->argn = stackp -1; /* last argument */
    execute(sp->u.defn);
    returning = 0;
}

ret(){
    int i;
    for(i = 0; i < fp->nargs; i++){
        pop(); /* pop arguments */
    }
    pc = (Inst *)fp->retpc;
    --fp;
    returning = 1;
}

funcret(){
    Datum d;
    if(fp->sp->type == PROCEDURE){
        execerror(fp->sp->name, "(proc) returns value");
    }
    d = pop();
    ret();
    push(d);
}

procret(){/* common from a procedure */
    if(fp->sp->type == FUNCTION){
        execerror(fp->sp->name, "(func) returns no value");
    }
    ret();
}

double *getarg(){ /* return pointer to argument */
    int nargs = (int) *pc++;
    if(nargs > fp->nargs){
        execerror(fp->sp->name, "not enough arguments");
    }
    return &fp->argn[nargs - fp->nargs].val;
}

arg(){ /* push argument onto stack */
    Datum d;
    d.val = *getarg();
    push(d);
}

argassign(){ /* store top of the stack */
    Datum d;
    d = pop();
    push(d); /* leave value on stack */
    *getarg() = d.val;
}

prstr(){ /* prints string value */
    printf("%s", (char *) *pc++);
}


varread(){ /* read into variable */
    Datum d;
    extern FILE *fin;
    Symbol *var = (Symbol *) *pc++;
    Again:
        switch (fscanf(fin, "%lf", &var->u.val)){
        case EOF:
            if (moreinput()){
                goto Again;
            }
            d.val = var->u.val = 0.0;
            break;
        case 0:
            execerror("non-number read into", var->name);
            break;
        default:
            d.val = 1.0;
            break;
        }
        var->type = VAR;
        push(d);
}
