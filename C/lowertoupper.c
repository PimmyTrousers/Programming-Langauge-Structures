#include <stdio.h>
#include <stdlib.h>

int is_upper_or_lower(char letter);
void switch_case(char* word1);


int main(int argc, char** argv){

  if(argc > 1){
    printf("I don't take any arguments...\n");
    exit(0);
  }

  char word1[100], word2[100];
  printf("enter your word: ");
  scanf("%s", word1);
  switch_case(word1);
  printf("%s\n", word1);
}

int is_upper_or_lower(char letter){
  if(letter > 97 && letter < 122){
    return 1;
  }
  if(letter > 65 && letter < 90){
    return 0;
  }
}

void switch_case(char* word1){
  for(int i = 0; word1[i] != 0; ++i){
    if(is_upper_or_lower(word1[i]))
      word1[i] = word1[i] - 32;
    else
      word1[i] = word1[i] + 32;
  }
 }
