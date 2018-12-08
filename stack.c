
Instr* instr_ldc(int v) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_LDC;
  node->op.value = v;
  return node;
}

Instr* instr_adi(int v) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_ADI;
  node->op.value = v;
  return node;
}

Instr* instr_sbi(int v) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_SBI;
  node->op.value = v;
  return node;
}

Instr* instr_mpi(int v) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_MPI;
  node->op.value = v;
  return node;
}

Instr* instr_dvi(int v) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_DVI;
  node->op.value = v;
  return node;
}

Instr_List* instr_list(Instr* instr, Instr_List* next){
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
