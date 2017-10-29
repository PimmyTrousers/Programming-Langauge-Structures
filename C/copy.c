#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  if(argc != 3){
    printf("This program takes command line args\n");
    exit(0);
  }

  FILE* file1;
  FILE* file2;
  char c;
  file1 = fopen(argv[1], "r");
  file2 = fopen(argv[2], "w");
  if(file1 == NULL || file2 == NULL){
    printf("Something went wrong in opening the two files\n");
    exit(0);
  }

  while(c != EOF){
    c = fgetc(file1);
    fputc(c, file2);
  }
  fclose(file2);
  fclose(file1);
}
