#include <stdio.h>
#include "parser.h"

void print_tabs(int tabs){
  for(int i=0; i < tabs; i++){
    printf(" ");
  }
  return;
}

int eval(Expr* expr) {
  int result = 0;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    result = expr->attr.value;
  }
  else if (expr->kind == E_OPERATION) {
    int vLeft = eval(expr->attr.op.left);
    int vRight = eval(expr->attr.op.right);
    switch (expr->attr.op.operator) {
    case PLUS:
      result = vLeft + vRight;
      break;
    case MINUS:
      result = vLeft - vRight;
      break;
    case MULT:
      result = vLeft * vRight;
      break;
    case DIV:
      result = vLeft / vRight;
      break;
    case MOD:
      result = vLeft % vRight;
      break;
    default: yyerror("Unknown operator!");
    }
  }
  return result;
}

int eval_bool(Expr_bool* expr) {
  int result = 0;
  if(expr == 0) {
    yyerror("Null expression!!");
  }
  else if(expr->kind == E_INTEGER){
    result = expr->attr.value;
  }
  else if(expr->kind == E_OPERATION_BOOL){
    int vLeft = eval(expr->attr.op.left);
    int vRight = eval(expr->attr.op.right);
    switch(expr->attr.op.operator){
    case EQUALS:
      result = (vLeft == vRight);
      break;
    case DIFF:
      result = (vLeft != vRight);
      break;
    case GT:
      result = (vLeft > vRight);
      break;
    case GET:
      result = (vLeft >= vRight);
      break;
    case LT:
      result = (vLeft < vRight);
      break;
    case LET:
      result = (vLeft <= vRight);
      break;
    default: yyerror("Unknown operator!");
    }
  }
}

int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
      printf("Result = %d\n", eval(root));
  }
  return 0;


}
