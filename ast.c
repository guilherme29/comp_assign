// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

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
  node->attr_bool.value = v;
  return node;
}

Expr_bool* ast_operation_bool
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc (sizeof(Expr));
  node->kind = E_OPERATION_BOOL;
  node->attr_bool.op_bool.left = left;
  node->attr_bool.op_bool.right = right;
  return node;
}
