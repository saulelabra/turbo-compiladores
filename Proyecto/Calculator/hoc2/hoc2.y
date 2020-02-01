%{
double mem[26];
%}
%union {
    double val;
    int index;
}
%token <val> NUMBER
%token <index> VAR
%type <val> expr
%right '='
%left '+' '-'
%left '*' '/' '%'
%left UNARYMINUS UNARYPLUS
%%
list:
    | list '\n'
    | list expr '\n' { printf("\t%.8g\n", $2); }
    | list error '\n' { yyerrok; }
    ;
expr:   NUMBER
        | VAR           { $$ = mem[$1]; }
        | VAR '=' expr  { $$ = mem[$1] = $3; }
        | expr '+' expr { $$ = $1 + $3; }
        | expr '-' expr { $$ = $1 - $3; }
        | expr '*' expr { $$ = $1 * $3; }
        | expr '/' expr { 
            if($3 == 0.0)
                execerror("division by zero", "");
            $$ = $1 / $3; }
        | expr '%' expr { $$ = (int)$1 % (int)$3; }
        | '(' expr ')'  { $$ = $2; }
        | '+' expr %prec UNARYPLUS { $$ = +$2; }
        | '-' expr %prec UNARYMINUS { $$ = -$2; }
        ;
%%

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>
jmp_buf begin;
char  *progname;
int lineno = 1;

main(argc, argv)
    char *argv[];
{
    int fpecatch();

    progname = argv[0];
    setjmp(begin);
    signal(SIGFPE, fpecatch);
    yyparse();
}

execerror(s, t) /* recover from runtime error */
    char *s, *t;
{
    warning(s, t);
    longjmp(begin, 0);
}

fpecatch() /* catch floating point exceptions */
{
    execerror("floating point exception", (char *) 0);
}

yylex()
{
    int c;

    while((c=getchar()) == ' ' || c == '\t')
        ;
    if(c == EOF)
        return 0;

    if(c == '.' || isdigit(c)) {
        ungetc(c, stdin);
        scanf("%lf", &yylval.val);
        return NUMBER;
    }

    if(islower(c)) {
        yylval.index = c - 'a';
        return VAR;
    }

    if(c == "\n")
        lineno++;

    return c;
}

yyerror(s)
    char *s;
{
    warning(s, (char *) 0);
}

warning(s, t)
    char *s, *t;
{
    fprintf(stderr, "%s: %s", progname, s);
    if(t)
        printf(stderr, " %s", t);
    fprintf(stderr, " near line %d\n", lineno);
}