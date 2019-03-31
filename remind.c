#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_log(int argc,char log[],FILE *remind_log,int counter)
{
  int c;
  int n = 1;
  printf("\nREMINDERS\n---------------\n");
  if(counter != 0){
    printf("%d   ",n);
  }
  counter++;
  remind_log = fopen(log,"r");
  c = fgetc(remind_log);
  while(c != EOF){
    printf("%c", c);
    //insert dividers between reminders
    if(c == '\n'){
      n++;
      for(int i = 0; i<15; i++){
	printf("-");
      }
      printf("\n");
      if(n != counter){
	printf("%d   ",n);
      }
    }
    c = fgetc(remind_log);
  }
}

int count_items(char log[],FILE *remind_log)
{
  int c;
  int counter = 0;
  remind_log = fopen(log,"r");
  c = fgetc(remind_log);
  while(c != EOF){
    if(c == '\n'){
      counter++;
    }
    c = fgetc(remind_log);
  }
  return counter;
} 

void undo(int counter, char log[], FILE *remind_log)
{
  int c;
  int tempctr = 0;
  FILE *tempfile = fopen("/usr/local/bin/temp.log","w");
  remind_log = fopen(log,"r");
  
  if(counter == 1){
    remind_log = fopen(log,"w");
    return;
  }
  //write undone log to temp file
  c = fgetc(remind_log);
  while(c != EOF){
  fprintf(tempfile,"%c",c);
    if(c == '\n'){
      tempctr++;
    }
    if(tempctr == counter-1){
      break;
    }
    c = fgetc(remind_log);
  }
  fclose(remind_log);
  fclose(tempfile);

  tempfile = fopen("/usr/local/bin/temp.log","r");
  remind_log = fopen(log,"w");
  c = fgetc(tempfile);
  while(c != EOF){
    fprintf(remind_log,"%c",c);
    c = fgetc(tempfile);
  }
}

void clear(FILE *remind_log,char log[])
{
  remind_log = fopen(log,"w");
  return;
}

void remove_line(int counter,int line_to_remove,FILE *remind_log,char log[])
{
  int c;
  int tempctr = 0;
  FILE *tempfile = fopen("/usr/local/bin/temp.log","w");
  remind_log = fopen(log,"r");

  if(line_to_remove > counter){
    fprintf(stderr,"Item does not exist\n");
    exit(1);
  }
  if(counter == 1 && line_to_remove == 1){
    remind_log = fopen(log,"w");
    return;
  }

  c = fgetc(remind_log);
  while(c != EOF){
    if(tempctr != line_to_remove-1){
      fprintf(tempfile,"%c",c);
    }
    if(c == '\n'){
      tempctr++;
    }
    if(tempctr == line_to_remove-1){
      c = fgetc(remind_log);
      while(c != '\n' && c != EOF){
	c = fgetc(remind_log);
      }
      tempctr++;
    }
    c = fgetc(remind_log);
  }
  fclose(remind_log);
  fclose(tempfile);

  tempfile = fopen("/usr/local/bin/temp.log","r");
  remind_log = fopen(log,"w");
  c = fgetc(tempfile);
  while(c != EOF){
    fprintf(remind_log,"%c",c);
    c = fgetc(tempfile);
  }
}
  
int main(int argc, char *argv[])
{
  FILE *remind_log;
  char log[] = "/usr/local/bin/reminds.log";
  remind_log = fopen(log,"a");

  //get number of items in log
  int counter = count_items(log,remind_log);
  
  //remove certain numbered line
  if(argc == 3 && strcmp(argv[1],"rm") == 0){
    int n = atoi(argv[2]);
    remove_line(counter,n,remind_log,log);
    return 0;
  }
  //undo
  if(argc == 2 && strcmp(argv[1],"undo") == 0){
    undo(counter,log,remind_log);
    return 0;
  }

  //clear
  if(argc == 2 && strcmp(argv[1],"clear") == 0){
    clear(remind_log,log);
    return 0;
  }
  //if there are no given parameters, print log
  if(argc == 1){
    print_log(argc,log,remind_log,counter);
  return 0;
  }

  //else add reminder to log
  for(int i = 1;i<argc;i++){
    fprintf(remind_log,"%s ",argv[i]);
  }
  fprintf(remind_log,"\n");

  return 0;
}
