#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dictionary(char* word1, char* word2);
void make_lower(char* word);

int main(int argc, char** argv){

  if(argc > 1){
    printf("I don't take any arguments...\n");
    exit(0);
  }

  char word1[100], word2[100], word1_lower[100], word2_lower[100];

  printf("Enter the first word: ");
  scanf("%s", word1);

  printf("Enter the second word: ");
  scanf("%s", word2);

  strcpy(word1_lower, word1);
  strcpy(word2_lower, word2);

  make_lower(word1_lower);
  make_lower(word2_lower);

  int result = dictionary(word1_lower, word2_lower);

  if(result == 1){
    printf("The word \"%s\" comes first\n", word1);
  }
  else if(result == 2){
    printf("The word \"%s\" comes first\n", word2);
  } 
  else{
    printf("The words are the same\n");
  }
}


int dictionary(char* word1, char* word2){
    size_t length;
    unsigned int flag = 0;

    size_t size1 = strlen(word1);
    size_t size2 = strlen(word2);

    if(size1 > size2) {length = size2;}
    else{length = size1;}

    for(int i = 0; i < length; ++i){
      if(word2[i] > word1[i]){
        return 1;
      }
      else if(word1[i] > word2[i]){
        return 2;
      }
    }

    if(!flag && size1 == size2){
      return 0;
    }

    else if(!flag && size1 > size2)
      return 2;

    else if(!flag && size2 > size1)
      return 1;
}

void make_lower(char* word){
  for(int i = 0; i < strlen(word); ++i){
    if(word[i] > 64 && word[i] < 90)
      word[i] = word[i] + 32;
  }
}
