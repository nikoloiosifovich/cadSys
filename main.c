#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* GLOBAL VARS... */
FILE *bd;       // BASE
FILE *f_lines;  // FIRST LINES
FILE *l_lines;  // LAST LINES
FILE *s_line;   // SELECTED LINE

char bd_file[6] = {"bd.txt"};
char first_lines[11] = {"f_lines.txt"};
char last_lines[11] = {"l_lines.txt"};
char selected_line[10] = {"s_line.txt"};
char reg, gender, name[20];
int id_client, age;
float credit;

/* FUNCTIONS... */

// READ REGISTRIES...
void read_reg(FILE *arq){

  // READ THE 1ST REG AS REG AND PUT SOME STRUCTURED TYPE OF DATA ON RESPECTIVE VARS...
  reg = fscanf(arq,"%d %c %s %d %f",&id_client,&gender,&name,&age,&credit);
}
// INPUT REGISTRIES...
void put_reg(FILE *i_arq){

  fprintf(i_arq,"%d %c %s %d %.2f\n",id_client,gender,name,age,credit);
}

// PRINT ALL LINES FROM DATA TOP-DOWN...
void print_reg(){

  bd = fopen(bd_file,"r");

  read_reg(bd);
  printf("ID SEXO NOME IDADE CREDITO\n");

  while(reg != EOF){

    printf("%d %c %s %d %.2f\n",id_client,gender,name,age,credit);
    read_reg(bd);
  }

  fclose(bd);
}

// SPLIT DATA FILE IN 3 OTHER FILES
void split_file(int line){

  bd = fopen(bd_file,"r");
  f_lines = fopen(first_lines,"w+");
  l_lines = fopen(last_lines,"w+");
  s_line = fopen(selected_line,"w+");

  read_reg(bd);
  while(reg != EOF){

    if(id_client < line){
      put_reg(f_lines);
    }else if(id_client > line){
      put_reg(l_lines);
    }else if(id_client == line){
      put_reg(s_line);
    }
    read_reg(bd);
  }
  fclose(f_lines);
  fclose(l_lines);
  fclose(s_line);
  fclose(bd);
}

// JOIN SOME PICES OF FILES ON NEW DATA FILE...
void join_file(){

  bd = fopen(bd_file,"w+");
  f_lines = fopen(first_lines,"r");
  l_lines = fopen(last_lines,"r");
  s_line = fopen(selected_line,"r");

  read_reg(f_lines);
  while(reg != EOF){

    put_reg(bd);
    read_reg(f_lines);
  }

  read_reg(s_line);
  while(reg != EOF){

    put_reg(bd);
    read_reg(s_line);
  }

  read_reg(l_lines);
  while(reg != EOF){

    put_reg(bd);
    read_reg(l_lines);
  }

  fclose(f_lines);
  fclose(l_lines);
  fclose(s_line);
  fclose(bd);
}

// ADD SOME REGISTRIES ON BOTTOM OF DATA FILE...
void add(){

  bd = fopen(bd_file,"a+");
  read_reg(bd);

  while(reg != EOF){

    // GET THE LAST ID FROM DATA FILE...
    read_reg(bd);
  }

  // GET THE NEW INPUT AND PUT THEN ON BOTTOM...
  printf("%d ",id_client+1);
  scanf(" %c %s %d %f",&gender,name,&age,&credit);
  id_client++;
  fprintf(bd,"%d %c %s %d %.2f\n",id_client,gender,name,age,credit);

  fclose(bd);
}

// DELETE SOME REGISTRIES FROM DATA FILE...
void del(int del_key){

  split_file(del_key);

  s_line = fopen(selected_line,"w+");

  fprintf(s_line,"%d - DELETED! 0 0.00\n",del_key);
  printf("DONE! - REG %d DELETED!\n",del_key);

  fclose(s_line);

  join_file();
}

// UPDATE SOME REGISTRIES FROM DATA FILE...
void update(int up_key){

  split_file(up_key);

  s_line = fopen(selected_line,"w+");

  printf("ID SEXO NOME IDADE CREDITO\n");
  printf("%d ",up_key);
  scanf(" %c %s %d %f",&gender,name,&age,&credit);
  put_reg(s_line);
  printf("DONE! - REG %d UPDATED!\n",up_key);

  fclose(s_line);

  join_file();
}

// SEARCH AND SORT BY NAME SOME REGISTRIES TOP-DOWN...
void search(char to_search[]){

  bd = fopen(bd_file,"r");
  read_reg(bd);
  printf("ID SEXO NOME IDADE CREDITO\n");

  while(reg != EOF){

    // CHECK IF THE NAME SEARCHED EXIST ON DATA AND PRINT TOP-DOWN...
    if(strcasecmp(to_search,name) == 0){
      printf("%d %c %s %d %.2f\n",id_client,gender,name,age,credit);
    }
    read_reg(bd);
   }

  fclose(bd);
}

// I IMPLEMENT THIS TO PAUSE MY SYSTEM - LINUX LIKE.
void pause_sys(char stop[]){

  printf("\n\nPress any key + ENTER to continue...");
  scanf("%s",stop);
}

/* THE PROGRAM */
int main(){
  // Local Vars..
  char pause_s[1];
  char searched_name[20];
  int key, menu_index = 5;

  // Menu - Principal loop...
  do{

    // Create the default file if not exist...
    if(bd == NULL){

      bd = fopen(bd_file,"w");
      fprintf(bd,"0 - DEFAULT 0 0.0\n");
      fclose(bd);

    }else {

      system("clear");
      printf(" ==== ==== ==== CadSystem ==== ==== ====\n");
      printf("\n\n[1|ADD]\t[2|DELETE] [3|UPDATE] [4|SEARCH]\n");
      printf("\t[0|EXIT]\n\n:: ");
      scanf("%d",&menu_index);

      switch(menu_index){
        case 0 : break;

        case 1 : // add

          print_reg();
          add();
          pause_sys(pause_s);
        break;

        case 2 : // delete

          print_reg();
          printf("\n\nInsert ID: ");
          scanf("%d",&key);
          del(key);
          pause_sys(pause_s);
        break;

        case 3 : // update

          print_reg();
          printf("\n\nInsert ID: ");
          scanf("%d",&key);
          update(key);
          pause_sys(pause_s);
        break;

        case 4 : // search

          printf("Name: ");
          scanf("%20s",searched_name);
          search(searched_name);
          pause_sys(pause_s);
        break;
        default :
        break;
      }
    }
  }while(menu_index != 0);

  return 0;
}
