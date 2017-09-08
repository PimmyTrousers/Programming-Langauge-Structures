#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int basic_word_length(char *word);
size_t advanced_word_length(const char *word);


int main(int argc, char** argv){
  char c[100];
  int lettercount;
  printf("enter your word: ");
  scanf("%s", c);
  lettercount = basic_word_length(c);
  printf("after the basic word length we get , %d\n", lettercount);
  lettercount = advanced_word_length(c);
  printf("after the advanced word length we get, %d\n", lettercount);
  printf("standard strlen() is, %zu\n", strlen(c));
}



int basic_word_length(char *word){
  int i = 0;
  while(word[i] != 0){
    i++;
  }
  return i;
}

size_t advanced_word_length(const char *word){
  const char *s;
  for (s = word; *s; ++s);
  return(s-word);
}
