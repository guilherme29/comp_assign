
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

struct _Cmd {
  enum {
    E_ATRIB,
    E_IF,
    E_IFELSE,
    E_WHILE,
    E_SCANF,
    E_PRINTF,
    E_LISTCMD
  } kind;
  union {
    struct {
      char* left;
      struct _Expr* right;
    } atrib;
    struct {
      struct _Expr_bool* expr;
      struct _Cmd* list;
    } _if;
    struct {
      struct _Expr_bool* expr;
      struct _Cmd* list1;
      struct _Cmd* list2;
    } _ifelse;
    struct {
      struct _Expr_bool* expr;
      struct _Cmd* list;
    } _while;
    struct {
      char* var;
    } _scanf;
    struct {
      struct _Expr* expr; //n tenho a certeza deste
    } _printf;
    struct {
      struct _Cmd* head;
      struct _Cmd* tail;
    } list_cmd;
  } attr;
};

typedef struct _Expr Expr; // Convenience typedef
typedef struct _Expr_bool Expr_bool;
typedef struct _Cmd Cmd;
typedef struct _Cmd_list Cmd_list;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr_bool* ast_operation_bool(int operator, Expr* left, Expr* right);

#endif
