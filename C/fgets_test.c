#include <stdio.h>
#include <stdlib.h>

int main()
{
  char equation[1000] ;
  FILE *input_file ;
  input_file = fopen("testfile","r") ;
  if (input_file == NULL) {
    printf("can't opne testfile\n") ;
    exit(0) ;
  }

  fgets(equation, 1000, input_file);
  printf("The input equation is \n\"%s\"\n", equation);
}
