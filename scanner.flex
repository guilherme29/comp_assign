%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULT; }
"/" { return DIV; }
"%" { return MOD; }

"<" { return LT; }
">" { return GT; }
"<=" { return LET; }
">=" { return GET; }
"!=" { return DIFF; }
"==" { return EQUALS; }




\-?[0-9]+ {
   yylval.intValue = atoi(yytext);
   return INT;
}

.  { yyerror("unexpected character"); }
%%
