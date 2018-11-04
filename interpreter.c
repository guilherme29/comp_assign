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
      eval(expr->attr.op.left, tabs + 1);
      eval(expr->attr.op.right, tabs + 1);
      break;
    case DIFF:
      print_tabs(tabs);
      printf("DIFF\n");
      //result = (vLeft != vRight);
      eval(expr->attr.op.left, tabs + 1);
      eval(expr->attr.op.right, tabs + 1);
      break;
    case GT:
      print_tabs(tabs);
      printf("GT\n");
      //result = (vLeft > vRight);
      eval(expr->attr.op.left, tabs + 1);
      eval(expr->attr.op.right, tabs + 1);
      break;
    case GET:
      print_tabs(tabs);
      printf("GET\n");
      //result = (vLeft >= vRight);
      eval(expr->attr.op.left, tabs + 1);
      eval(expr->attr.op.right, tabs + 1);
      break;
    case LT:
      print_tabs(tabs);
      printf("LT\n");
      //result = (vLeft < vRight);
      eval(expr->attr.op.left, tabs + 1);
      eval(expr->attr.op.right, tabs + 1);
      break;
    case LET:
      print_tabs(tabs);
      printf("LET\n");
      //result = (vLeft <= vRight);
      eval(expr->attr.op.left, tabs + 1);
      eval(expr->attr.op.right, tabs + 1);
      break;
    default: yyerror("Unknown operator!");
    }
  }
  else {
    if(expr->attr.var == 280){          //TRUE
      print_tabs(tabs);
      printf("TRUE\n");
    }
    else {
      print_tabs(tabs);
      printf("FALSE\n");
    }
  }
}

void eval_cmd(Cmd* list, int tabs) {
  switch (list->kind) {
    case E_ATRIB:
      print_tabs(tabs);
      printf("ATRIB\n");
      print_tabs(tabs+1);
      printf("%s\n", list->attr.atrib.left);
      eval(list->attr.atrib.right, tabs+1);
      break;
    case E_IF:
      print_tabs(tabs);
      printf("IF\n");
      eval_bool(list->attr._if.expr, tabs+1);
      eval_cmd(list->attr._if.list, tabs+1);
      break;
    case E_IFELSE:
      print_tabs(tabs);
      printf("IF\n");
      eval_bool(list->attr._ifelse.expr, tabs+1);
      eval_cmd(list->attr._ifelse.list1, tabs+1);
      print_tabs(tabs);
      printf("ELSE\n");
      eval_cmd(list->attr._ifelse.list2, tabs+1);
      break;
    case E_WHILE:
      print_tabs(tabs);
      printf("WHILE\n");
      eval_bool(list->attr._while.expr, tabs+1);
      eval_cmd(list->attr._while.list, tabs+1);
      break;
    case E_SCANF:
    	print_tabs(tabs);
    	printf("SCANF\n");
    	print_tabs(tabs+1);
    	printf("%s\n", list->attr._scanf.var);
    	break;
    case E_PRINTF:
    	print_tabs(tabs);
    	printf("PRINTF\n");
    	eval(list->attr._printf.expr, tabs+1);
    	break;
    case E_LISTCMD:
      eval_cmd(list->attr.list_cmd.head, tabs+1);
      if(list->attr.list_cmd.tail != NULL){
        eval_cmd(list->attr.list_cmd.tail, tabs);
      }
      break;
  }
  return;
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
      printf("MAIN\n");
      Cmd* list = root;
      eval_cmd(list, 1);
      //printf("Result = %d\n", eval(root));
  }
  return 0;


}
