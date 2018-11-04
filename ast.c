// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header
#include <string.h> //for strdup

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Expr_bool* ast_bool (int v){
  Expr_bool* node = (Expr_bool*) malloc(sizeof(Expr_bool));
  node->kind = E_BOOL;
  node->attr.value = v;
  return node;
}

Expr_bool* ast_operation_bool
(int operator, Expr* left, Expr* right) {
  Expr_bool* node = (Expr_bool*) malloc (sizeof(Expr_bool));
  node->kind = E_OPERATION_BOOL;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}


//command constructor functions
Cmd* ast_atrib(char* string, Expr* expr){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_ATRIB;
  node->attr.atrib.left = strdup(string);
  //cria nova string igual e devolve apontador
  node->attr.atrib.right = expr;
}

Cmd* ast_if(Expr_bool* expr, Cmd* list){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd*));
  node->kind = E_IF;
  node->attr._if.expr = expr;
  node->attr._if.list = list;
  return node;
}

Cmd* ast_ifelse(Expr_bool* expr, Cmd* list1, Cmd* list2){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd*));
  node->kind = E_IFELSE;
  node->attr._ifelse.expr = expr;
  node->attr._ifelse.list1 = list1;
  node->attr._ifelse.list2 = list2;
  return node;
}

Cmd* ast_while(Expr_bool* expr, Cmd* list){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd*));
  node->attr._while.expr = expr;
  node->attr._while.list = list;
  return node;
}

Cmd* ast_scan(char* var){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_SCANF;
  node->attr._scanf.var = strdup(var);
  return node;
}

Cmd* ast_printf(Expr* expr){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_PRINTF;
  node->attr._printf.expr = expr;
  return node;
}


Cmd* ast_cmd_list(Cmd* cmd, Cmd* next) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_LISTCMD;
  node->attr.list_cmd.head = cmd;
  node->attr.list_cmd.tail = next;
  return node;
}
