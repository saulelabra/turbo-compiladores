typedef struct Symbol {
    char *name;
    short type;
    union {
        double val;
        double (*ptr)();
    } u;
    struct Symbol *next;
}Symbol;
Symbol *install(), *lookup();

typedef union Datum {
    double val;
    Symbol *sym;
} Datum;
extern Datum pop();

typedef int (*Inst)();
#define STOP (Inst) 0

extern Inst prog[], *progp, *code();
extern eval(), add(), sub(), mul(), div(), negate(), power();
extern assign(), bltin(), varpush(), constpush(), print();
extern prexpr();
extern gt(), lt(), eq(), ge(), le(), ne(), and(), or(), not();
extern ifcode(), whilecode();