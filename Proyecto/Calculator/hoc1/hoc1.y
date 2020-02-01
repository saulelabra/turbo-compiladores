%{
#define YYSTYPE double
%}
%token NUMBER /* the order affects precedence */
%left '+' '-'
%left '*' '/' '%'
%left UNARYMINUS UNARYPLUS
%%
list:
    | list '\n'
    | list expr '\n' { printf("\t%.8g\n", $2); }
    ;
expr:   NUMBER          { $$ = $1; }
        | '+' expr %prec UNARYPLUS { $$ = +$2; }
        | '-' expr %prec UNARYMINUS { $$ = -$2; }
        | expr '+' expr { $$ = $1 + $3; }
        | expr '-' expr { $$ = $1 - $3; }
        | expr '*' expr { $$ = $1 * $3; }
        | expr '/' expr { $$ = $1 / $3; }
        | expr '%' expr { $$ = (int)$1 % (int)$3; }
        | '(' expr ')'  { $$ = $2; }
        ;
%%

#include <stdio.h>
#include <ctype.h>
char  *progname;
int lineno = 1;

main(argc, argv)
    char *argv[];
{
    progname = argv[0];
    yyparse();
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
        scanf("%lf", &yylval);
        return NUMBER;
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