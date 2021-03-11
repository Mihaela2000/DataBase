/*BUZDUGAN Mihaela - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structures.h"

//cu ajutorul acestei functii se va initializa o baza de bate
t_db *init_db(char *name){
  t_db *data_base=malloc(sizeof(t_db));
  if(data_base==NULL)
    return NULL;
  strcpy(data_base->name, name);
  data_base->tables=NULL;
  return data_base;
}

//cu ajutorul acestei functii se va printa tabelul dorit din baza de date 
void print_table(t_db *data_base, char *name_table){
  t_table *aux_table;
  t_column *aux_column;
  int i, crt,err=0;
  
  //se va parcurge lista cu tabele din baza de date 
  //daca se gaseste tabelul cerut,se va parcurge lista cu coloane din 
  //acesta si lista cu linii si la randul lor si lista cu celule si se va 
  //printa altfel va aparea o eroare ca nu s-a gasit tabelul in baza de date
  for(aux_table=data_base->tables; aux_table!=NULL; aux_table=aux_table->next){
    if(strcmp(aux_table->name,name_table )==0){
      err=1;
      printf("TABLE: %s\n", aux_table->name);
      for(aux_column=aux_table->columns; aux_column!=NULL;
      aux_column=aux_column->next){
        printf("%s", aux_column->name);
        for(int i=0; i<MAX_COLUMN_NAME_LEN-strlen(aux_column->name); i++){
          printf(" ");
        } 
        printf(" ");
      }
      printf("\n");
      for(aux_column=aux_table->columns; aux_column!=NULL;
      aux_column=aux_column->next){
        for(i=0; i<MAX_COLUMN_NAME_LEN; i++){
          printf("-");
        }
        printf(" ");
      }
      printf("\n");
      switch (aux_table->type){
        case INT:{
          t_intLine *aux_line;
          t_intCell *aux_cell;
          int test_cell;
          crt=0;
          for(aux_line=aux_table->lines; aux_line!=NULL;
          aux_line=aux_line->next){
            for(aux_cell=aux_line->cells; aux_cell!=NULL;
            aux_cell=aux_cell->next){
              crt=0;
              printf("%d", aux_cell->value);
            
              if(aux_cell->value==0)
                crt=1;
              else
                for(test_cell=aux_cell->value; test_cell!=0;
                test_cell=test_cell/10, crt++);
            
              for(i=0; i<MAX_COLUMN_NAME_LEN-crt; i++){
                printf(" ");
              }
              printf(" ");
            }
            printf("\n");
          }
          break;
        }
        case FLOAT:{
          t_floatLine *aux_line;
          t_floatCell *aux_cell;
          float test_cell;
          crt=0;
          for(aux_line=aux_table->lines; aux_line!=NULL;
          aux_line=aux_line->next){
            for(aux_cell=aux_line->cells; aux_cell!=NULL;
            aux_cell=aux_cell->next){
              crt=0;
              if(fabs(aux_cell->value) < 1) {
                  crt++;
              }
              printf("%.6f", aux_cell->value);
              //fabs() - pt modul
              for(test_cell=aux_cell->value; fabs(test_cell)>=1;
              test_cell=test_cell/10 ,crt++);
              for(i=0; i<MAX_COLUMN_NAME_LEN-crt-7; i++){
                printf(" ");
              }
              printf(" ");
            }
            printf("\n");
          }
          break;
        }
        case STRING:{
          t_stringLine *aux_line;
          t_stringCell *aux_cell;
          for(aux_line=aux_table->lines; aux_line!=NULL;
          aux_line=aux_line->next){
            for(aux_cell=aux_line->cells; aux_cell!=NULL;
            aux_cell=aux_cell->next){
              printf("%s", aux_cell->value);
              for(i=0; i<MAX_COLUMN_NAME_LEN-strlen(aux_cell->value); i++){
                printf(" ");
              }
              printf(" ");
            }
            printf("\n");
          }
          break;
        }
      }
      printf("\n");
    }
  }
  if(err==0){
    printf("Table \"%s\" not found in database.\n", name_table);
  }
}

//cu ajutorul acestei functii se va printa baza de date
void print_db(t_db *data_base){
  printf("DATABASE: %s\n\n", data_base->name);
  t_table *aux_table;
  t_column *aux_column;
  int i, crt;
  //se va parcurge lista cu tabele si la randul 
  //lor lista cu coloane si cea cu linii, care la randul lor 
  //se va parcurge lista cu celule si se vor afisa tabelele
  for(aux_table=data_base->tables; aux_table!=NULL; aux_table=aux_table->next){
    printf("TABLE: %s\n", aux_table->name);
    for(aux_column=aux_table->columns; aux_column!=NULL;
    aux_column=aux_column->next){
      printf("%s", aux_column->name);
      for(int i=0; i<MAX_COLUMN_NAME_LEN-strlen(aux_column->name); i++){
        printf(" ");
      } 
      printf(" ");
    }
    printf("\n");
    for(aux_column=aux_table->columns; aux_column!=NULL;
    aux_column=aux_column->next){
      for(i=0; i<MAX_COLUMN_NAME_LEN; i++){
        printf("-");
      }
      printf(" ");
    }
    printf("\n");
    switch (aux_table->type){
      case INT:{
        t_intLine *aux_line;
        t_intCell *aux_cell;
        int test_cell;
        crt=0;
        for(aux_line=aux_table->lines; aux_line!=NULL;
        aux_line=aux_line->next){
          
          for(aux_cell=aux_line->cells; aux_cell!=NULL;
          aux_cell=aux_cell->next){
            crt=0;
            printf("%d", aux_cell->value);
            
            if(aux_cell->value==0)
              crt=1;
            else
              for(test_cell=aux_cell->value; test_cell!=0; 
              test_cell=test_cell/10, crt++);
            
            for(i=0; i<MAX_COLUMN_NAME_LEN-crt; i++){
              printf(" ");
            }
            printf(" ");
          }
          printf("\n");
        }
        break;
      }
      case FLOAT:{
        t_floatLine *aux_line;
        t_floatCell *aux_cell;
        float test_cell;
        crt=0;
        for(aux_line=aux_table->lines; aux_line!=NULL; 
        aux_line=aux_line->next){
          for(aux_cell=aux_line->cells; aux_cell!=NULL; 
          aux_cell=aux_cell->next){
            crt=0;
            if(fabs(aux_cell->value) < 1) {
                  crt++;
            }
            printf("%.6f", aux_cell->value);
            //fabs() - pt modul
            for(test_cell=aux_cell->value; fabs(test_cell)>=1; 
            test_cell=test_cell/10 ,crt++);
            for(i=0; i<MAX_COLUMN_NAME_LEN-crt-7; i++){
              printf(" ");
            }
            printf(" ");
          }
          printf("\n");
        }
        break;

      }
      case STRING:{
        t_stringLine *aux_line;
        t_stringCell *aux_cell;
        for(aux_line=aux_table->lines; aux_line!=NULL; 
        aux_line=aux_line->next){
          for(aux_cell=aux_line->cells; aux_cell!=NULL; 
          aux_cell=aux_cell->next){
            printf("%s", aux_cell->value);
            for(i=0; i<MAX_COLUMN_NAME_LEN-strlen(aux_cell->value); i++){
              printf(" ");
            }
            printf(" ");
          }
          printf("\n");
        }
        break;
      }
    }
    printf("\n");
  }
}

//cu ajutorul acestei functii se va creea un tabel cu coloane
void create(t_db *data_base, char *name_table, t_cellType type,
 char *name_col[], int nr_col ){
  int i;
  t_table *aux_table;
  int err=0;
  //se va parcurge lista cu tabele si se va verifica daca exista deja numele
  //tabelului cerut. Daca exista, se va afisa direct un mesaj, iar daca nu,
  //functia de creare va continua sa creeze un tabel
  for(aux_table=data_base->tables; aux_table!=NULL; aux_table=aux_table->next){
    if(strcmp(aux_table->name,name_table )==0){
      err=1;
    }
  }
  if(err==1){
    printf("Table \"%s\" already exists.\n", name_table);
    return;
  }
  t_table *table=malloc(sizeof(t_table));
  if(table==NULL){
    return;
  }
  t_column *column=malloc(sizeof(t_column));
  if(column==NULL){
    free(table);
    return;
  }
  column->next = NULL;
  strcpy(column->name,name_col[0]);
  table->columns=column;
  for(i=1;i<nr_col;i++){
    t_column *aux_col=malloc(sizeof(t_column));
    if(aux_col==NULL){
      return;
    }
    strcpy(aux_col->name, name_col[i]);
    aux_col->next=NULL;
    column->next=aux_col;
    column=column->next;
  }
  table->lines=NULL;
  table->next=NULL;
  strcpy(table->name, name_table);
  table->type=type;

  if(data_base->tables==NULL){
    data_base->tables=table;
  }else{
    t_table *aux_table;
    for(aux_table=data_base->tables; aux_table->next!=NULL; 
    aux_table=aux_table->next);
    aux_table->next=table;
  }
}

//cu ajutorul acestei functii se vor adauga linii in tabelul specificat, 
//cu numarul celulelor in functie de numarul coloanelor
void add_line(t_db *data_base, char *name_table, char *val_cell[], int nr_col){
  t_table *aux_table;
  int err=0;
  //voi parcurge fiecare tabel din baza de date pana voi gasi tabelul la care
  //vreau sa adaug liniile.
  //in cazul in care tabelul nu se va gasi, se va iesi din bucla si se va
  //afisa un mesaj specific.
  for(aux_table=data_base->tables; aux_table!=NULL; aux_table=aux_table->next){
    if(strcmp(aux_table->name,name_table )==0){
      err=1;
      switch (aux_table->type){
        case INT:{
          t_intLine *new_line=malloc(sizeof(t_intLine));
          if(new_line==NULL)
            return;
          if(aux_table->lines==NULL)
            aux_table->lines=new_line;
          else{
            t_intLine *aux_line;
            for(aux_line=aux_table->lines; aux_line->next!=NULL; 
            aux_line=aux_line->next);
            aux_line->next=new_line;
          }
          new_line->next=NULL;
          t_intCell *new_cell=malloc(sizeof(t_intCell));
		  new_cell->next = NULL;
          new_line->cells=new_cell;
          //din string in int
          new_cell->value=atoi(val_cell[0]);
          for(int i=1; i<nr_col; i++){
            t_intCell *aux_cell=malloc(sizeof(t_intCell));
            if(aux_cell==NULL)
              return;
            aux_cell->value=atoi(val_cell[i]);
            new_cell->next=aux_cell;
            aux_cell->next=NULL;
            new_cell=new_cell->next;
          }
          break;
        }
        case FLOAT:{
          t_floatLine *new_line=malloc(sizeof(t_floatLine));
          if(new_line==NULL)
            return;
          if(aux_table->lines==NULL)
            aux_table->lines=new_line;
          else{
            t_floatLine *aux_line;
            for(aux_line=aux_table->lines; aux_line->next!=NULL; 
            aux_line=aux_line->next);
            aux_line->next=new_line;
          }
          new_line->next=NULL;
          t_floatCell *new_cell=malloc(sizeof(t_floatCell));
		  new_cell->next=NULL;
          new_line->cells=new_cell;
          //din string in float
          new_cell->value=strtof(val_cell[0], NULL);
          for(int i=1; i<nr_col; i++){
            t_floatCell *aux_cell=malloc(sizeof(t_floatCell));
            if(aux_cell==NULL)
              return;
            //din string in float
            aux_cell->value=strtof(val_cell[i], NULL);
            new_cell->next=aux_cell;
            aux_cell->next=NULL;
            new_cell=new_cell->next;
          }
          break;
        }
        case STRING:{
          t_stringLine *new_line=malloc(sizeof(t_stringLine));
          if(new_line==NULL)
            return;
          if(aux_table->lines==NULL)
            aux_table->lines=new_line;
          else{
            t_stringLine *aux_line;
            for(aux_line=aux_table->lines; aux_line->next!=NULL; 
            aux_line=aux_line->next);
            aux_line->next=new_line;
          }
          new_line->next=NULL;
          t_stringCell *new_cell=malloc(sizeof(t_stringCell));
		  new_cell->next = NULL;
          new_line->cells=new_cell;
          //copiere si alocarea altei zone pt new_cell->value[0]
          new_cell->value=strdup(val_cell[0]);
          for(int i=1; i<nr_col; i++){
            t_stringCell *aux_cell=malloc(sizeof(t_stringCell));
            if(aux_cell==NULL)
              return;
            aux_cell->value=strdup(val_cell[i]);
            new_cell->next=aux_cell;
            aux_cell->next=NULL;
            new_cell=new_cell->next;
          }
          break; 
        }   
      }
    }
  }
  if(err==0){
    printf("Table \"%s\" not found in database.\n", name_table);
  }
}

//cu ajutorul acestei functii se vor sterge liniile de pe coloana 
//specificata care respecta relatia data
void delete(t_db *data_base, char *name_table, char *name_col,
 char* relational, char *val_cell){
  t_table *aux_table;
  t_column *aux_column;

  int nr_col, i, err_table=0, err_col=0;
  //se va parcurge lista de tabele din baza de date si se va verifica 
  //daca exista tabelul specificat. In cazul in care nu exista, 
  //se va afisa un mesaj corespunzator.
  for(aux_table=data_base->tables; aux_table!=NULL; aux_table=aux_table->next){
    if(strcmp(aux_table->name,name_table)==0){
      err_table=1;
      //se va parcurge lista cu coloane pana se va gasi coloana indicata(in
      //cazul in care aceasta nu exista, se va afisa un mesaj corespunzator),
      //iar in acelasi timp se va calula si pozitia coloanei specificate
      for(nr_col=0,aux_column=aux_table->columns; aux_column!=NULL;nr_col++,
      aux_column=aux_column->next){
        if(strcmp(aux_column->name, name_col)==0){
          err_col=1;
          //se va parcurge fiecare linie in functie de tipul tabelului
          //dupa aceea se va parcurge lista de celule pana cand se ajunge in 
          //dreptul coloanei specificate si se va compara celula cu valoarea 
          //specificata, iar in functie de relatia data se vor sterge
          //liniile care respecta conditia 
          switch (aux_table->type){
            case INT:{
              t_intLine *aux_line,*pre_line=NULL;
              t_intCell *aux_cell;
              for(aux_line=aux_table->lines; aux_line!=NULL;){
                for(i=0,aux_cell=aux_line->cells;i<nr_col && aux_cell!=NULL ;
                i++, aux_cell=aux_cell->next);
                if(strcmp(relational, "<")==0){
                  if(aux_cell->value < atoi(val_cell)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_intCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                  
                }else if(strcmp(relational, "<=")==0){
                  if(aux_cell->value <= atoi(val_cell)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_intCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, "==")==0){
                  if(aux_cell->value == atoi(val_cell)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_intCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, "!=")==0){
                  if(aux_cell->value != atoi(val_cell)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_intCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, ">=")==0){
                  if(aux_cell->value >= atoi(val_cell)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_intCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, ">")==0){
                  if(aux_cell->value > atoi(val_cell)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_intCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }
                
              }
              break;
            }
            case FLOAT:{
              t_floatLine *aux_line,*pre_line=NULL;
              t_floatCell *aux_cell;
              for(aux_line=aux_table->lines; aux_line!=NULL;){
                for(i=0,aux_cell=aux_line->cells;i<nr_col && aux_cell!=NULL ;
                i++, aux_cell=aux_cell->next);
                if(strcmp(relational, "<")==0){
                  if(aux_cell->value < strtof(val_cell, NULL)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_floatCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                  
                }else if(strcmp(relational, "<=")==0){
                  if(aux_cell->value <= strtof(val_cell, NULL)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_floatCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, "==")==0){
                  if(aux_cell->value == strtof(val_cell, NULL)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_floatCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, "!=")==0){
                  if(aux_cell->value != strtof(val_cell, NULL)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_floatCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, ">=")==0){
                  if(aux_cell->value >= strtof(val_cell, NULL)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_floatCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, ">")==0){
                  if(aux_cell->value > strtof(val_cell, NULL)){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_floatCell *tmp_cell;
                      tmp_cell=aux_cell->next;
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }
                
              }
              break;
            }
            case STRING:{
              t_stringLine *aux_line,*pre_line=NULL;
              t_stringCell *aux_cell;
              for(aux_line=aux_table->lines; aux_line!=NULL;){
                for(i=0,aux_cell=aux_line->cells;i<nr_col && aux_cell!=NULL ;
                i++, aux_cell=aux_cell->next);
                if(strcmp(relational, "<")==0){
                  if(strcmp(aux_cell->value, val_cell)<0){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_stringCell *tmp_cell;
                      tmp_cell=aux_cell->next;
					  free(aux_cell->value);
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                  
                }else if(strcmp(relational, "<=")==0){
                  if(strcmp(aux_cell->value, val_cell)<=0){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_stringCell *tmp_cell;
                      tmp_cell=aux_cell->next;
					  free(aux_cell->value);
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, "==")==0){
                  if(strcmp(aux_cell->value, val_cell)==0){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_stringCell *tmp_cell;
                      tmp_cell=aux_cell->next;
					  free(aux_cell->value);
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, "!=")==0){
                  if(strcmp(aux_cell->value, val_cell)!=0){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_stringCell *tmp_cell;
                      tmp_cell=aux_cell->next;
					  free(aux_cell->value);
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, ">=")==0){
                  if(strcmp(aux_cell->value, val_cell)>=0){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_stringCell *tmp_cell;
                      tmp_cell=aux_cell->next;
					  free(aux_cell->value);
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }else if(strcmp(relational, ">")==0){
                  if(strcmp(aux_cell->value, val_cell)>0){
                    if(pre_line==NULL){
                      aux_table->lines=aux_line->next;
                    }else{
                      pre_line->next=aux_line->next;
                    }
                    for(aux_cell=aux_line->cells;aux_cell!=NULL ;){
                      t_stringCell *tmp_cell;
                      tmp_cell=aux_cell->next;
					  free(aux_cell->value);
                      free(aux_cell);
                      aux_cell=tmp_cell;
                    }
                    free(aux_line);
                    if(pre_line == NULL) {
                        aux_line = aux_table->lines;
                    }
                    else {
                        aux_line=pre_line->next;
                    }
                  }else{
                    pre_line=aux_line;
                    aux_line=aux_line->next;
                  }
                }
                
              }
              break;
            }
          }          
        }
      }
    }
  }
  if(err_table==0){
    printf("Table \"%s\" not found in database.\n", name_table);
    return;
  }
  if(err_col==0&&err_table==1){
    printf("Table \"%s\" does not contain column \"%s\".\n", name_table,
     name_col);
  }

}

//cu ajutorul acestei functii se vor gasi liniile de pe coloana
//specificata care respecta relatia data
void search(t_db *data_base, char *name_table, char *name_col, 
char* relational, char *val_cell){
  t_table *aux_table;
  t_column *aux_column;

  int nr_col, i, crt, err_table=0, err_col=0;
  //se va parcurge lista de tabele din baza de date si se va verifica 
  //daca exista tabelul specificat. In cazul in care nu exista, 
  //se va afisa un mesaj corespunzator
  for(aux_table=data_base->tables; aux_table!=NULL; aux_table=aux_table->next){
    if(strcmp(aux_table->name,name_table)==0){
      err_table=1;
      //se vor parcuge coloanele pentru a verifica daca exista coloana 
      //indicata in tabel. Daca aceasta nu exista se va iesi din bucle 
      //si se va afisa un mesaj corespunzator
      for(aux_column=aux_table->columns;aux_column!=NULL;
      aux_column=aux_column->next){
        if(strcmp(aux_column->name, name_col)==0){
          err_col=1;
          break;
        }else{
          err_col=0;
        }
      }
      if(err_col==0){
        break;
      }
      //se va printa numele tabelului si coloanele indiferent de relatia 
      //specificata
      printf("TABLE: %s\n", name_table);
      for(aux_column=aux_table->columns; aux_column!=NULL;
      aux_column=aux_column->next){
        printf("%s", aux_column->name);
        for(int i=0; i<MAX_COLUMN_NAME_LEN-strlen(aux_column->name); i++){
          printf(" ");
        } 
        printf(" ");
      }
      printf("\n");
      for(aux_column=aux_table->columns; aux_column!=NULL;
      aux_column=aux_column->next){
        for(i=0; i<MAX_COLUMN_NAME_LEN; i++){
          printf("-");
        }
        printf(" ");
      }
      printf("\n");
      //se va parcurge lista cu coloane si se va afla pozitia pe care se afla 
      //coloana specificata
      for(nr_col=0,aux_column=aux_table->columns; aux_column!=NULL;
      nr_col++,aux_column=aux_column->next){
        if(strcmp(aux_column->name, name_col)==0){
          //se va parcurge fiecare linie in functie de tipul tabelului
          //dupa aceea se va parcurge lista de celule pana cand se ajunge in 
          //dreptul coloanei specificate si se va compara celula cu valoarea 
          //specificata, iar in functie de relatia data se vor afisa
          //liniile care respecta conditia 
          switch (aux_table->type){
            case INT:{
              t_intLine *aux_line;
              t_intCell *aux_cell;
              int test_cell;
              crt=0;
              for(aux_line=aux_table->lines; aux_line!=NULL;
              aux_line=aux_line->next){
                for(i=0,aux_cell=aux_line->cells;i<nr_col && aux_cell!=NULL ;
                i++, aux_cell=aux_cell->next);
                if(strcmp(relational, "<")==0){
                  if(aux_cell->value < atoi(val_cell)){
                      for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                      aux_cell=aux_cell->next){
                        crt=0;
                        printf("%d", aux_cell->value);
            
                        if(aux_cell->value==0)
                          crt=1;
                        else
                          for(test_cell=aux_cell->value; test_cell!=0; 
                          test_cell=test_cell/10, crt++);
            
                        for(i=0; i<MAX_COLUMN_NAME_LEN-crt; i++){
                          printf(" ");
                        }
                        printf(" ");
                      }
                      printf("\n");
                  }
                  
                }else if(strcmp(relational, "<=")==0){
                  if(aux_cell->value <= atoi(val_cell)){
                      for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                      aux_cell=aux_cell->next){
                        crt=0;
                        printf("%d", aux_cell->value);
            
                        if(aux_cell->value==0)
                          crt=1;
                        else
                          for(test_cell=aux_cell->value; test_cell!=0; 
                          test_cell=test_cell/10, crt++);
            
                        for(i=0; i<MAX_COLUMN_NAME_LEN-crt; i++){
                          printf(" ");
                        }
                        printf(" ");
                      }
                      printf("\n");
                  }
                }else if(strcmp(relational, "==")==0){
                  if(aux_cell->value == atoi(val_cell)){ 
                      for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                      aux_cell=aux_cell->next){
                        crt=0;
                        printf("%d", aux_cell->value);
            
                        if(aux_cell->value==0)
                          crt=1;
                        else
                          for(test_cell=aux_cell->value; test_cell!=0; 
                          test_cell=test_cell/10, crt++);
            
                        for(i=0; i<MAX_COLUMN_NAME_LEN-crt; i++){
                          printf(" ");
                        }
                        printf(" ");
                      }
                      printf("\n");
                  }
                }else if(strcmp(relational, "!=")==0){
                  if(aux_cell->value != atoi(val_cell)){  
                      for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                      aux_cell=aux_cell->next){
                        crt=0;
                        printf("%d", aux_cell->value);
            
                        if(aux_cell->value==0)
                          crt=1;
                        else
                          for(test_cell=aux_cell->value; test_cell!=0; 
                          test_cell=test_cell/10, crt++);
            
                        for(i=0; i<MAX_COLUMN_NAME_LEN-crt; i++){
                          printf(" ");
                        }
                        printf(" ");
                      }
                      printf("\n");                    
                  }
                }else if(strcmp(relational, ">=")==0){
                  if(aux_cell->value >= atoi(val_cell)){  
                      for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                      aux_cell=aux_cell->next){
                        crt=0;
                        printf("%d", aux_cell->value);
            
                        if(aux_cell->value==0)
                          crt=1;
                        else
                          for(test_cell=aux_cell->value; test_cell!=0; 
                          test_cell=test_cell/10, crt++);
            
                        for(i=0; i<MAX_COLUMN_NAME_LEN-crt; i++){
                          printf(" ");
                        }
                        printf(" ");
                      }
                      printf("\n");                    
                  }
                }else if(strcmp(relational, ">")==0){
                  if(aux_cell->value > atoi(val_cell)){  
                      for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                      aux_cell=aux_cell->next){
                        crt=0;
                        printf("%d", aux_cell->value);
            
                        if(aux_cell->value==0)
                          crt=1;
                        else
                          for(test_cell=aux_cell->value; test_cell!=0; 
                          test_cell=test_cell/10, crt++);
            
                        for(i=0; i<MAX_COLUMN_NAME_LEN-crt; i++){
                          printf(" ");
                        }
                        printf(" ");
                      }
                      printf("\n");                    
                  }
                } 
              }
              break;
            }
            case FLOAT:{
              t_floatLine *aux_line, *pre_line;
              t_floatCell *aux_cell;
              float test_cell;
              crt=0;
              for(aux_line=aux_table->lines; aux_line!=NULL;
              aux_line=aux_line->next){
                for(i=0,aux_cell=aux_line->cells;i<nr_col && aux_cell!=NULL ;
                i++, aux_cell=aux_cell->next);
                if(strcmp(relational, "<")==0){
                  if(aux_cell->value < strtof(val_cell, NULL)){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      crt=0;
                      if(fabs(aux_cell->value) < 1) {
                        crt++;
                      }
                      printf("%.6f", aux_cell->value);
                      //fabs() - pt modul
                      for(test_cell=aux_cell->value; fabs(test_cell)>=1; 
                      test_cell=test_cell/10 ,crt++);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-crt-7; i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }
                }else if(strcmp(relational, "<=")==0){
                  if(aux_cell->value <= strtof(val_cell, NULL)){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      crt=0;
                      if(fabs(aux_cell->value) < 1) {
                        crt++;
                      }
                      printf("%.6f", aux_cell->value);
                      //fabs() - pt modul
                      for(test_cell=aux_cell->value; fabs(test_cell)>=1; 
                      test_cell=test_cell/10 ,crt++);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-crt-7; i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }
                }else if(strcmp(relational, "==")==0){
                  if(aux_cell->value == strtof(val_cell, NULL)){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      crt=0;
                      if(fabs(aux_cell->value) < 1) {
                        crt++;
                      }
                      printf("%.6f", aux_cell->value);
                      //fabs() - pt modul
                      for(test_cell=aux_cell->value; fabs(test_cell)>=1; 
                      test_cell=test_cell/10 ,crt++);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-crt-7; i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }
                }else if(strcmp(relational, "!=")==0){
                  if(aux_cell->value != strtof(val_cell, NULL)){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      crt=0;
                      if(fabs(aux_cell->value) < 1) {
                        crt++;
                      }
                      printf("%.6f", aux_cell->value);
                      //fabs() - pt modul
                      for(test_cell=aux_cell->value; fabs(test_cell)>=1; 
                      test_cell=test_cell/10 ,crt++);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-crt-7; i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }
                }else if(strcmp(relational, ">=")==0){
                  if(aux_cell->value >= strtof(val_cell, NULL)){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      crt=0;
                      if(fabs(aux_cell->value) < 1) {
                        crt++;
                      }
                      printf("%.6f", aux_cell->value);
                      //fabs() - pt modul
                      for(test_cell=aux_cell->value; fabs(test_cell)>=1; 
                      test_cell=test_cell/10 ,crt++);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-crt-7; i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }
                }else if(strcmp(relational, ">")==0){
                  if(aux_cell->value > strtof(val_cell, NULL)){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      crt=0;
                      if(fabs(aux_cell->value) < 1) {
                        crt++;
                      }
                      printf("%.6f", aux_cell->value);
                      //fabs() - pt modul
                      for(test_cell=aux_cell->value; fabs(test_cell)>=1; 
                      test_cell=test_cell/10 ,crt++);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-crt-7; i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }
                } 
              }
              break;
            }
            case STRING:{
              t_stringLine *aux_line, *pre_line;
              t_stringCell *aux_cell;
              for(aux_line=aux_table->lines; aux_line!=NULL;
              aux_line=aux_line->next){
                for(i=0,aux_cell=aux_line->cells;i<nr_col && aux_cell!=NULL ;
                i++, aux_cell=aux_cell->next);
                if(strcmp(relational, "<")==0){
                  if(strcmp(aux_cell->value, val_cell)<0){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      printf("%s", aux_cell->value);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-strlen(aux_cell->value); 
                      i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }                  
                }else if(strcmp(relational, "<=")==0){
                  if(strcmp(aux_cell->value, val_cell)<=0){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      printf("%s", aux_cell->value);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-strlen(aux_cell->value); 
                      i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }
                }else if(strcmp(relational, "==")==0){
                  if(strcmp(aux_cell->value, val_cell)==0){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      printf("%s", aux_cell->value);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-strlen(aux_cell->value); 
                      i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }
                }else if(strcmp(relational, "!=")==0){
                  if(strcmp(aux_cell->value, val_cell)!=0){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      printf("%s", aux_cell->value);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-strlen(aux_cell->value); 
                      i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }
                }else if(strcmp(relational, ">=")==0){
                  if(strcmp(aux_cell->value, val_cell)>=0){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      printf("%s", aux_cell->value);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-strlen(aux_cell->value); 
                      i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }
                }else if(strcmp(relational, ">")==0){
                  if(strcmp(aux_cell->value, val_cell)>0){
                    for(aux_cell=aux_line->cells; aux_cell!=NULL; 
                    aux_cell=aux_cell->next){
                      printf("%s", aux_cell->value);
                      for(i=0; i<MAX_COLUMN_NAME_LEN-strlen(aux_cell->value); 
                      i++){
                        printf(" ");
                      }
                      printf(" ");
                    }
                    printf("\n");
                  }
                }    
              }
              break;
            }
          }          
        }
      }
      printf("\n");
    }
  }
  
  if(err_col==0&&err_table==1){
    printf("Table \"%s\" does not contain column \"%s\".\n", name_table, 
    name_col);
  }
  if(err_table==0){
    printf("Table \"%s\" not found in database.\n", name_table);
    
  }
}

//cu ajutorul acestei functii se vor elimina toate liniile din tabelul 
//specificat
void clear(t_db *data_base, char *name_table){
  t_table *aux_table;
  t_column *aux_column;
  int err=0;
  //se ve parcurge lista cu tabele din baza de date si se va cauta tabelul
  //specificat. Daca acesta nu se gaseste se va afisa un mesaj corespunzator 
  //de eroare
  for(aux_table=data_base->tables; aux_table!=NULL; aux_table=aux_table->next){
    if(strcmp(aux_table->name,name_table )==0){
      err=1;
      //in functie de tipul tabelului se vor parcurge listele cu linii si
      //la randul lor listele cu celule si se vor elimina din tabel
      switch(aux_table->type){
        case INT:{
          t_intLine *aux_line,*pre_line=NULL;
          t_intCell *aux_cell;
          for(aux_line=aux_table->lines; aux_line!=NULL;){
            if(pre_line==NULL){
              aux_table->lines=aux_line->next;
            }else{
              pre_line->next=aux_line->next;
            }
            for(aux_cell=aux_line->cells;aux_cell!=NULL;){
              t_intCell *tmp_cell;
              tmp_cell=aux_cell->next;
              free(aux_cell);
              aux_cell=tmp_cell;
            }
            free(aux_line);
            if(pre_line==NULL){
              aux_line=aux_table->lines;
            }else{
              aux_line=pre_line->next;
            }   
          }
          break;
        }
        case FLOAT:{
          t_floatLine *aux_line,*pre_line=NULL;
          t_floatCell *aux_cell;
          for(aux_line=aux_table->lines; aux_line!=NULL;){
            if(pre_line==NULL){
              aux_table->lines=aux_line->next;
            }else{
              pre_line->next=aux_line->next;
            }
            for(aux_cell=aux_line->cells;aux_cell!=NULL;){
              t_floatCell *tmp_cell;
              tmp_cell=aux_cell->next;
              free(aux_cell);
              aux_cell=tmp_cell;
            }
            free(aux_line);
            if(pre_line==NULL){
              aux_line=aux_table->lines;
            }else{
              aux_line=pre_line->next;
            }   
          }
          break;
        }
        case STRING:{
          t_stringLine *aux_line,*pre_line=NULL;
          t_stringCell *aux_cell;
          for(aux_line=aux_table->lines; aux_line!=NULL;){
            if(pre_line==NULL){
              aux_table->lines=aux_line->next;
            }else{
              pre_line->next=aux_line->next;
            }
            for(aux_cell=aux_line->cells;aux_cell!=NULL;){
              t_stringCell *tmp_cell;
              tmp_cell=aux_cell->next;
              free(aux_cell->value);
              free(aux_cell);
              aux_cell=tmp_cell;
            }
            free(aux_line);
            if(pre_line==NULL){
              aux_line=aux_table->lines;
            }else{
              aux_line=pre_line->next;
            }   
          }
          break;

        }
      }

    }
  }
  if(err==0){
    printf("Table \"%s\" not found in database.\n", name_table);
  }
}

//cu ajutorul acestei functii se va elimina tabelul specificat din baza de date
void delete_table(t_db *data_base, char *name_table){
  t_table *aux_table, *pre_table=NULL;//pre_table - reprezinta tabelul anterior
  t_column *aux_column, *pre_column=NULL;//pre_column-reprezinta 
  //coloana anterioara

  int err=0;
  //se va parcurge lista cu tabele, iar in cazul in care tabelul specificat 
  //nu exista, se va afisa un mesaj corespunzator
  for(aux_table=data_base->tables; aux_table!=NULL; ){
    if(strcmp(aux_table->name,name_table )==0){
      err=1;
      //daca tabelul care trebuie eliminat se afla pe prima pozitie,
      //se va face legatura intre urmatorul tabel si baza de date
      //iar daca acesta se afla pe alta pozitie fata de prima 
      //se va reface legatura intre tabelul anterior si tabelul urmator
      if(pre_table==NULL){
        data_base->tables=aux_table->next;
      }else{
        pre_table->next=aux_table->next;
      }  

      //dupa ce se refac legaturile se parcurge lista cu coloane a tabelului
      //si se elibereaza fiecare coloana
      for(aux_column=aux_table->columns;aux_column!=NULL;){
        if(pre_column==NULL){
          aux_table->columns=aux_column->next;
        }else{
          pre_column->next=aux_column->next;
        }
        free(aux_column);
        if(pre_column==NULL){
          aux_column=aux_table->columns;
        }else{
          aux_column=pre_column->next;
        }
      }
      //in functie de tipul tabelului se parcurge listele cu linii si 
      //la randul lor
      switch(aux_table->type){
        case INT:{
          t_intLine *aux_line,*pre_line=NULL;
          t_intCell *aux_cell;
          for(aux_line=aux_table->lines; aux_line!=NULL;){
            if(pre_line==NULL){
              aux_table->lines=aux_line->next;
            }else{
              pre_line->next=aux_line->next;
            }
            for(aux_cell=aux_line->cells;aux_cell!=NULL;){
              t_intCell *tmp_cell;
              tmp_cell=aux_cell->next;
              free(aux_cell);
              aux_cell=tmp_cell;
            }
            free(aux_line);
            if(pre_line==NULL){
              aux_line=aux_table->lines;
            }else{
              aux_line=pre_line->next;
            }   
          }
          break;
        }
        case FLOAT:{
          t_floatLine *aux_line,*pre_line=NULL;
          t_floatCell *aux_cell;
          for(aux_line=aux_table->lines; aux_line!=NULL;){
            if(pre_line==NULL){
              aux_table->lines=aux_line->next;
            }else{
              pre_line->next=aux_line->next;
            }
            for(aux_cell=aux_line->cells;aux_cell!=NULL;){
              t_floatCell *tmp_cell;
              tmp_cell=aux_cell->next;
              free(aux_cell);
              aux_cell=tmp_cell;
            }
            free(aux_line);
            if(pre_line==NULL){
              aux_line=aux_table->lines;
            }else{
              aux_line=pre_line->next;
            }   
          }
          break;
        }
        case STRING:{
          t_stringLine *aux_line,*pre_line=NULL;
          t_stringCell *aux_cell;
          for(aux_line=aux_table->lines; aux_line!=NULL;){
            if(pre_line==NULL){
              aux_table->lines=aux_line->next;
            }else{
              pre_line->next=aux_line->next;
            }
            for(aux_cell=aux_line->cells;aux_cell!=NULL;){
              t_stringCell *tmp_cell;
              tmp_cell=aux_cell->next;
              free(aux_cell->value);
              free(aux_cell);
              aux_cell=tmp_cell;
            }
            free(aux_line);
            if(pre_line==NULL){
              aux_line=aux_table->lines;
            }else{
              aux_line=pre_line->next;
            }   
          }
          break;
        }
      }
      free(aux_table);
      if(pre_table==NULL){
        aux_table=data_base->tables;
      }else{
        aux_table=pre_table->next;
      }
    }else{
      pre_table=aux_table;
      aux_table=aux_table->next;
    }
  }
  if(err==0){
    printf("Table \"%s\" not found in database.\n", name_table);
  }
}

//cu ajutorul acestei functii se va elibera intreaba baza de date
void delete_db(t_db *data_base){
  t_table *aux_table, *pre_table=NULL;
  t_column *aux_column, *pre_column=NULL;
  //se va parcurge lista de tabele si se vor elibera prima oara valorile din ele, parcurgand lista 
  //de coloane si lista de linii, si apoi lista de celule, iar apoi se vor elibera tabelele si 
  //intreaga baza de date
  for(aux_table=data_base->tables; aux_table!=NULL; pre_table=aux_table){
  
      if(pre_table==NULL){
        data_base->tables=aux_table->next;
      }else{
        pre_table->next=aux_table->next;
      }      
      for(aux_column=aux_table->columns;aux_column!=NULL;){
        if(pre_column==NULL){
          aux_table->columns=aux_column->next;
        }else{
          pre_column->next=aux_column->next;
        }
        free(aux_column);
        if(pre_column==NULL){
          aux_column=aux_table->columns;
        }else{
          aux_column=pre_column->next;
        }
      }
      switch(aux_table->type){
        case INT:{
          t_intLine *aux_line,*pre_line=NULL;
          t_intCell *aux_cell;
          for(aux_line=aux_table->lines; aux_line!=NULL;){
            if(pre_line==NULL){
              aux_table->lines=aux_line->next;
            }else{
              pre_line->next=aux_line->next;
            }
            for(aux_cell=aux_line->cells;aux_cell!=NULL;){
              t_intCell *tmp_cell;
              tmp_cell=aux_cell->next;
              free(aux_cell);
              aux_cell=tmp_cell;
            }
            free(aux_line);
            if(pre_line==NULL){
              aux_line=aux_table->lines;
            }else{
              aux_line=pre_line->next;
            }   
          }
          break;
        }
        case FLOAT:{
          t_floatLine *aux_line,*pre_line=NULL;
          t_floatCell *aux_cell;
          for(aux_line=aux_table->lines; aux_line!=NULL;){
            if(pre_line==NULL){
              aux_table->lines=aux_line->next;
            }else{
              pre_line->next=aux_line->next;
            }
            for(aux_cell=aux_line->cells;aux_cell!=NULL;){
              t_floatCell *tmp_cell;
              tmp_cell=aux_cell->next;
              free(aux_cell);
              aux_cell=tmp_cell;
            }
            free(aux_line);
            if(pre_line==NULL){
              aux_line=aux_table->lines;
            }else{
              aux_line=pre_line->next;
            }   
          }
          break;
        }
        case STRING:{
          t_stringLine *aux_line,*pre_line=NULL;
          t_stringCell *aux_cell;
          for(aux_line=aux_table->lines; aux_line!=NULL;){
            if(pre_line==NULL){
              aux_table->lines=aux_line->next;
            }else{
              pre_line->next=aux_line->next;
            }
            for(aux_cell=aux_line->cells;aux_cell!=NULL;){
              t_stringCell *tmp_cell;
              tmp_cell=aux_cell->next;
              free(aux_cell->value);
              free(aux_cell);
              aux_cell=tmp_cell;
            }
            free(aux_line);
            if(pre_line==NULL){
              aux_line=aux_table->lines;
            }else{
              aux_line=pre_line->next;
            }   
          }
          break;
        }
      }
	  if(data_base->tables == aux_table)
		  data_base->tables = aux_table->next; 
      free(aux_table);
	  aux_table = data_base->tables;
	  if(!aux_table)
		  break;
  }
  free(data_base);
  data_base=NULL;
  
}

int main() {
  char *token;
  t_db *data_base;
  char script_line[MAX_CMD_LEN];
  char delimiters[] = " \n";
  char *relational;
  int i, nr_col,st;

  //se va citi script-ul folosind un buffer
  //se va analiza fiecare linie a scriptului si se va aplica 
  //transformarea corespunzatoare
  while(fgets(script_line, MAX_CMD_LEN, stdin) != NULL) {
    st=1; //Nr cuvinte;
    for(i=0;script_line[i]!='\0';i++){
      if(script_line[i]==' '){
        st=st+1;
      }
    }
    token=strtok(script_line,delimiters);
    if(strcmp(token, "INIT_DB")==0){
      token=strtok(NULL,delimiters);
      data_base=init_db(token);
    }else if(strcmp(token, "PRINT_DB")==0){
      print_db(data_base);
    }else if(strcmp(token, "DELETE_DB")==0){
      delete_db(data_base);
      break;
    }else if(strcmp(token, "CREATE")==0){
      t_cellType type;
      char *name_table;
      char *name_col[MAX_COLUMN_NAME_LEN];
      token=strtok(NULL, delimiters);
      name_table=strdup(token);
      token=strtok(NULL, delimiters);
      if(strcmp(token, "INT")==0){
        type=INT;
      }else if(strcmp(token, "FLOAT")==0){
        type=FLOAT;
      }else if(strcmp(token, "STRING")==0){
        type=STRING;
      }else{
        printf("Unknown data type:\"%s\".\n", token);
        continue;
      }
      token=strtok(NULL, delimiters);
      for(i=0;token!=NULL;token=strtok(NULL, delimiters), i++){
        name_col[i]=strdup(token);
      }
      nr_col=i;
      create(data_base, name_table, type, name_col, nr_col);
      for(i=0;i<nr_col; i++){
        free(name_col[i]);
      }
      free(name_table);
    }else if(strcmp(token, "ADD")==0){
      char *name_table;
      char *val_cell[30]={0};
      token=strtok(NULL, delimiters);
      name_table=strdup(token);
      token=strtok(NULL, delimiters);
      for(i=0; token!=NULL; token=strtok(NULL, delimiters), i++){
        val_cell[i]=strdup(token);    
      }
      nr_col=i;
      add_line(data_base, name_table, val_cell, nr_col);
      free(name_table);

      for(i=i-1; i>=0; i--){
        free(val_cell[i]);    
      }      
    }else if(strcmp(token, "PRINT")==0){
      char *name_table;
      token=strtok(NULL, delimiters);
      name_table=strdup(token);
      print_table(data_base, name_table);
      free(name_table);
    }else if(strcmp(token, "DELETE")==0){
      char *name_table;
      if(st>2){
          char *name_col;
          char *val_cell;
          token=strtok(NULL, delimiters);
          name_table=strdup(token);
          token=strtok(NULL, delimiters);
          name_col=strdup(token);
          token=strtok(NULL, delimiters);
          relational=strdup(token);
          token=strtok(NULL, delimiters);
          val_cell=token;
          delete(data_base, name_table, name_col, relational, val_cell);
          free(name_col);
          free(relational);
        }else{
          token=strtok(NULL, delimiters);
          name_table=strdup(token);
          delete_table(data_base, name_table);
        }
        free(name_table);
    }else if(strcmp(token, "SEARCH")==0){
      char *name_table;
      char *name_col;
      char *val_cell;
      token=strtok(NULL, delimiters);
      name_table=strdup(token);
      token=strtok(NULL, delimiters);
      name_col=strdup(token);
      token=strtok(NULL, delimiters);
      relational=strdup(token);
      token=strtok(NULL, delimiters);
      val_cell=token;
      search(data_base, name_table, name_col, relational, val_cell);
      free(name_table);
      free(name_col);
      free(relational);
    }else if(strcmp(token, "CLEAR")==0){
      char *name_table;
      token=strtok(NULL, delimiters);
      name_table=strdup(token);
      clear(data_base, name_table);
      free(name_table);
    }else{
      printf("Unknown command:\"%s\".\n", token);
    }
  }
  return 0;
}
