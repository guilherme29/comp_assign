
Instr* instr_ldc(int v) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_LDC;
  node->op.value = v;
  return node;
}

Instr* instr_adi() {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_ADI;
  return node;
}

Instr* instr_sbi() {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_SBI;
  return node;
}

Instr* instr_mpi() {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_MPI;
  return node;
}

Instr* instr_dvi() {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_DVI;
  return node;
}

Instr* instr_lod(char *var){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_LOD;
  node->attr.var = var;
  return node;
}

Instr* instr_lda(char *var){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_LDA;
  node->attr.var = var;
  return node;
}

Instr* instr_sto(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_STO;
  return node;
}

Instr* instr_grt(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = GRT;
  return node;
}

Instr* instr_les(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_LES;
  return node;
}

Instr* instr_geq(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_GEQ;
  return node;
}

Instr* instr_leq(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_LEQ;
  return node;
}

Instr* instr_neq(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_NEQ;
  return node;
}

Instr* instr_equ(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_EQU;
  return node;
}

Instr* instr_ujp(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_UJP;
  return node;
}

Instr* instr_fjp(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_FJP;
  return node;
}

Instr* instr_lab(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_LAB;
  return node;
}

Instr* instr_rdi(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_RDI;
  return node;
}

Instr* instr_wri(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->op = I_WRI;
  return node;
}

Instr_List* make_instr_list(Instr* instr, Instr_List* next){
  Instr_List* list = malloc(sizeof(Instr_List));
  list->instr = instr;
  list->next = next;
  return list;
}

Instr_List* append(Instr_List* list1, Instr_List* list2){ //o append e capaz de nao ser assim
  if(list1 == NULL){
    return list2;
  }
  Instr_List* aux = list1;
  while(aux->next != NULL){
    aux = aux->next;
  }
  aux->next = list2;
  return list1;
}

Instr* head(Instr_List* list){
  return list->instr;
}

Instr_List* tail(Instr_List* list){
  return list->next;
}

void print_instr(Instr* instr){
  switch(instr->kind){
  case I_LDC:{
    printf("ldc %d\n", instr->op);
    break;
  }
  case I_ADI:{
    printf("adi %d\n", instr->op);
    break;
  }
  case I_SBI:{
    printf("sbi %d\n", instr->op);
    break;
  }
  case I_MPI:{
    printf("mpi %d\n", instr->op);
    break;
  }
  case I_DVI:{
    printf("dvi %d\n", instr->op);
    break;
  }
  }
  return;
}

void print_instr_list(Instr_List* list){
  Instr_List* aux = list;
  while(aux->next != NULL){
    print_instr(aux->instr);
    aux = aux->next;
  }
  return;
}
