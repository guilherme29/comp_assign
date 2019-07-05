#ifndef __stack_h__
#define __stack_h__

struct _Instr {
  enum {
    I_LDC,
    I_ADI,
    I_SBI,
    I_MPI,
    I_DVI
    I_LOD,
    I_LDA,
    I_STO,
    I_GRT,
    I_LES,
    I_GEQ,
    I_LEQ,
    I_NEQ,
    I_EQU,
    I_UJP,
    I_FJP,
    I_LAB,
    I_RDI,
    I_WRI

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

//constructor functions
Instr* instr_ldc(int v);
Instr* instr_adi();
Instr* instr_sbi();
Instr* instr_mpi();
Instr* instr_dvi();
Instr* instr_lod(char* var);
Instr* instr_lda(char* var);
Instr* instr_sto();
Instr* instr_grt();
Instr* instr_les();
Instr* instr_geq();
Instr* instr_leq();
Instr* instr_neq();
Instr* instr_equ();
Instr* instr_ujp();
Instr* instr_fjp();
Instr* instr_lab();
Instr* instr_rdi();
Instr* instr_wri();


#endif
