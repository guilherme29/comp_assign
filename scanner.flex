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
"true" { return TRUE; }
"false" { return FALSE; }

"include" { return INCLUDE; }
"int main" { return MAIN; }
"(" { return OPEN; }
")" { return CLOSE; }
"{" { return OPEN_BRACKET; }
"}" { return CLOSE_BRACKET; }
"=" { return ATRIB; }
";" { return SEMICOLON; }
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"printf" { return PRINTF; }
"scanf" { return SCANF; }
"&" { return ADDRESS; }
"%d" { return PR_INT; }
"," { return COMMA; }
"\"" { return QUOTES; }
"#" { return CARDINAL; }
"stdio.h" { return STDIO_H; }

\-?[0-9]+ {
   yylval.intValue = atoi(yytext);
   return INT;
}
[a-z][a-zA-Z]* {
	yylval.var = strdup(yytext);
	return VAR;
}

.  { yyerror("unexpected character"); }
%%
