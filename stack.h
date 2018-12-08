
struct _Instr {
  enum {
    I_LDC,
    I_ADI,
    I_SBI,
    I_MPI,
    I_DVI
  } kind;
  union {
    int value;
  } op;
};

struct _Instr_List {
  struct _Instr *instr;
  struct _Instr_List *next;
};
typedef struct _Instr Instr;
typedef struct _Instr_List Instr_List;
