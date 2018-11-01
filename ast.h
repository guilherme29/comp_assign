
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum {
    E_INTEGER,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    struct {
      int operator; // PLUS, MINUS, etc
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _Expr_bool {
  enum {
     E_BOOL,
     E_OPERATION_BOOL
  } kind;
  union {
    int value;
    struct {
      int operator;
      struct _Expr* left;
      struct _Expr* right;
    } op;
  } attr;
};

typedef struct _Expr Expr; // Convenience typedef
typedef struct _Expr_bool Expr_bool;
// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr_bool* ast_operation_bool(int operator, Expr* left, Expr* right);

#endif
