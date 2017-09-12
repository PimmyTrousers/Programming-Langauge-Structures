#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  if(argc == 1) {
    printf("This program takes arguments in the form of ./a.out testfile.txt");
    exit(0);
  }

  FILE *g;
  char buffer;
  char w[100];
  int wordcount;

  g = fopen(argv[1], "r");
  if(g == NULL){
    printf("Something went wrong while opening the file");
    exit(0);
  }

  for(wordcount = 0; fscanf(g, "%s", w) == 1; ++wordcount){
    continue;
  }
  printf("There are %d words\n", wordcount);

}
