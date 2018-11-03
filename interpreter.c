#include <stdio.h>
#include "parser.h"

void print_tabs(int tabs){
  for(int i=0; i < tabs; i++){
    printf(" ");
  }
  return;
}

void eval(Expr* expr, int tabs) {
  int result = 0;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    print_tabs(tabs);
    printf("%d\n", expr->attr.value);
    result = expr->attr.value;
  }
  else if (expr->kind == E_OPERATION) {
    //int vLeft = eval(expr->attr.op.left);
    //int vRight = eval(expr->attr.op.right);
    switch (expr->attr.op.operator) {
    case PLUS:
      print_tabs(tabs);
      printf("PLUS\n");
      //result = vLeft + vRight;
      eval(expr->attr.op.left, tabs + 1);
      eval(expr->attr.op.right, tabs + 1);
      break;
    case MINUS:
      print_tabs(tabs);
      printf("MINUS\n");
      //result = vLeft - vRight;
      eval(expr->attr.op.left, tabs + 1);
      eval(expr->attr.op.right, tabs + 1);
      break;
    case MULT:
      print_tabs(tabs);
      printf("MULT\n");
      //result = vLeft * vRight;
      eval(expr->attr.op.left, tabs + 1);
      eval(expr->attr.op.right, tabs + 1);
      break;
    case DIV:
      print_tabs(tabs);
      printf("DIV\n");
      //result = vLeft / vRight;
      eval(expr->attr.op.left, tabs + 1);
      eval(expr->attr.op.right, tabs + 1);
      break;
    case MOD:
      print_tabs(tabs);
      printf("MOD\n");
      //result = vLeft % vRight;
      eval(expr->attr.op.left, tabs + 1);
      eval(expr->attr.op.right, tabs + 1);
      break;
    default: yyerror("Unknown operator!");
    }
  }
  return;
}

void eval_bool(Expr_bool* expr, int tabs) {
  int result = 0;
  if(expr == 0) {
    yyerror("Null expression!!");
  }
  else if(expr->kind == E_INTEGER){
    print_tabs(tabs);
    printf("%d\n", expr->attr.value);
    result = expr->attr.value;
  }
  else if(expr->kind == E_OPERATION_BOOL){
    //int vLeft = eval(expr->attr.op.left);
    //int vRight = eval(expr->attr.op.right);
    switch(expr->attr.op.operator){
    case EQUALS:
      print_tabs(tabs);
      printf("EQUALS\n");
      //result = (vLeft == vRight);
      eval_bool(expr->attr.op.left, tabs + 1);
      eval_bool(expr->attr.op.right, tabs + 1);
      break;
    case DIFF:
      print_tabs(tabs);
      printf("DIFF\n");
      //result = (vLeft != vRight);
      eval_bool(expr->attr.op.left, tabs + 1);
      eval_bool(expr->attr.op.right, tabs + 1);
      break;
    case GT:
      print_tabs(tabs);
      printf("GT\n");
      //result = (vLeft > vRight);
      eval_bool(expr->attr.op.left, tabs + 1);
      eval_bool(expr->attr.op.right, tabs + 1);
      break;
    case GET:
      print_tabs(tabs);
      printf("GET\n");
      //result = (vLeft >= vRight);
      eval_bool(expr->attr.op.left, tabs + 1);
      eval_bool(expr->attr.op.right, tabs + 1);
      break;
    case LT:
      print_tabs(tabs);
      printf("LT\n");
      //result = (vLeft < vRight);
      eval_bool(expr->attr.op.left, tabs + 1);
      eval_bool(expr->attr.op.right, tabs + 1);
      break;
    case LET:
      print_tabs(tabs);
      printf("LET\n");
      //result = (vLeft <= vRight);
      eval_bool(expr->attr.op.left, tabs + 1);
      eval_bool(expr->attr.op.right, tabs + 1);
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
      //printf("Result = %d\n", eval(root));
  }
  return 0;


}
