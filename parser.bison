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
  BTRUE
  BFALSE
  EQUALS
  DIFF
  GT
  LT
  GET
  LET
  CARDINAL
  COMMA
  INCLUDE
  STDIO_H
  PR_INT
  QUOTES
  FLOAT

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
  float floatValue;
  Expr* exprValue;
  Expr_bool* expr_boolValue;
  Cmd* cmd;
  Cmd* cmd_list;
  char* var;
}

%type <intValue> INT
%type <floatValue> FLOAT
%type <exprValue> expr
%type <expr_boolValue> expr_bool
%type <cmd> cmd
%type <cmd_list> cmd_list
%type <var> VAR

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
Cmd* root;
}

%%
program:
  CARDINAL INCLUDE LT STDIO_H GT MAIN OPEN CLOSE OPEN_BRACKET cmd_list CLOSE_BRACKET {
    root = $10;
  }
  |
  MAIN OPEN CLOSE OPEN_BRACKET cmd_list CLOSE_BRACKET {
    root = $5;
  }
;

cmd_list:
  { $$ = NULL; /*se estiver vazia*/ }
  |
  cmd cmd_list { $$ = ast_cmd_list($1, $2); }

cmd:
  INT VAR ATRIB expr SEMICOLON { //atribuicao
    $$ = ast_atrib($2, $4);
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
  PRINTF OPEN QUOTES PR_INT QUOTES COMMA expr CLOSE SEMICOLON {
    $$ = ast_printf($7);
  }
;


expr_bool:
  BTRUE {
    $$ = ast_bool(BTRUE);
  }
  |
  BFALSE {
    $$ = ast_bool(BFALSE);
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
  FLOAT {
    $$ = ast_float($1);
  }
  |
  VAR {
    $$ = ast_var($1);
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

%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
