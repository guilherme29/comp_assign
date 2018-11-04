// Tokens
%token
  IMPORT
  INT
  VAR
  MAIN
  OPEN
  CLOSE
  OPEN_BRACKET
  CLOSE_BRACKET
  ATRIB
  SEMICOLON
  IF
  ELSE
  WHILE
  PRINTF
  SCANF
  ADDRESS
  PRINT_INT
  PLUS
  MINUS
  MULT
  DIV
  MOD
  TRUE
  FALSE
  EQUALS
  DIFF
  GT
  LT
  GET
  LET

// Operator associativity & precedence
%left EQUAL DIFF GT LT GET LET
%left PLUS MINUS
%left MULT DIV
%left MOD

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue;
  Expr_bool* expr_boolValue;
  Cmd* cmd;
  char* var;
}

%type <intValue> INT
%type <exprValue> expr
%type <expr_boolValue> expr_bool
%type <cmd> cmd
%type <var> var

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Expr* root;
}

%%
program: expr { root = $1; };

expr_bool:
  TRUE {
    $$ = ast_bool(TRUE);
  }
  |
  FALSE {
    $$ = ast_bool(FALSE);
  }
  |
  expr EQUALS expr {
    $$ = ast_operation_bool(EQUALS, $1, $3);
  }
  |
  expr DIFF expr {
    $$ = ast_operation_bool(DIFF, $1, $3);
  }
  |
  expr GT expr {
    $$ = ast_operation_bool(GT, $1, $3);
  }
  |
  expr GET expr {
    $$ = ast_operation_bool(GET, $1, $3);
  }
  |
  expr LT expr {
    $$ = ast_operation_bool(LT, $1, $3);
  }
  |
  expr LET expr {
    $$ = ast_operation_bool(LET, $1, $3);
  }
;

expr:
  INT {
    $$ = ast_integer($1);
  }
  |
  expr PLUS expr {
    $$ = ast_operation(PLUS, $1, $3);
  }
  |
  expr MINUS expr {
    $$ = ast_operation(MINUS, $1, $3);
  }
  |
  expr MULT expr {
    $$ = ast_operation(MULT, $1, $3);
  }
  |
  expr DIV expr {
    $$ = ast_operation(DIV, $1, $3);
  }
  |
  expr MOD expr {
    $$ = ast_operation(MOD, $1 , $3);
  }
;

cmd_list:
  { $$ = NULL; /*se estiver vazia*/ }
  |
  cmd cmd_list { $$ = ast_cmd_list($1, $2); }

cmd:
  VAR ATRIB expr SEMICOLON { //atribuicao
    $$ = ast_atrib($1, $3);
  }
  |
  IF OPEN expr_bool CLOSE OPEN_BRACKET cmd_list CLOSE_BRACKET { //if com chavetas
    $$ = ast_if($3, $6);
  }
  |
  IF OPEN expr_bool CLOSE OPEN_BRACKET cmd_list CLOSE_BRACKET ELSE OPEN_BRACKET cmd_list CLOSE_BRACKET {
    $$ = ast_ifelse($3, $6, $10);
  }
  |
  WHILE OPEN expr_bool CLOSE OPEN_BRACKET cmd_list CLOSE_BRACKET {
    $$ = ast_while($3, $6);
  }
  |
  SCANF OPEN QUOTES PR_INT QUOTES COMMA ADDRESS VAR CLOSE SEMICOLON {
    $$ = ast_scanf($8);
  }
  |
  PRINTF OPEN QUOTES PR_INT QUOTES COMMA VAR CLOSE SEMICOLON {
    $$ = ast_printf($7);
  }
;

%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
